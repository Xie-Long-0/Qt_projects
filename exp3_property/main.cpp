#include "widget.h"
#include <QApplication>
#include "propertychang.h"
#include <QMetaClassInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    PropertyChang p;

    QObject::connect(&p, &PropertyChang::nickNameChanged, &w, &Widget::labelShowNickName);
    QObject::connect(&p, &PropertyChang::countChanged, &w, &Widget::labelShowCount);
    QObject::connect(&p, &PropertyChang::valueChanged, &w, &Widget::labelShowValue);

    p.setNickName(QObject::tr("XieLong"));
    p.setCount(2333);
    p.setProperty("value", 3.14159);

    w.show();

    const QMetaObject *pMOw = w.metaObject();
    qDebug() << "Class Name: " << pMOw->className();
    qDebug() << "Object Name: " << w.objectName();

    int nInfoCount = pMOw->classInfoCount();
    for (int i=0; i < nInfoCount; i++) {
        QMetaClassInfo info = pMOw->classInfo(i);
        qDebug() << info.name() << "\t" << info.value();
    }

    const QMetaObject *pMOp = p.metaObject();
    qDebug() << "Class Name: " << pMOp->className();
    qDebug() << "Object Name: " << p.objectName();

    return a.exec();
}
