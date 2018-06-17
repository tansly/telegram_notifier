#include "bot.h"
#include "config.h"
#include "curl_handle.h"
#include "queue.h"

#include <boost/asio.hpp>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

/*
 * TODO: Mutex on std::cout, std::cerr?
 */

static Queue<std::string> message_queue;

void receiver(void)
{
    using boost::asio::ip::tcp;

    boost::asio::io_context io_context;
    tcp::acceptor acceptor {io_context, tcp::endpoint(tcp::v4(), 6666)};

    for (;;) {
        auto read_msg = [](std::unique_ptr<tcp::socket> socket_ptr)
        {
            std::string buf;
            boost::system::error_code error;

            auto n = boost::asio::read(*socket_ptr, boost::asio::dynamic_buffer(buf), error);

            if (!error || error == boost::asio::error::eof) {
                message_queue.enqueue(buf);
            } else {
                /*
                 * Some error occured that I don't want to handle.
                 */
                std::cerr << error.message();
            }
        };

        auto socket_ptr = std::make_unique<tcp::socket>(io_context);

        acceptor.accept(*socket_ptr);

        std::packaged_task<void(std::unique_ptr<tcp::socket>)> task {read_msg};
        std::thread task_td {std::move(task), std::move(socket_ptr)};
        task_td.detach();
    }
}

void transmitter(void)
{
    for (;;) {
        Bot::send_message(message_queue.dequeue());
    }
}

int main(int argc, char **argv)
{
    std::thread receive_thread {receiver};
    std::thread transmit_thread {transmitter};

    receive_thread.join();
    transmit_thread.join();

    return 0;
}
