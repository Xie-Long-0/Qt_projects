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
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void printText(const QString &text);

private slots:
    void onLineEditEnableBtnClicked();
    void onLineEditDisableBtnClicked();
    void onLabelConnectBtnClicked();
    void onLabelDisconnectBtnClicked();
    void onTextBrsConnectBtnClicked();
    void onTextBrsDisconnectBtnClicked();
    void whoAmI();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
