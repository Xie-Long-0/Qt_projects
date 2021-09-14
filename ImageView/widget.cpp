#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QBoxLayout>

#include "graphicview.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout(ui->frame);
    gv = new GraphicView(ui->frame);
    layout->addWidget(gv);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->frame->setLayout(layout);

    connect(gv, &GraphicView::factorChanged, this, &Widget::onScaleChanged);

    ui->zoomInBtn->setEnabled(false);
    ui->zoomOutBtn->setEnabled(false);
    ui->originalBtn->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openImgBtn_clicked()
{
    QString imgName = QFileDialog::getOpenFileName(this, tr("打开图片"), QString(), "*.bmp *.jpg *.jpeg *.png");
    if (imgName.isEmpty()) return;
    QImage img(imgName);
    if (img.isNull()) return;

    gv->setImage(img);
    ui->imgPathLineEdit->setText(imgName);

    ui->zoomInBtn->setEnabled(true);
    ui->zoomOutBtn->setEnabled(true);
    ui->originalBtn->setEnabled(true);
}

void Widget::on_zoomInBtn_clicked()
{
    gv->zoomIn();
}

void Widget::on_zoomOutBtn_clicked()
{
    gv->zoomOut();
}

void Widget::on_originalBtn_clicked()
{
    gv->resetZoom();
}

void Widget::onScaleChanged(double factor)
{
    ui->scaledLabel->setText(QString::number(factor * 100) + '%');
}
