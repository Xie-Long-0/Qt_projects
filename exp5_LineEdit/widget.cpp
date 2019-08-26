#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QRegExp>
#include <QRegExpValidator>
#include <QCompleter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置密码框显示
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    //设置输入模板
    ui->lineEdit_MAC->setInputMask("HH:HH:HH:HH:HH:HH");
    ui->lineEdit_MAC->setText("00:00:00:00:00:00");

    //设置正则表达式校验器
    QRegExp re("[a-zA-Z][0-9a-zA-Z_]{16}");
    QRegExpValidator *reValidator = new QRegExpValidator(re);
    ui->lineEdit_username->setValidator(reValidator);

    //设置自动补全器
    QStringList listNickName;
    listNickName << "xielong" << "XieLong" << "Xie Long" << "XieLongMaster";
    QCompleter *cplNickName = new QCompleter(listNickName);
    cplNickName->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_NickName->setCompleter(cplNickName);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_confirm_clicked()
{
    if (ui->lineEdit_username->text().isEmpty() ||
            ui->lineEdit_password->text().isEmpty()) {

        QMessageBox::warning(this, tr("警告"), tr("用户名或密码为空！"));

        if (ui->lineEdit_username->text().isEmpty())
            ui->lineEdit_username->setFocus();
        else
            ui->lineEdit_password->setFocus();
        return;
    }

    username = ui->lineEdit_username->text();
    passwordHash = QCryptographicHash::hash(
                ui->lineEdit_password->text().toUtf8(),
                QCryptographicHash::Sha3_256);

    qDebug() << username;
    qDebug() << passwordHash.toHex();
    qDebug() << ui->lineEdit_MAC->text();

    QString strMsg = tr("用户名：");
    strMsg += username;
    strMsg += tr("\n密码Hash值：");
    strMsg += passwordHash.toHex();
    strMsg += tr("\n昵称：");
    strMsg += ui->lineEdit_NickName->text();
    strMsg += tr("\nMAC：");
    strMsg += ui->lineEdit_MAC->text();

    QMessageBox::information(this, tr("用户信息"), strMsg);
}

void Widget::on_pushButton_clear_clicked()
{
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_NickName->clear();
    ui->lineEdit_MAC->clear();
    ui->lineEdit_MAC->setText("00:00:00:00:00:00");
    ui->lineEdit_username->setFocus();
}
