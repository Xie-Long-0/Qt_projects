#pragma once

#include <QObject>
#include <QTcpServer>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(bool no_led = false, QObject *parent = nullptr);
    ~TcpServer();

    bool startListen(quint16 port);
    void stopListen();

private slots:
    void onReceiveData();
    void onNewConnection();
    void onDisconnect();

private:
    QTcpServer *m_tcpServer = nullptr;
    QHash<QString, QTcpSocket *> m_tcpClientList;
    bool m_noLED = false;
};

