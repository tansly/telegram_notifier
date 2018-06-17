#include "bot.h"
#include "config.h"
#include "curl_handle.h"
#include "queue.h"

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

static Queue<std::string> message_queue;

void receiver(void)
{
    using boost::asio::ip::tcp;

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 6666));

    std::string buf;

    for (;;) {
        /*
         * XXX: No error checking!
         */
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        size_t n = boost::asio::read_until(socket, boost::asio::dynamic_buffer(buf), "\n\n");
        message_queue.enqueue(buf.substr(0, n));
        buf.erase(0, n);
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
    std::thread receive_thread{receiver};
    std::thread transmit_thread{transmitter};

    receive_thread.join();
    transmit_thread.join();

    return 0;
}
