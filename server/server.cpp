#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include <thread>

using boost::asio::ip::tcp;

void handle_client(tcp::socket socket)
{
    try
    {
        std::string data;
        for (;;)
        {
            // Read data from the client until '\n' is encountered
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n');

            // Make a str from buffer.
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());

            std::cout << "Received: " << data << std::endl;

            // Craft a responce
            std::string message = "Hello from server!\n" + data;

            // Write a reply to the client
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

            // Clear the data variable
            data.clear();
        }
    }
    catch (boost::system::system_error &e)
    {
        // A system_error is thrown when a client disconnects.
        if (e.code() == boost::asio::error::eof)
        {
            // Connection closed cleanly by peer.
            std::cout << "Connection closed cleanly by client." << std::endl;
        }
        else
        {
            // Some other error.
            std::cerr << "Error: " << e.code().message() << std::endl;
        }
    }
    catch (std::exception &e)
    {
        // Catch any other exceptions.
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
}

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

            std::thread(handle_client, std::move(socket)).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}