#pragma once

#include "ui_CustomListItemWidget.h"
#include <QPixmap>

class CustomListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListItemWidget(const QPixmap &image,
                                  const QString &name,
                                  const QString &type,
                                  const QString &date,
                                  const QString &size,
                                  QWidget *parent = nullptr);

private:
    Ui::CustomListItemWidget ui;
};
