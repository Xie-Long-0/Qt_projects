#include "CustomListItemWidget.h"

CustomListItemWidget::CustomListItemWidget(const QPixmap &image, const QString &name, const QString &type, const QString &date, const QString &size, QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ui.label_image->setPixmap(image);
    ui.label_name->setText(name);
    ui.label_type->setText(type);
    ui.label_date->setText(date);
    ui.label_size->setText(size);
}
