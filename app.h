#ifndef APP_H
#define APP_H

#include "tcp/boost_tcp_client.h"
#include "protocol/client_protocol.h"
#include <set>

#include <QObject>

class Protocol;
class ClientHandler;
class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connection READ connection WRITE setConnection NOTIFY connectionChanged FINAL)
public:
    explicit App(QObject *parent = nullptr);
    VoltMeteersModel& voltMeterModel();

public slots:
    void testRequest();
    void statusRequest(int id_channel);
    void setRange(int channel_id, int range_id);
    void startMeasure(int channel_id);
    void stopMeasure(int channel_id);

signals:
    void connectionChanged();

private:
    void timerEvent(QTimerEvent*) override;
    void getResult();
    bool connection() const;
    void setConnection(bool is_connect);
    std::unique_ptr<TcpClient> m_tcp_client;
    VoltMeteersModel* m_model = nullptr;
    std::unique_ptr<Protocol> m_protocol;
    ClientHandler* m_client_handler = nullptr;
    std::set<int> m_channels;

};

#endif // APP_H
