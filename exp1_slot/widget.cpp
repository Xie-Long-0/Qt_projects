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
    on_pB_lineEditEnable_clicked();
    //关联Label
    on_pB_labelConn_clicked();
    //关联TextBrowser
    on_pB_textbConn_clicked();

    connect(ui->lineEdit, &QLineEdit::textEdited, this, &Widget::printText);

    connect(ui->pB_Archer, &QPushButton::clicked, this, &Widget::whoAmI);
    connect(ui->pB_Berserker, &QPushButton::clicked, this, &Widget::whoAmI);
    connect(ui->pB_Caster, &QPushButton::clicked, this, &Widget::whoAmI);
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
    QString objName = this->sender()->objectName();
    qDebug() << objName;

    QString strMsg;
    if (objName == "pB_Archer") {
        strMsg = tr("Hello, I am Archer!");
    }
    else if (objName == "pB_Berserker") {
        strMsg = tr("Hello, I am Berserker!");
    }
    else if (objName == "pB_Caster") {
        strMsg = tr("Hello, I am Caster!");
    }
    else return;

    qDebug() << strMsg;
    QMessageBox::information(this, tr("Who am I"), strMsg);
}

void Widget::on_pB_lineEditEnable_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->pB_lineEditEnable->setEnabled(false);
    ui->pB_lineEditDisable->setEnabled(true);
}

void Widget::on_pB_lineEditDisable_clicked()
{
    ui->lineEdit->setEnabled(false);
    ui->pB_lineEditEnable->setEnabled(true);
    ui->pB_lineEditDisable->setEnabled(false);
}

void Widget::on_pB_labelConn_clicked()
{
    connect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);
    ui->pB_labelConn->setEnabled(false);
    ui->pB_labelDiscon->setEnabled(true);
}

void Widget::on_pB_labelDiscon_clicked()
{
    disconnect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);
    ui->pB_labelConn->setEnabled(true);
    ui->pB_labelDiscon->setEnabled(false);
}

void Widget::on_pB_textbConn_clicked()
{
    connect(ui->lineEdit, &QLineEdit::textEdited, ui->textBrowser, &QTextBrowser::setText);
    ui->pB_textbConn->setEnabled(false);
    ui->pB_textbDiscon->setEnabled(true);
}

void Widget::on_pB_textbDiscon_clicked()
{
    disconnect(ui->lineEdit, &QLineEdit::textEdited, ui->textBrowser, &QTextBrowser::setText);
    ui->pB_textbConn->setEnabled(true);
    ui->pB_textbDiscon->setEnabled(false);
}
