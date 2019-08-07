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

public slots:
    void printText(const QString &text);
    void whoAmI();

private slots:
    void on_pB_lineEditEnable_clicked();
    void on_pB_lineEditDisable_clicked();
    void on_pB_labelConn_clicked();
    void on_pB_labelDiscon_clicked();
    void on_pB_textbConn_clicked();
    void on_pB_textbDiscon_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
