#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 预设命令行选项
    QCommandLineParser cmdparser;
    cmdparser.setApplicationDescription(QObject::tr("TCP server for LED lighting."));
    cmdparser.addHelpOption();

    // 添加端口参数
    QCommandLineOption portOption({"p", "port"}, QObject::tr("Server port in [0-65534]"), "port");
    cmdparser.addOption(portOption);

    // 添加无LED参数选项
    QCommandLineOption offlineOption("no-led", QObject::tr("Run in machine without LED"));
    cmdparser.addOption(offlineOption);

    // 处理程序输入参数
    cmdparser.process(a);

    quint16 port = 6666;
    // 判断是否存在port参数
    if (cmdparser.isSet(portOption))
    {
        auto strport = cmdparser.value(portOption);
        bool ok = false;
        port = strport.toUShort(&ok);
        if (!ok)
        {
            qDebug() << "Invalid port argument";
            a.quit();
            return a.exec();
        }
    }

    // 判断是否在无LED设备上运行
    bool noled = cmdparser.isSet(offlineOption);

    TcpServer server(noled);
    if (server.startListen(port))
    {
        qDebug() << "Listen on port:" << port;
    }
    else
    {
        qDebug() << "Failed to listen port" << port;
        a.quit();
    }

    return a.exec();
}
