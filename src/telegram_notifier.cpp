/*
    Copyright (C) 2018 Yağmur Oymak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bot/bot.hpp"
#include "config.hpp"
#include "curl_handle/curl_handle.hpp"
#include "global/global.hpp"
#include "queue/queue.hpp"

#include <atomic>
#include <json/json.h>
#include <boost/asio.hpp>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace {

Queue<std::string> message_queue;

bool transmit = true;
std::mutex transmit_mutex;
std::condition_variable transmit_cond;

std::atomic_bool notify = true;

void receiver(void)
{
    using boost::asio::ip::tcp;

    boost::asio::io_context io_context;
    tcp::acceptor acceptor {io_context, tcp::endpoint(tcp::v4(), Config::port)};

    auto read_msg = [](tcp::socket socket)
    {
        std::string buf;
        boost::system::error_code error;

        boost::asio::read(socket, boost::asio::dynamic_buffer(buf), error);

        if (!error || error == boost::asio::error::eof) {
            message_queue.enqueue(std::move(buf));
        } else {
            /*
             * Some error occured that I don't want to handle.
             */
            std::lock_guard lock {Global::cerr_mutex};

            std::cerr << "receiver(): " << error.message() << std::endl;
        }
    };

    for (;;) {
        tcp::socket socket {io_context};

        acceptor.accept(socket);

        std::packaged_task<void(tcp::socket)> task {read_msg};
        std::thread task_td {std::move(task), std::move(socket)};
        task_td.detach();
    }
}

void transmitter(void)
{
    for (;;) {
        auto message = message_queue.dequeue();

        std::unique_lock transmit_lock {transmit_mutex};
        transmit_cond.wait(transmit_lock, []{ return transmit; });
        transmit_lock.unlock();

        Bot::send_message(message, notify);
    }
}

}

int main(int argc, char **argv)
{
    std::thread receive_thread {receiver};
    std::thread transmit_thread {transmitter};

    Bot::register_callback("/pause", []
            {
                std::lock_guard lock {transmit_mutex};
                transmit = false;
            });

    Bot::register_callback("/continue", []
            {
                std::lock_guard lock {transmit_mutex};
                transmit = true;
                transmit_cond.notify_one();
            });

    Bot::register_callback("/notifyoff", []
            {
                notify = false;
            });

    Bot::register_callback("/notifyon", []
            {
                notify = true;
            });

    Bot::update_handler();

    receive_thread.join();
    transmit_thread.join();

    return 0;
}
