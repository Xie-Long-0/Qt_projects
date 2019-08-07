#ifndef SHOWLEDSIGNAL_H
#define SHOWLEDSIGNAL_H

#include <QObject>

class ShowLEDSignal : public QObject
{
    Q_OBJECT
public:
    explicit ShowLEDSignal(QObject *parent = nullptr);

signals:

public slots:
    void showSignal(QString str);
    void showAllSignals();
};

#endif // SHOWLEDSIGNAL_H
