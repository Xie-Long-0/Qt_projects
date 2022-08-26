#pragma once

#include <QtWidgets/QWidget>
#include "ui_STL_read.h"

class STL_read : public QWidget
{
    Q_OBJECT

public:
    STL_read(QWidget *parent = nullptr);
    ~STL_read();

private slots:
    void onOpenBtn();

private:
    Ui::STL_readClass ui;
};
