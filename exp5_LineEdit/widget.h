#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_confirm_clicked();
    void on_pushButton_clear_clicked();

private:
    Ui::Widget *ui;

    QString username;
    QByteArray passwordHash;
};

#endif // WIDGET_H
