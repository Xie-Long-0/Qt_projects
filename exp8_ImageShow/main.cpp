#include "widget.h"
#include <QApplication>

#include <QPixmap>
#include <QIcon>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    QIcon icon(":icon");
    a.setWindowIcon(icon);
    w.setWindowIcon(icon);

    QPixmap pixSplash(":splash");
    pixSplash = pixSplash.scaled(300, 300);

    //创建闪屏
    QSplashScreen splash(pixSplash);
    //显示闪屏和提示信息
    splash.show();
    splash.showMessage(QObject::tr("1+1=⑨"), Qt::AlignBottom | Qt::AlignHCenter);

    //启动应用程序的事件处理
    a.processEvents();

    w.thread()->sleep(1);
    w.show();

    //主窗体显示后结束闪屏
    splash.finish(&w);

    return a.exec();
}
