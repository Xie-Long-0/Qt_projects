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

public slots:
    void recvRolesID(int id);
    void recvGenderID(int id);

private slots:
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void on_radioButton_4_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    //按钮分组
    QButtonGroup *pRadioRolesGroup;
    QButtonGroup *pRadioGenderGroup;
};

#endif // WIDGET_H
