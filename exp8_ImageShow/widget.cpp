#include "widget.h"
#include "ui_widget.h"

#ifdef QT_DEBUG
  #include <QDebug>
#endif

#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>

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
    QScrollArea *m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidget(ui->label_Viewer);

    QRect labelRect = ui->label_Viewer->geometry();
    //调整滚动条区域大小，防止一开始就出现
    labelRect.setWidth(labelRect.width() + 4);
    labelRect.setHeight(labelRect.height() + 4);
    m_scrollArea->setGeometry(labelRect);

    ui->pushButton_Func1->setEnabled(false);
    ui->pushButton_Func2->setEnabled(false);
    ui->pushButton_Func3->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);

#ifdef QT_DEBUG
    //打印支持的格式
    qDebug() << QImageReader::supportedImageFormats();
    qDebug() << QMovie::supportedFormats();
#endif
}

Widget::~Widget()
{
    clearOld();
    delete ui;
}

void Widget::recvPlayError(QImageReader::ImageReaderError error)
{
#ifdef QT_DEBUG
    qDebug() << "动图播放出错代码：" << error;
#endif

    QMessageBox::critical(this, tr("播放出错"),
                          tr("动图播放出错[code: %2]：%1").arg(m_pMovie->fileName()).arg(error));
    m_isPlaying = false;
}

void Widget::recvFrameNumber(int frameNumber)
{
    ui->horizontalSlider->setValue(frameNumber);
}

void Widget::clearOld()
{
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

    ui->label_Viewer->clear();
    ui->label_Viewer->setText(tr("无显示内容"));
    m_isMovie = false;
    m_isPlaying = false;
    ui->pushButton_Func1->setEnabled(false);
    ui->pushButton_Func2->setEnabled(false);
    ui->pushButton_Func3->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->label_Slider->clear();
}

void Widget::scalePixMap(int scale)
{
    int sw = m_pPixMap->width() * scale / 100;
    int sh = m_pPixMap->height() * scale / 100;
    QPixmap newpix = m_pPixMap->scaled(sw, sh);
    ui->label_Viewer->setPixmap(newpix);
    ui->label_Viewer->setGeometry(newpix.rect());
    ui->horizontalSlider->setValue(scale);
}

void Widget::on_pushButton_OpenImage_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开图片"), "",
                      "Pictures (*.bmp *.ico *.jpg *.jpeg *.png *.svg *.tif *.tiff *.webp *.xpm)");
    if (strFile.isEmpty())
        return;

    clearOld();     //清除旧内容

#ifdef QT_DEBUG
    qDebug() << strFile;
#endif

    m_pPixMap = new QPixmap();
    if (m_pPixMap->load(strFile)) {
        ui->label_Viewer->setPixmap(*m_pPixMap);
        ui->label_Viewer->setGeometry(m_pPixMap->rect());
        m_isMovie = false;
        m_isPlaying = false;

        ui->pushButton_Func1->setEnabled(true);
        ui->pushButton_Func1->setText(tr("缩小"));
        ui->pushButton_Func2->setEnabled(true);
        ui->pushButton_Func2->setText(tr("放大"));
        ui->pushButton_Func3->setEnabled(true);
        ui->pushButton_Func3->setText(tr("还原"));

        ui->horizontalSlider->setEnabled(true);
        ui->horizontalSlider->setRange(25, 300);
        ui->horizontalSlider->setSingleStep(10);
        ui->horizontalSlider->setValue(100);
        ui->label_Slider->setText(tr("缩放倍数：100%"));
    }
    else {
        delete m_pPixMap;
        m_pPixMap = nullptr;
        QMessageBox::critical(this, tr("打开失败"), tr("无法打开图片：%1").arg(strFile));
    }
}

void Widget::on_pushButton_OpenMovie_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this, tr("打开动态图"), "",
                      "Animations (*.gif *.mng *.webp)");
    if (strFile.isEmpty())
        return;

    clearOld();     //清除旧内容

#ifdef QT_DEBUG
    qDebug() << strFile;
#endif

    m_pMovie = new QMovie(strFile);
    if (!m_pMovie->isValid()) {
        delete m_pMovie;
        m_pMovie = nullptr;
        QMessageBox::critical(this, tr("打开失败"), tr("无法打开动态图：%1").arg(strFile));
        return;
    }

    int nFrameCount = m_pMovie->frameCount();

#ifdef QT_DEBUG
    qDebug() << "总帧数：" << nFrameCount;
    qDebug() << "循环次数：" << m_pMovie->loopCount();
#endif

    ui->label_Viewer->setMovie(m_pMovie);
    m_isMovie = true;

    if (nFrameCount > 0) {
        ui->horizontalSlider->setRange(0, nFrameCount);
        ui->horizontalSlider->setSingleStep(1);
        ui->horizontalSlider->setValue(0);
        ui->label_Slider->setText(tr("播放帧数：%1").arg(nFrameCount));
    }

    connect(m_pMovie, &QMovie::error, this, &Widget::recvPlayError);
    connect(m_pMovie, &QMovie::frameChanged, this, &Widget::recvFrameNumber);

    if (m_pMovie->jumpToFrame(0)) {     //设置label的大小为第一帧的大小
        ui->label_Viewer->setGeometry(m_pMovie->frameRect());
    }

    ui->pushButton_Func1->setEnabled(true);
    ui->pushButton_Func1->setText(tr("播放"));
    ui->pushButton_Func2->setEnabled(true);
    ui->pushButton_Func2->setText(tr("停止"));
}

void Widget::on_pushButton_Func1_clicked()
{
    if (m_isMovie) {    //播放暂停功能
        if (m_isPlaying) {
            m_pMovie->setPaused(true);
            m_isPlaying = false;
            ui->pushButton_Func1->setText(tr("播放"));
        }
        else {
            m_pMovie->start();
            m_isPlaying = true;
            ui->pushButton_Func1->setText(tr("暂停"));
        }
    }
    else {      //缩小功能
        int scale = ui->horizontalSlider->value() - 25;
        if (scale < 25)
            scale = 25;
        scalePixMap(scale);
    }
}

void Widget::on_pushButton_Func2_clicked()
{
    if (m_isMovie) {    //停止播放功能
        m_pMovie->stop();
        m_isPlaying = false;
        m_pMovie->jumpToFrame(0);
        ui->pushButton_Func1->setText(tr("播放"));
    }
    else {      //放大功能
        int scale = ui->horizontalSlider->value() + 25;
        if (scale > 200)
            scale = 200;
        scalePixMap(scale);
    }
}

void Widget::on_pushButton_Func3_clicked()
{
    //还原功能
    ui->label_Viewer->setPixmap(*m_pPixMap);
    ui->label_Viewer->setGeometry(m_pPixMap->rect());
    ui->horizontalSlider->setValue(100);
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    if (m_isMovie) {
        ui->label_Slider->setText(tr("播放帧数：%1/%2").arg(value).arg(m_pMovie->frameCount()));
    }
    else {
        scalePixMap(value);
        ui->label_Slider->setText(tr("缩放倍数：%1%").arg(value));
    }
}
