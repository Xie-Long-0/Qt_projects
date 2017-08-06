#include "widget.h"
#include <QMessageBox>
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_pushButton_clicked()
{
    //QMessageBox::information(this, tr("O的K"), tr("我觉得不行"));
//  QMessageBox *msg = new QMessageBox(this);
//  msg->setWindowTitle("Alert");
//  msg->setText("我觉得还行");
//  msg->setBaseSize(320, 240);
//  msg->setButtonText(1, tr("不行"));
//  msg->exec();
  QMessageBox msg(this);
  msg.setWindowTitle("Alert");
  msg.setText("我觉得还行");
  msg.setBaseSize(320,480);
  msg.setButtonText(1,"不行");
  msg.exec();
}
