#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;

#include "chat.h"

static ChatHandler chatHandler;


void handle_request_message(const std::string &data)
{
    std::cout << "Message " << data << std::endl;
};

std::string handle_string(std::string &data)
{
    // Remove the newline character at the end of the data
    if (!data.empty() && data[data.length() - 1] == '\n')
    {
        data.erase(data.length() - 1);
    }

    nlohmann::json jsonData = nlohmann::json::parse(data);

    std::string type = jsonData["action"];

    if (type == "message")
    {
        std::string message = jsonData["message"];
        handle_request_message(message);
    }

    std::string response = jsonData.dump();

    return response;
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
            std::string data = boost::asio::buffer_cast<const char *>(buf.data());

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