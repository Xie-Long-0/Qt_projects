#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QStyleOption>

#include "foldablewidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->left_vLayout->setAlignment(Qt::AlignTop);
    ui->right_vLayout->setAlignment(Qt::AlignTop);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Widget::on_left_addWidgetBtn_clicked()
{
    auto fw = new FoldableWidget(ui->left_frame);
    fw->setText(tr("Widget %1").arg(m_leftWidgets.size()));
    auto bt = new QPushButton("Btn");
    fw->addWidget(bt);
    ui->left_vLayout->addWidget(fw);
    m_leftWidgets.append(fw);
}

void Widget::on_left_removeWidgetBtn_clicked()
{
    if (!m_leftWidgets.isEmpty())
    {
        auto fw = m_leftWidgets.takeLast();
        fw->deleteLater();
    }
}

void Widget::on_right_addWidgetBtn_clicked()
{
    auto fw = new FoldableWidget(ui->right_frame);
    fw->setText(tr("Widget %1").arg(m_rightWidgets.size()));
    fw->setAltIconVisible(false);
    auto cw = fw->contentWidget();
    auto cl = fw->contentBoxLayout();
    auto bt = new QPushButton(tr("Button"), cw);
    cl->addWidget(bt);
    ui->right_vLayout->addWidget(fw);
    m_rightWidgets.append(fw);
}

void Widget::on_right_removeWidgetBtn_clicked()
{
    if (!m_rightWidgets.isEmpty())
    {
        auto fw = m_rightWidgets.takeLast();
        fw->deleteLater();
    }
}
