#include "STL_read.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    STL_read w;
    w.show();
    return a.exec();
}
