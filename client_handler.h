#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <QObject>
#include <condition_variable>
#include <thread>

class TcpClient;
class Protocol;
class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(TcpClient& client,
                           Protocol& protocol, QObject *parent = nullptr);
    ~ClientHandler();
    void command(const std::string& cmd);

signals:

private:
    void recieve();

    TcpClient& m_client;
    Protocol& m_recieve_protocol;
    std::unique_ptr<std::thread> m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    bool is_finished = false;
    bool is_ready = false;
};

#endif // CLIENT_HANDLER_H
