#include "client_protocol.h"
#include <QDebug>
#include <boost/algorithm/string.hpp>

ClientProtocol::ClientProtocol(VoltMeteersModel *model)
    : m_model(model)
{
    initFuncs();
}

void ClientProtocol::recieve(const std::string &str)
{
    size_t pos = str.find(' ');
    std::string command = str.substr(0, pos);
    std::string params;

    if(pos != str.npos)
        params = str.substr(pos + 1);

    if(m_funcs.count(command))
        (this->*m_funcs[command])(params);
}

void ClientProtocol::initFuncs()
{
    m_funcs["data"] = &ClientProtocol::loadData;
    m_funcs["get_status"] = &ClientProtocol::loadStatus;
    m_funcs["set_range"] = &ClientProtocol::setRangeAnswer;
    m_funcs["start_measure"] = &ClientProtocol::setStartMeasureAnswer;
    m_funcs["stop_measure"] = &ClientProtocol::setStopMeasureAnswer;
    m_funcs["get_result"] = &ClientProtocol::getResultAnswer;
}

void ClientProtocol::loadData(const std::string& params)
{
    m_model->clear();

    std::vector<std::string> tokens = getStrArray(params);
    int count = std::stoi(tokens.front());

    int counter = 1;
    for(int i = 0; i < count; ++i) {
        Channel::Status status = static_cast<Channel::Status>(
                std::stoi(tokens[counter++])
            );
        float low = std::stof(tokens[counter++]);
        float high = std::stof(tokens[counter++]);
        Range range(low, high);
        Channel* channel = new Channel(range);
        channel->setStatus(status);

        m_model->addItem(channel);
    }
}

void ClientProtocol::loadStatus(const std::string &params)
{
    std::vector<std::string> tokens = getStrArray(params);
    if(!tokens.empty() && tokens.front() == "ok") {
        std::string ch = "channel";
        std::string st = "status";
        int channel_id = std::stoi(tokens[1].substr(ch.size()));
        int status = std::stoi(tokens[2].substr(st.size()));
        m_model->setStatus(channel_id, static_cast<Channel::Status>(status));
    }
}

void ClientProtocol::setRangeAnswer(const std::string &params)
{
    std::vector<std::string> tokens = getStrArray(params);
    if(tokens[0] != "ok") {

        qDebug()  << "error range";
    }
}

void ClientProtocol::setStartMeasureAnswer(const std::string &params)
{
    std::vector<std::string> tokens = getStrArray(params);
    if(tokens[0] != "ok") {
        qDebug()  << "error start measure";
        std::string ch = "channel";
        int channel_id = std::stoi(tokens[1].substr(ch.size()));
        m_model->setStatus(channel_id, Channel::Status::idle_state);
    }
}

void ClientProtocol::setStopMeasureAnswer(const std::string &params)
{
    std::vector<std::string> tokens = getStrArray(params);
    if(tokens[0] != "ok") {
        qDebug()  << "error stop measure";
        std::string ch = "channel";
        int channel_id = std::stoi(tokens[1].substr(ch.size()));
        m_model->setStatus(channel_id, Channel::Status::measure_state);
    }
}

void ClientProtocol::getResultAnswer(const std::string &params)
{
    std::vector<std::string> tokens = getStrArray(params);
    if(tokens[0] == "ok") {
        std::string ch = "channel";
        int channel_id = std::stoi(tokens[1].substr(ch.size()));
        m_model->setValue(channel_id, std::stof(tokens[2]));
    }
}

std::vector<std::string> ClientProtocol::getStrArray(const std::string &str)
{
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(", "));
    tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const auto& item){
                     return item == "";
                 }), tokens.end());

    if(!tokens.empty() && tokens.back().back() == '\n') {
        tokens.back().pop_back();
    }

    return tokens;
}

