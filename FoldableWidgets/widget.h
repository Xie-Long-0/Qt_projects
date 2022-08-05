#pragma once

#include <QWidget>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *) override;

private slots:
    void on_left_addWidgetBtn_clicked();
    void on_left_removeWidgetBtn_clicked();
    void on_right_addWidgetBtn_clicked();
    void on_right_removeWidgetBtn_clicked();

private:
    Ui::Widget *ui;
    QList<QWidget *> m_leftWidgets;
    QList<QWidget *> m_rightWidgets;
};
