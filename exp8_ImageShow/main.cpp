#include "widget.h"
#include <QApplication>

#include <QPixmap>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    QPixmap pixSplash(":/resource/splash.jpg");
    pixSplash = pixSplash.scaled(w.size());

    //创建闪屏
    QSplashScreen splash(pixSplash);
    splash.setGeometry(w.geometry());
    //显示闪屏和提示信息
    splash.show();      //NOTE: 本人在 qt5.9.5 on Ubuntu 18.04下运行时splash只显示一个透明矩形，
                        //      并在最后一瞬才显示图片，具体原因暂不明。
    splash.showMessage(QObject::tr("先看一下老婆～"), Qt::AlignBottom|Qt::AlignHCenter);

    //启动应用程序的事件处理
    a.processEvents();

    w.thread()->sleep(3);
    w.show();

    //主窗体显示后结束闪屏
    splash.finish(&w);

    return a.exec();
}
