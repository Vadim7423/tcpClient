#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "protocol.h"
#include "model/volt_meteers_model.h"
#include <string>

class ClientProtocol : public Protocol
{
public:
    ClientProtocol(VoltMeteersModel* model);
    void recieve(const std::string& str) override;

private:
    void initFuncs();
    void loadData(const std::string& params);
    void loadStatus(const std::string& params);
    void setRangeAnswer(const std::string& params);
    void setStartMeasureAnswer(const std::string& params);
    void setStopMeasureAnswer(const std::string& params);
    void getResultAnswer(const std::string& params);
    std::vector<std::string> getStrArray(const std::string& str);
    VoltMeteersModel* m_model = nullptr;
    std::unordered_map<std::string, void (ClientProtocol::*) (const std::string&)> m_funcs;

};

#endif // CLIENT_PROTOCOL_H
