#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pB_AllSignal, &QPushButton::clicked, this, &Widget::sendAllSignals);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pB_RedSignal_clicked()
{
    emit sendLEDsignal(tr("红灯亮了"));
}

void Widget::on_pB_YellowSignal_clicked()
{
    emit sendLEDsignal(tr("黄灯亮了"));
}

void Widget::on_pB_GreenSignal_clicked()
{
    emit sendLEDsignal(tr("绿灯亮了"));
}
