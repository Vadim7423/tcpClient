#include "client_handler.h"
#include "tcp/tcp_client.h"
#include <iostream>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include "protocol/protocol.h"

ClientHandler::ClientHandler(TcpClient& client,
                             Protocol& protocol, QObject *parent)
    : QObject{parent}
    , m_client(client)
    , m_recieve_protocol(protocol)
{
    m_thread.reset(new std::thread(&ClientHandler::recieve, this));
}

ClientHandler::~ClientHandler()
{
    is_finished = true;
    m_cv.notify_one();
    if(m_thread->joinable()) {
        m_thread->join();
    }
}

void ClientHandler::command(const std::string& cmd)
{
    m_client.send_message(cmd);
    is_ready = true;
    m_cv.notify_one();
}

void ClientHandler::recieve()
{
    while(true) {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [this](){
            return is_ready || is_finished;
        });

        if(is_finished)
            break;

        try {
            m_recieve_protocol.recieve(m_client.receive_message());
        } catch (std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }

        is_ready = false;
    }
}
