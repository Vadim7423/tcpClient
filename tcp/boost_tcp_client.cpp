#include "boost_tcp_client.h"
#include <iostream>

using boost::asio::ip::tcp;

BoostTcpClient::BoostTcpClient()
    : m_io_context(), m_socket(m_io_context)
{

}

void BoostTcpClient::connect(const std::string &host, const std::string& port)
{
    tcp::resolver resolver(m_io_context);
    tcp::resolver::results_type endpoints = resolver.resolve(host, port);

    try {
        boost::asio::connect(m_socket, endpoints);
        is_connected = true;
    } catch (...) {
        is_connected = false;
        std::cerr << "connection error" << std::endl;
    }

}

void BoostTcpClient::disconnect()
{
    m_socket.close();
    is_connected = false;
}

bool BoostTcpClient::isConnected()
{
    return is_connected;
}

void BoostTcpClient::send_message(const std::string &msg)
{
    boost::asio::write(m_socket, boost::asio::buffer(msg));
}

std::string BoostTcpClient::receive_message()
{
    char data[1024];
    size_t length = m_socket.read_some(boost::asio::buffer(data));
    std::string result(data, length);
    return result;
}
