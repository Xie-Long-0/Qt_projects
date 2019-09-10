#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMovie>
#include <QImageReader>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_OpenImage_clicked();
    void on_pushButton_OpenMovie_clicked();
    void on_pushButton_Func1_clicked();
    void on_pushButton_Func2_clicked();
    void on_pushButton_Func3_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void recvPlayError(QImageReader::ImageReaderError error);   //接收播放错误信号
    void recvFrameNumber(int frameNumber);          //接收帧号变化信号

private:
    Ui::Widget *ui;

    QPixmap *m_pPixMap;
    QMovie *m_pMovie;
    bool m_isMovie;
    bool m_isPlaying;

    void clearOld();
    void scalePixMap(int scale);
};

#endif // WIDGET_H
