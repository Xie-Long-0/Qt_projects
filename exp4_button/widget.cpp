#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>

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

    //设置三态复选框
    ui->checkBoxGame->setTristate(true);
    ui->checkBoxMusic->setTristate(true);
    ui->checkBoxComic->setTristate(true);
    ui->checkBoxProgram->setTristate(true);
}

Widget::~Widget()
{
    delete ui;
}

int Widget::checkGames() const
{
    int count = 0;
    if (ui->checkBoxGameArknights->isChecked())
        count++;
    if (ui->checkBoxGameFate->isChecked())
        count++;
    if (ui->checkBoxGameTouhou->isChecked())
        count++;

    if (count <= 0)
        ui->checkBoxGame->setCheckState(Qt::Unchecked);
    else if (count >= 3)
        ui->checkBoxGame->setCheckState(Qt::Checked);
    else
        ui->checkBoxGame->setCheckState(Qt::PartiallyChecked);

    return count;
}

int Widget::checkMusics() const
{
    int count = 0;
    if (ui->checkBoxMusicJayChou->isChecked())
        count++;
    if (ui->checkBoxMusicTouhou->isChecked())
        count++;
    if (ui->checkBoxMusicVae->isChecked())
        count++;

    if (count <= 0)
        ui->checkBoxMusic->setCheckState(Qt::Unchecked);
    else if (count >= 3)
        ui->checkBoxMusic->setCheckState(Qt::Checked);
    else
        ui->checkBoxMusic->setCheckState(Qt::PartiallyChecked);

    return count;
}

int Widget::checkComics() const
{
    int count = 0;
    if (ui->checkBoxComicConan->isChecked())
        count++;
    if (ui->checkBoxComicFate->isChecked())
        count++;
    if (ui->checkBoxComicKaguya->isChecked())
        count++;

    if (count <= 0)
        ui->checkBoxComic->setCheckState(Qt::Unchecked);
    else if (count >= 3)
        ui->checkBoxComic->setCheckState(Qt::Checked);
    else
        ui->checkBoxComic->setCheckState(Qt::PartiallyChecked);

    return count;
}

int Widget::checkPrograms() const
{
    int count = 0;
    if (ui->checkBoxProgramC->isChecked())
        count++;
    if (ui->checkBoxProgramJava->isChecked())
        count++;
    if (ui->checkBoxProgramPython->isChecked())
        count++;

    if (count <= 0)
        ui->checkBoxProgram->setCheckState(Qt::Unchecked);
    else if (count >= 3)
        ui->checkBoxProgram->setCheckState(Qt::Checked);
    else
        ui->checkBoxProgram->setCheckState(Qt::PartiallyChecked);

    return count;
}

void Widget::recvRolesID(int id)
{
    switch (id) {
    case 0:
        qDebug() << tr("骂死塔");
        break;
    case 1:
        qDebug() << tr("刀客塔");
        break;
    case 2:
        qDebug() << tr("Kono DIO da!");
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

//综合显示
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

    if (ui->radioButton->isChecked())
        strResult += tr("类别：无氪玩家\n");
    else if (ui->radioButton_2->isChecked())
        strResult += tr("类别：非洲玩家\n");
    else if (ui->radioButton_3->isChecked())
        strResult += tr("类别：欧洲玩家\n");
    else if (ui->radioButton_4->isChecked())
        strResult += tr("类别：咸鱼玩家\n");
    else
        strResult += tr("类别：未选中\n");

    strResult += tr("喜欢的东西：");
    int count = 0;
    if (ui->checkBoxGame->checkState() > 0) {
        strResult += tr("游戏 ");
        count++;
    }
    if (ui->checkBoxMusic->checkState() > 0) {
        strResult += tr("音乐 ");
        count++;
    }
    if (ui->checkBoxComic->checkState() > 0) {
        strResult += tr("动漫 ");
        count++;
    }
    if (ui->checkBoxProgram->checkState() > 0) {
        strResult += tr("编程");
        count++;
    }
    if (0 == count)
        strResult += tr("未选中");

    QMessageBox::information(this, tr("综合信息"), strResult);
}

void Widget::on_checkBoxGameFate_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("Fate系列游戏");
    checkGames();
}

void Widget::on_checkBoxGameTouhou_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("东方系列游戏");
    checkGames();
}

void Widget::on_checkBoxGameArknights_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("明日方舟");
    checkGames();
}

void Widget::on_checkBoxMusicTouhou_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("东方系列音乐");
    checkMusics();
}

void Widget::on_checkBoxMusicVae_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("许嵩的歌曲");
    checkMusics();
}

void Widget::on_checkBoxMusicJayChou_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("周董的歌曲");
    checkMusics();
}

void Widget::on_checkBoxComicFate_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("Fate系列动漫");
    checkComics();
}

void Widget::on_checkBoxComicKaguya_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("辉夜大小姐想让我告白～");
    checkComics();
}

void Widget::on_checkBoxComicConan_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("名侦探柯南");
    checkComics();
}

void Widget::on_checkBoxProgramC_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("C/C++");
    checkPrograms();
}

void Widget::on_checkBoxProgramJava_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("Java");
    checkPrograms();
}

void Widget::on_checkBoxProgramPython_toggled(bool checked)
{
    if (checked)
        qDebug() << tr("Python");
    checkPrograms();
}

void Widget::on_cmdLinkButtonHome_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///home/xielong"));
}

void Widget::on_cmdLinkButtonGoogle_clicked()
{
    QDesktopServices::openUrl(QUrl("https://google.com"));
}

void Widget::on_checkBoxGame_stateChanged(int arg1)
{
    switch (arg1) {
    case 0:
        ui->checkBoxGameArknights->setChecked(false);
        ui->checkBoxGameFate->setChecked(false);
        ui->checkBoxGameTouhou->setChecked(false);
        break;
    case 1:
        if (checkGames() <= 0)
            ui->checkBoxGameFate->setChecked(true);
        break;
    case 2:
        ui->checkBoxGameArknights->setChecked(true);
        ui->checkBoxGameFate->setChecked(true);
        ui->checkBoxGameTouhou->setChecked(true);
        break;
    default:
        break;
    }
}

void Widget::on_checkBoxMusic_stateChanged(int arg1)
{
    switch (arg1) {
    case 0:
        ui->checkBoxMusicJayChou->setChecked(false);
        ui->checkBoxMusicTouhou->setChecked(false);
        ui->checkBoxMusicVae->setChecked(false);
        break;
    case 1:
        if (checkMusics() <= 0)
            ui->checkBoxMusicTouhou->setChecked(true);
        break;
    case 2:
        ui->checkBoxMusicJayChou->setChecked(true);
        ui->checkBoxMusicTouhou->setChecked(true);
        ui->checkBoxMusicVae->setChecked(true);
        break;
    default:
        break;
    }
}

void Widget::on_checkBoxComic_stateChanged(int arg1)
{
    switch (arg1) {
    case 0:
        ui->checkBoxComicConan->setChecked(false);
        ui->checkBoxComicFate->setChecked(false);
        ui->checkBoxComicKaguya->setChecked(false);
        break;
    case 1:
        if (checkComics() <= 0)
            ui->checkBoxComicFate->setChecked(true);
        break;
    case 2:
        ui->checkBoxComicConan->setChecked(true);
        ui->checkBoxComicFate->setChecked(true);
        ui->checkBoxComicKaguya->setChecked(true);
        break;
    default:
        break;
    }
}

void Widget::on_checkBoxProgram_stateChanged(int arg1)
{
    switch (arg1) {
    case 0:
        ui->checkBoxProgramC->setChecked(false);
        ui->checkBoxProgramJava->setChecked(false);
        ui->checkBoxProgramPython->setChecked(false);
        break;
    case 1:
        if (checkPrograms() <= 0)
            ui->checkBoxProgramC->setChecked(true);
        break;
    case 2:
        ui->checkBoxProgramC->setChecked(true);
        ui->checkBoxProgramJava->setChecked(true);
        ui->checkBoxProgramPython->setChecked(true);
        break;
    default:
        break;
    }
}
