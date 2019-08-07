#include "widget.h"
#include <QApplication>
#include "showledsignal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    ShowLEDSignal s;

    QObject::connect(&w, &Widget::sendLEDsignal, &s, &ShowLEDSignal::showSignal);
    QObject::connect(&w, &Widget::sendAllSignals, &s, &ShowLEDSignal::showAllSignals);

    w.show();

    return a.exec();
}
