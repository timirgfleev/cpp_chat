#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

        std::string data;

        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            // Read data from the client until '\n' is encountered
            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n');

            // Convert data to std::string
            // Convert data to std::string
            data = boost::asio::buffer_cast<const char *>(buf.data());

            std::cout << "Received: " << data << std::endl;

            std::string message = "Hello from server!\n" + data;

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

            // Clear the data variable
            data.clear();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}