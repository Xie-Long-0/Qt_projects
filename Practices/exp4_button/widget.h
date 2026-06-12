#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //检查三态复选框
    int checkGames() const;
    int checkMusics() const;
    int checkComics() const;
    int checkPrograms() const;

public slots:
    void recvRolesID(int id);
    void recvGenderID(int id);

private slots:
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void on_radioButton_4_toggled(bool checked);

    void on_pushButton_clicked();

    void on_checkBoxGameFate_toggled(bool checked);
    void on_checkBoxGameTouhou_toggled(bool checked);
    void on_checkBoxGameArknights_toggled(bool checked);
    void on_checkBoxMusicTouhou_toggled(bool checked);
    void on_checkBoxMusicVae_toggled(bool checked);
    void on_checkBoxMusicJayChou_toggled(bool checked);
    void on_checkBoxComicFate_toggled(bool checked);
    void on_checkBoxComicKaguya_toggled(bool checked);
    void on_checkBoxComicConan_toggled(bool checked);
    void on_checkBoxProgramC_toggled(bool checked);
    void on_checkBoxProgramJava_toggled(bool checked);
    void on_checkBoxProgramPython_toggled(bool checked);

    void on_cmdLinkButtonHome_clicked();
    void on_cmdLinkButtonGoogle_clicked();

    void on_checkBoxGame_stateChanged(int arg1);
    void on_checkBoxMusic_stateChanged(int arg1);
    void on_checkBoxComic_stateChanged(int arg1);
    void on_checkBoxProgram_stateChanged(int arg1);

private:
    Ui::Widget *ui;
    //按钮分组
    QButtonGroup *pRadioRolesGroup;
    QButtonGroup *pRadioGenderGroup;
};

#endif // WIDGET_H
