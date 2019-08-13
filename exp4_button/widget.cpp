#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pRadioRolesGroup = new QButtonGroup(this);
    pRadioRolesGroup->addButton(ui->radioBtnMaster, 0);
    pRadioRolesGroup->addButton(ui->radioBtnDoctor, 1);
    pRadioRolesGroup->addButton(ui->radioBtnBothMnD, 2);

    pRadioGenderGroup = new QButtonGroup(this);
    pRadioGenderGroup->addButton(ui->radioBtnMale, 0);
    pRadioGenderGroup->addButton(ui->radioBtnFemale, 1);
    pRadioGenderGroup->addButton(ui->radioBtnNonSex, 2);

    //NOTE: 要使用静态转换成int的信号
    connect(pRadioRolesGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this, &Widget::recvRolesID);
    connect(pRadioGenderGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this, &Widget::recvGenderID);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::recvRolesID(int id)
{
    switch (id) {
    case 0:
        qDebug() << tr("妈死塔");
        break;
    case 1:
        qDebug() << tr("刀客塔");
        break;
    case 2:
        qDebug() << tr("硕博连读");
        break;
    default:
        break;
    }
}

void Widget::recvGenderID(int id)
{
    switch (id) {
    case 0:
        qDebug() << tr("咕哒夫");
        break;
    case 1:
        qDebug() << tr("咕哒子");
        break;
    case 2:
        qDebug() << tr("博士人");
        break;
    default:
        break;
    }

}

void Widget::on_radioButton_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("吴克玩家");
    else
        qDebug() << tr("不是吴克玩家");
}

void Widget::on_radioButton_2_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("非洲玩家");
    else
        qDebug() << tr("不是非洲玩家");
}

void Widget::on_radioButton_3_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("海豹玩家");
    else
        qDebug() << tr("不是海豹玩家");
}

void Widget::on_radioButton_4_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("咸鱼玩家");
    else
        qDebug() << tr("不是咸鱼玩家");
}

void Widget::on_pushButton_clicked()
{
    QString strResult = "";

    int roleID = pRadioRolesGroup->checkedId();
    switch (roleID) {
    case 0:
        strResult += tr("角色：Master\n");
        break;
    case 1:
        strResult += tr("角色：Doctor\n");
        break;
    case 2:
        strResult += tr("角色：两个都是\n");
        break;
    default:
        strResult += tr("角色：未选中\n");
        break;
    }

    int genderID = pRadioGenderGroup->checkedId();
    switch (genderID) {
    case 0:
        strResult += tr("性别：藤丸\n");
        break;
    case 1:
        strResult += tr("性别：立香\n");
        break;
    case 2:
        strResult += tr("性别：未知\n");
        break;
    default:
        strResult += tr("性别：未选中\n");
        break;
    }

    if (ui->radioButton->isChecked()) {
        strResult += tr("类别：无氪玩家\n");
    }
    else if (ui->radioButton_2->isChecked()) {
        strResult += tr("类别：非洲玩家\n");
    }
    else if (ui->radioButton_3->isChecked()) {
        strResult += tr("类别：欧洲玩家\n");
    }
    else if (ui->radioButton_4->isChecked()) {
        strResult += tr("类别：咸鱼玩家\n");
    }
    else {
        strResult += tr("类别：未选中\n");
    }

    QMessageBox::information(this, tr("综合信息"), strResult);
}
