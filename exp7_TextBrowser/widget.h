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
    void on_textBrowser_backwardAvailable(bool arg1);

    void on_textBrowser_forwardAvailable(bool arg1);

    void on_textBrowser_textChanged();

    void on_pushButton_Open_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
