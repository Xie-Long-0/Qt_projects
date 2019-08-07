#include "showledsignal.h"
#include <QMessageBox>

ShowLEDSignal::ShowLEDSignal(QObject *parent) : QObject(parent)
{

}

void ShowLEDSignal::showSignal(QString str)
{
    QMessageBox::information(NULL, tr("信号灯"), str);
}

void ShowLEDSignal::showAllSignals()
{
    showSignal(tr("红灯、黄灯、绿灯亮了！"));
}
