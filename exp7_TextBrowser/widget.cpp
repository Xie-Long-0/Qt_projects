#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QUrl>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启用自带浏览器打开外部链接
    ui->textBrowser->setOpenLinks(true);

    //设置只读
    ui->plainTextEdit->setReadOnly(true);

    ui->pushButton_Backward->setEnabled(false);
    ui->pushButton_Forward->setEnabled(false);

    //关联前进后退刷新信号
    connect(ui->pushButton_Backward, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::backward);
    connect(ui->pushButton_Forward, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::forward);
    connect(ui->pushButton_Reflash, &QPushButton::clicked, ui->textBrowser, &QTextBrowser::reload);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_textBrowser_backwardAvailable(bool arg1)
{
    ui->pushButton_Backward->setEnabled(arg1);
}

void Widget::on_textBrowser_forwardAvailable(bool arg1)
{
    ui->pushButton_Forward->setEnabled(arg1);
}

void Widget::on_textBrowser_textChanged()
{
    ui->plainTextEdit->setPlainText(ui->textBrowser->toHtml());
}

void Widget::on_pushButton_Open_clicked()
{
    QUrl file = QFileDialog::getOpenFileUrl(this, tr("打开HTML文件"), QUrl(),
                                            "HTML files(*.htm *.html);;Text files(*.txt *.md)");
    if (! file.isEmpty()) {
        qDebug() << file;
        ui->textBrowser->setSource(file);
    }
}
