#include "widget.h"

#include <QApplication>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap)0));
    Widget w;
    w.show();
    return a.exec();
}
