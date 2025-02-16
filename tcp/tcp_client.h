#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QString>

class TcpClient {
public:
    virtual ~TcpClient() = default;
    virtual void connect(const std::string& host, const std::string& port = "12345") = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;
    virtual void send_message(const std::string& msg) = 0;
    virtual std::string receive_message() = 0;
};

#endif // TCP_CLIENT_H
