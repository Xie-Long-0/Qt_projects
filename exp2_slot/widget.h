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

signals:
    void sendLEDsignal(QString str);
    void sendAllSignals();

private slots:
    void on_pB_RedSignal_clicked();
    void on_pB_YellowSignal_clicked();
    void on_pB_GreenSignal_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
