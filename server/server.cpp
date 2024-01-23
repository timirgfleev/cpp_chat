#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include <thread>

using boost::asio::ip::tcp;


#include "client_hander.h"


int main()
{
    try
    {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            auto p = std::thread(handle_client, std::move(socket));
            p.detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}