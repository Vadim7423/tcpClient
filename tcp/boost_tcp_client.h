#ifndef BOOST_TCP_CLIENT_H
#define BOOST_TCP_CLIENT_H

#include "tcp_client.h"
#include <boost/asio.hpp>

class BoostTcpClient : public TcpClient
{
public:
    BoostTcpClient();
    void connect(const std::string& host, const std::string& port = "12345") override;
    void disconnect() override;
    bool isConnected() override;
    void send_message(const std::string& msg) override;
    std::string receive_message() override;

private:
    boost::asio::io_context m_io_context; // Контекст ввода-вывода
    boost::asio::ip::tcp::socket m_socket;                // Сокет для общения с сервером
    bool is_connected = false;
};

#endif // BOOST_TCP_CLIENT_H
