#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkReply>
#include <QSslError>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onSendRqstBtnClicked();
    void onClearBtnClicked();
    void onPostFinished(QNetworkReply *reply);
    void onSslError(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
