#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启用LineEdit编辑
    onLineEditEnableBtnClicked();
    //关联Label
    onLabelConnectBtnClicked();
    //关联TextBrowser
    onTextBrsConnectBtnClicked();

    // 连接按钮点击信号
    connect(ui->lineEditEnableBtn, &QPushButton::clicked, this, &Widget::onLineEditEnableBtnClicked);
    connect(ui->lineEditDisableBtn, &QPushButton::clicked, this, &Widget::onLineEditDisableBtnClicked);
    connect(ui->labelConnectBtn, &QPushButton::clicked, this, &Widget::onLabelConnectBtnClicked);
    connect(ui->labelDisconnectBtn, &QPushButton::clicked, this, &Widget::onLabelDisconnectBtnClicked);
    connect(ui->textBrsConnectBtn, &QPushButton::clicked, this, &Widget::onTextBrsConnectBtnClicked);
    connect(ui->textBrsDisconnectBtn, &QPushButton::clicked, this, &Widget::onTextBrsDisconnectBtnClicked);

    connect(ui->lineEdit, &QLineEdit::textEdited, this, &Widget::printText);

    // 多个信号连接到同一个槽函数
    connect(ui->ArcherBtn, &QPushButton::clicked, this, &Widget::whoAmI);
    connect(ui->BerserkerBtn, &QPushButton::clicked, this, &Widget::whoAmI);
    connect(ui->CasterBtn, &QPushButton::clicked, this, &Widget::whoAmI);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::printText(const QString &text)
{
    qDebug() << text;
}

void Widget::whoAmI()
{
    // 槽函数可以通过sender()获取发送对应信号的对象指针
    auto obj = this->sender();
    qDebug() << obj->objectName();

    QString strMsg;
    if (obj == ui->ArcherBtn) {
        strMsg = tr("Hello, I am Archer!");
    }
    else if (obj == ui->BerserkerBtn) {
        strMsg = tr("Hello, I am Berserker!");
    }
    else if (obj == ui->CasterBtn) {
        strMsg = tr("Hello, I am Caster!");
    }
    else return;

    qDebug() << strMsg;
    QMessageBox::information(this, tr("Who am I"), strMsg);
}

void Widget::onLineEditEnableBtnClicked()
{
    ui->lineEdit->setEnabled(true);
    ui->lineEditEnableBtn->setEnabled(false);
    ui->lineEditDisableBtn->setEnabled(true);
}

void Widget::onLineEditDisableBtnClicked()
{
    ui->lineEdit->setEnabled(false);
    ui->lineEditEnableBtn->setEnabled(true);
    ui->lineEditDisableBtn->setEnabled(false);
}

void Widget::onLabelConnectBtnClicked()
{
    // 连接信号槽
    connect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);
    ui->labelConnectBtn->setEnabled(false);
    ui->labelDisconnectBtn->setEnabled(true);
}

void Widget::onLabelDisconnectBtnClicked()
{
    // 断开相应信号槽的连接
    disconnect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);
    ui->labelConnectBtn->setEnabled(true);
    ui->labelDisconnectBtn->setEnabled(false);
}

void Widget::onTextBrsConnectBtnClicked()
{
    connect(ui->lineEdit, &QLineEdit::textEdited, ui->textBrowser, &QTextBrowser::setText);
    ui->textBrsConnectBtn->setEnabled(false);
    ui->textBrsDisconnectBtn->setEnabled(true);
}

void Widget::onTextBrsDisconnectBtnClicked()
{
    disconnect(ui->lineEdit, &QLineEdit::textEdited, ui->textBrowser, &QTextBrowser::setText);
    ui->textBrsConnectBtn->setEnabled(true);
    ui->textBrsDisconnectBtn->setEnabled(false);
}
