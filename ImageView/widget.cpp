#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QBoxLayout>

#include "ImageView.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("图片查看器"));

    QHBoxLayout *layout = new QHBoxLayout(ui->frame);
    gv = new ImageView(ui->frame);
    layout->addWidget(gv);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->frame->setLayout(layout);

    connect(gv, &ImageView::factorChanged, this, &Widget::onScaleChanged);

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
    QString imgName = QFileDialog::getOpenFileName(this, tr("打开图片"), QString(),
        tr("图片 (*.bmp *.jpg *.jpeg *.png *.tif *.tiff *.webp);; 所有文件 (*.*)"));
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
