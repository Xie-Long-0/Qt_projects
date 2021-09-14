#pragma once

#include <QWidget>
#include <QImage>

class GraphicView : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicView(QWidget *parent = nullptr);

    QImage image() const { return m_img; }
    double factor() const { return m_factor; }

public slots:
    void setImage(const QImage &img);
    void zoomIn();
    void zoomOut();
    void resetZoom();

protected:
    void mousePressEvent(QMouseEvent *e) override;  //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;       //滚轮事件
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

signals:
    void factorChanged(double factor);

private:
    QImage m_img;
    QPointF m_pos;
    double m_factor = 1.0;
    double m_x = 0.0;
    double m_y = 0.0;
    bool m_pressed = false;
};

