#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
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
    ui->centerImgBtn->setEnabled(false);
    ui->adjustImgBtn->setEnabled(false);
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
    ui->centerImgBtn->setEnabled(true);
    ui->adjustImgBtn->setEnabled(true);
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
    gv->zoom100();
}

void Widget::on_centerImgBtn_clicked()
{
    gv->centerImage();
}

void Widget::on_adjustImgBtn_clicked()
{
    gv->zoomAuto();
}

void Widget::onScaleChanged(double factor)
{
    ui->scaledLabel->setText(QString::number((int)(factor * 100)) + '%');
}
