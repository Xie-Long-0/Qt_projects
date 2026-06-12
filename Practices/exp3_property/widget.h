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

    Q_CLASSINFO("Version", "beta1")
    Q_CLASSINFO("Author", "XieLong")
    Q_CLASSINFO("Date", "2019-8-3")

public slots:
    void labelShowNickName(const QString &strNickName);
    void labelShowCount(int nCount);
    void labelShowValue(double dbValue);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
