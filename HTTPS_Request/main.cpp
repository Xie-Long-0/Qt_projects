#include "widget.h"

#include <QApplication>
#include <QMessageBox>
#include <QtNetwork>

QT_REQUIRE_CONFIG(ssl);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSslSocket::supportsSsl())
    {
        QMessageBox::information(nullptr, "Secure Socket Client",
                                 "This system does not support TLS.");
        return -1;
    }

    Widget w;
    w.show();
    return a.exec();
}
