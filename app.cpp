#include "app.h"
#include "client_handler.h"
#include "model/volt_meteers_model.h"

App::App(QObject *parent)
    : QObject{parent}
    , m_tcp_client(new BoostTcpClient)
    , m_model(new VoltMeteersModel(this))
    , m_protocol(new ClientProtocol(m_model))
    , m_client_handler(new ClientHandler(*m_tcp_client, *m_protocol, this))
{}

VoltMeteersModel &App::voltMeterModel()
{
    return *m_model;
}

void App::testRequest()
{
    if(m_tcp_client->isConnected())
        m_client_handler->command("get_data\n");
}

void App::statusRequest(int id_channel)
{
    std::string command = "get_status channel";
    command += std::to_string(id_channel) + '\n';
    if(m_tcp_client->isConnected())
        m_client_handler->command(command);
}

void App::setRange(int channel_id, int range_id)
{
    std::string command = "set_range ";
    command += "channel" + std::to_string(channel_id) + ", ";
    command += "range" + std::to_string(range_id) + '\n';
    if(m_tcp_client->isConnected())
        m_client_handler->command(command);
}

void App::startMeasure(int channel_id)
{
    std::string command = "start_measure ";
    command += "channel" + std::to_string(channel_id) + "\n";
    if(m_tcp_client->isConnected()) {
        m_client_handler->command(command);
    }
}

void App::stopMeasure(int channel_id)
{
    std::string command = "stop_measure ";
    command += "channel" + std::to_string(channel_id) + "\n";
    if(m_tcp_client->isConnected())
        m_client_handler->command(command);
}

void App::timerEvent(QTimerEvent *)
{
    for(int i = 0; i < m_model->rowCount(); ++i) {
        if(m_model->status(i) == Channel::Status::measure_state) {
            m_channels.insert(i);
        } else {
            m_channels.erase(i);
        }
    }
    getResult();
}

void App::getResult()
{
    for(int id : m_channels) {
        std::string command = "get_result ";
        command += "channel" + std::to_string(id) + "\n";
        if(m_tcp_client->isConnected())
            m_client_handler->command(command);
    }
}

bool App::connection() const
{
    return m_tcp_client->isConnected();
}

void App::setConnection(bool is_connect)
{
    static int timer_id = -1;
    if(is_connect) {
        m_tcp_client->connect("127.0.0.1", "12345");
        timer_id = startTimer(1000);
    } else {
        m_tcp_client->disconnect();
        killTimer(timer_id);
        timer_id = -1;
    }

    emit connectionChanged();
}
