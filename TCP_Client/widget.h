#pragma once

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_link_clicked();
    void on_bLed_on_clicked();
    void on_bLed_off_clicked();
    void on_gLed_on_clicked();
    void on_gLed_off_clicked();
    void on_rLed_on_clicked();
    void on_rLed_off_clicked();
    void onSocketError(QTcpSocket::SocketError error);

private:
    Ui::Widget *ui;

    QTcpSocket *m_tcpSocket = nullptr;
};
