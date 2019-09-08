#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QScrollArea>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pPixMap = nullptr;
    m_pMovie = nullptr;
    m_isMovie = false;
    m_isPlaying = false;

    //设置滚动区域
    QRect rectlabel = ui->label_Viewer->geometry();
    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setWidget(ui->label_Viewer);
    scrollarea->setGeometry(rectlabel);

    ui->pushButton_Func1->setEnabled(false);
    ui->pushButton_Func2->setEnabled(false);
    ui->pushButton_Func3->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);

    //打印支持的格式
    qDebug() << QImageReader::supportedImageFormats();
    qDebug() << QMovie::supportedFormats();
}

Widget::~Widget()
{
    clearOld();
    delete ui;
}

void Widget::recvPlayError(QImageReader::ImageReaderError error)
{

}

void Widget::recvFrameNumber(int frameNumber)
{

}

void Widget::clearOld()
{
    ui->label_Viewer->clear();

    if (m_pPixMap != nullptr) {
        delete m_pPixMap;
        m_pPixMap = nullptr;
    }

    if (m_pMovie != nullptr) {
        if (m_isPlaying)
            m_pMovie->stop();
        delete m_pMovie;
        m_pMovie = nullptr;
    }

    m_isMovie = false;
    m_isPlaying = false;
}

void Widget::on_pushButton_OpenImage_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开图片"), "/home/xielong/图片",
                      "Pictures (*.bmp *.ico *.jpg *.jpeg *.png *.svg *.tif *.tiff *.webp *.xpm)");
    if (strFile.isEmpty())
        return;

    clearOld();     //清除旧内容
    qDebug() << strFile;

    m_pPixMap = new QPixmap();
    if (m_pPixMap->load(strFile)) {
        ui->label_Viewer->setPixmap(*m_pPixMap);
        ui->label_Viewer->setGeometry(m_pPixMap->rect());
        m_isMovie = false;
        m_isPlaying = false;
    }
    else {
        delete m_pPixMap;
        m_pPixMap = nullptr;
        QMessageBox::critical(this, tr("打开失败"), tr("无法打开图片：%1").arg(strFile));
    }
}

void Widget::on_pushButton_OpenMovie_clicked()
{

}

void Widget::on_pushButton_Func1_clicked()
{

}

void Widget::on_pushButton_Func2_clicked()
{

}

void Widget::on_pushButton_Func3_clicked()
{

}
