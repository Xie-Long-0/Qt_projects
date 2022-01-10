#include "tcpserver.h"
#include <QTcpSocket>
#include <QUrl>

// 控制单片机LED灯
#define RLED_ON system("echo 255 > /sys/class/leds/red/brightness")
#define RLED_OFF system("echo 0 > /sys/class/leds/red/brightness")
#define GLED_ON system("echo 255 > /sys/class/leds/green/brightness")
#define GLED_OFF system("echo 0 > /sys/class/leds/green/brightness")
#define BLED_ON system("echo 255 > /sys/class/leds/blue/brightness")
#define BLED_OFF system("echo 0 > /sys/class/leds/blue/brightness")

#define ON_TEST 1   // 测试模式

TcpServer::TcpServer(bool no_led, QObject *parent) : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
#if ON_TEST
    m_noLED = true;
#else
    m_noLED = no_led;
#endif
    connect(m_tcpServer, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

TcpServer::~TcpServer()
{
    stopListen();
}

bool TcpServer::startListen(quint16 port)
{
    if (!m_tcpServer->listen(QHostAddress::Any, port))
    {
        qDebug() << m_tcpServer->errorString();
        return false;
    }
    return true;
}

void TcpServer::stopListen()
{
    // 关闭每个连接
    for (auto &tcp : m_tcpClientList)
    {
        if (tcp)
        {
            tcp->close();
            tcp->deleteLater();
        }
    }
    m_tcpClientList.clear();
    m_tcpServer->close();
}

void TcpServer::onReceiveData()
{
    // 获取发送此信号的对象
    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket *>(sender());
    if (tcpSocket == nullptr)
    {
        qDebug() << __FUNCTION__ << "qobject_cast returns nullptr";
        return;
    }

    qDebug().nospace().noquote() << tcpSocket->peerAddress().toString() << ":" << tcpSocket->peerPort() << " >>";

    //NOTE: 接收的数据没有换行符时不会进入canReadLine函数
    while (tcpSocket->canReadLine())
    {
        auto data = tcpSocket->readLine();
        if (!m_noLED)
        {
            if (data == "RLED_ON\r\n")
            {
                RLED_ON;
            }
            else if (data == "RLED_OFF\r\n")
            {
                RLED_OFF;
            }
            else if (data == "BLED_ON\r\n")
            {
                BLED_ON;
            }
            else if (data == "BLED_OFF\r\n")
            {
                BLED_OFF;
            }
            else if (data == "GLED_ON\r\n")
            {
                GLED_ON;
            }
            else if (data == "GLED_OFF\r\n")
            {
                GLED_OFF;
            }
        }
        qDebug() << data;
    }
}

void TcpServer::onNewConnection()
{
    // 获取传入连接的对象
    auto tcpSocket = m_tcpServer->nextPendingConnection();
    if (tcpSocket == nullptr) return;
    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::onReceiveData);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnect);
    // 将主机地址和端口号作为Hash键值存入列表
    QUrl host;
    host.setHost(tcpSocket->peerAddress().toString());
    host.setPort(tcpSocket->peerPort());
    m_tcpClientList.insert(host.toString(), tcpSocket);
    qDebug() << "New client:" << host.toString();
}

void TcpServer::onDisconnect()
{
    // 获取发送此信号的对象
    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket *>(sender());
    if (tcpSocket == nullptr)
    {
        qDebug() << __FUNCTION__ << "qobject_cast returns nullptr";
        return;
    }

    QUrl host;
    host.setHost(tcpSocket->peerAddress().toString());
    host.setPort(tcpSocket->peerPort());
    // 删除对应键值的元素
    m_tcpClientList.remove(host.toString());
    tcpSocket->deleteLater();
    qDebug() << "Client disconnected:" << host.toString();
}
