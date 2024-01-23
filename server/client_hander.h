#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>

#pragma once

using boost::asio::ip::tcp;

std::string handle_string(std::string &data)
{
    std::cout << "Received: " << data << std::endl;
    return "Hello from server!\n" + data;
}

void handle_client(tcp::socket socket)
{
    try
    {
        
        for (;;)
        {
            // Read data from the client until '\n' is encountered
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n');

            // Make a str from buffer.
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());

            // Craft a responce
            std::string message = handle_string(data);

            // Write a reply to the client
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
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