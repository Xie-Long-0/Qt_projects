#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
    if (m_tcpSocket)
    {
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
    }
}

void Widget::on_link_clicked()
{
    // 关闭连接
    if (m_tcpSocket && m_tcpSocket->isOpen())
    {
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
        m_tcpSocket = nullptr;
        ui->link->setText(tr("CONNECT"));
        ui->statusLabel->setText(tr("连接已断开"));
        ui->addressEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
        return;
    }

    QHostAddress addr(ui->addressEdit->text());
    if (addr.isNull())
    {
        QMessageBox::warning(this, tr("错误"), tr("服务器地址无效！"));
        ui->link->setText(tr("CONNECT"));
        ui->statusLabel->setText(tr("连接已断开"));
        ui->addressEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
        return;
    }

    // 新建连接
    if (m_tcpSocket)
    {
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
    }
    m_tcpSocket = new QTcpSocket(this);

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    connect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &Widget::onSocketError);
#else
    connect(m_tcpSocket, &QTcpSocket::errorOccurred, this, &Widget::onSocketError);
#endif

    connect(m_tcpSocket, &QTcpSocket::connected, this, [=](){
        ui->link->setText(tr("DISCONNECT"));
        ui->statusLabel->setText(tr("已连接"));
        ui->link->setEnabled(true);
    });
    
    m_tcpSocket->connectToHost(addr, ui->portSpinBox->value());
    // 设置按钮状态
    ui->link->setText(tr("CONNECTING"));
    ui->statusLabel->setText(tr("连接中..."));
    ui->link->setEnabled(false);
    // 禁用输入框
    ui->addressEdit->setEnabled(false);
    ui->portSpinBox->setEnabled(false);
}

void Widget::on_bLed_on_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("BLED_ON\r\n");
        qDebug() << "BLED_ON";
    }
}

void Widget::on_bLed_off_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("BLED_OFF\r\n");
        qDebug() << "BLED_OFF";
    }
}

void Widget::on_gLed_on_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("GLED_ON\r\n");
        qDebug() << "GLED_ON";
    }
}

void Widget::on_gLed_off_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("GLED_OFF\r\n");
        qDebug() << "GLED_OFF";
    }
}

void Widget::on_rLed_on_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("RLED_ON\r\n");
        qDebug() << "RLED_ON";
    }
}

void Widget::on_rLed_off_clicked()
{
    if (m_tcpSocket && m_tcpSocket->isWritable())
    {
        m_tcpSocket->write("RLED_OFF\r\n");
        qDebug() << "RLED_OFF";
    }
}

void Widget::onSocketError(QAbstractSocket::SocketError error)
{
    if (m_tcpSocket)
    {
        QMessageBox::warning(this, tr("连接出错"), QString::number(error).append(": " + m_tcpSocket->errorString()));
        qDebug() << error << m_tcpSocket->errorString();
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
        m_tcpSocket = nullptr;
        ui->link->setText(tr("CONNECT"));
        ui->statusLabel->setText(tr("连接已断开"));
        ui->link->setEnabled(true);
        ui->addressEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
    }
}
