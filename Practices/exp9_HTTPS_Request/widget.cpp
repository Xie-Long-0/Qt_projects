#include "widget.h"
#include "ui_widget.h"
#include "ui_sslerrors.h"

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

QT_REQUIRE_CONFIG(ssl);

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->sendRqstBtn, &QPushButton::clicked, this, &Widget::onSendRqstBtnClicked);
    connect(ui->clearBtn, &QPushButton::clicked, this, &Widget::onClearBtnClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onSendRqstBtnClicked()
{
    QUrl url(ui->urlComBox->currentText());
    qDebug() << url;
    if (!url.isValid())
    {
        QMessageBox::warning(this, tr("错误"), tr("地址无效！"));
        return;
    }

    QByteArray header = ui->headerTextEdit->toPlainText().toUtf8();
    qDebug() << header;

    QNetworkRequest request(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::AutoVerifyPeer);
    config.setProtocol(QSsl::TlsV1_3OrLater);   // use TLS v1.3 and higher

    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, header.length());

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    // set timeout
    request.setTransferTimeout(10000);
#endif

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, header);     // send post request

    ui->headerOutput->clear();
    ui->bodyOutput->clear();
    ui->sendRqstBtn->setEnabled(false);
    ui->clearBtn->setEnabled(false);
    ui->headerTextEdit->setEnabled(false);

    connect(manager, &QNetworkAccessManager::finished,
            this, &Widget::onPostFinished);
    connect(manager, &QNetworkAccessManager::sslErrors,
            this, &Widget::onSslError);
}

void Widget::onClearBtnClicked()
{
    ui->headerTextEdit->clear();
}

void Widget::onPostFinished(QNetworkReply *reply)
{
    // header
    auto headers = reply->rawHeaderPairs();
    for (auto &h : headers)
    {
        ui->headerOutput->append(h.first + ": " + h.second);
    }

    if (reply->error() == QNetworkReply::NoError)
    {
        int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (httpCode == 200)
        {
            ui->bodyOutput->setText(reply->readAll());
        }
        else
        {
            ui->bodyOutput->append(tr("HTTP Status is %1\n").arg(httpCode));
        }
    }
    else
    {
        ui->bodyOutput->append(reply->errorString());
    }
    
    ui->sendRqstBtn->setEnabled(true);
    ui->clearBtn->setEnabled(true);
    ui->headerTextEdit->setEnabled(true);
}

void Widget::onSslError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    QDialog errorDialog(this);
    Ui_SslErrors sslui;
    sslui.setupUi(&errorDialog);

    for (auto &error : errors)
    {
        sslui.sslErrorList->addItem(error.errorString());
    }

    if (errorDialog.exec() == QDialog::Accepted)
    {
        reply->ignoreSslErrors();
    }

    ui->sendRqstBtn->setEnabled(true);
    ui->clearBtn->setEnabled(true);
    ui->headerTextEdit->setEnabled(true);
}
