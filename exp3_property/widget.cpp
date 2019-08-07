#include "widget.h"
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

void Widget::labelShowNickName(const QString &strNickName)
{
    ui->label_NickName->setText(strNickName);
}

void Widget::labelShowCount(int nCount)
{
    QString txt;
    ui->label_Count->setText(txt.setNum(nCount));
}

void Widget::labelShowValue(double dbValue)
{
    QString txt;
    ui->label_Value->setText(txt.setNum(dbValue));
}
