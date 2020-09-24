#include "widget.h"
#include "ui_widget.h"
#include "ui_sslerrors.h"

#include <QtNetwork>
#include <QDialog>

#include <QDebug>

QT_REQUIRE_CONFIG(ssl);

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_sendRqstBtn_clicked()
{
    QUrl url(ui->urlComBox->currentText());
    url.setPort(ui->portSpinBox->value());
    qDebug() << url.toString();

    QByteArray body = ui->requestEdit->text().toUtf8();

    QNetworkRequest request(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyPeer);
    config.setProtocol(QSsl::TlsV1_3);

    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, body.length());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, body);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Widget::onPostFinished);
    connect(manager, &QNetworkAccessManager::sslErrors,
            this, &Widget::onSslError);
}

void Widget::onPostFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (httpCode == 200)
        {
            ui->textBrowser->append(reply->readAll());
        }
        else
        {
            ui->textBrowser->append(tr("HTTP Status is %1\n").arg(httpCode));
        }
    }
    else
    {
        ui->textBrowser->append(reply->errorString());
    }
}

void Widget::onSslError(QNetworkReply *reply, const QList<QSslError> errors)
{
    QDialog errorDialog(this);
    Ui_SslErrors ui;
    ui.setupUi(&errorDialog);

    for (const auto &error : errors)
    {
        ui.sslErrorList->addItem(error.errorString());
    }

    if (errorDialog.exec() == QDialog::Accepted)
    {
        reply->ignoreSslErrors();
    }
}
