#include "graphicview.h"
#include <QPainter>
#include <QTransform>
#include <QMouseEvent>
#include <QDebug>

GraphicView::GraphicView(QWidget *parent) : QWidget(parent)
{
}

void GraphicView::setImage(const QImage &img)
{
    m_img = img;
    zoomAuto();
}

void GraphicView::zoomIn()
{
    QPointF pos(width() / 2.0, height() / 2.0);
    zoomInAtPos(pos);
}

void GraphicView::zoomOut()
{
    QPointF pos(width() / 2.0, height() / 2.0);
    zoomOutAtPos(pos);
}

void GraphicView::zoom100()
{
    m_factor = 1.0;
    m_w = m_img.width();
    m_h = m_img.height();
    adjustImage();
    update();
    emit factorChanged(m_factor);
}

void GraphicView::zoomAuto()
{
    adaptFactor();
    centerImage();
    update();
}

void GraphicView::centerImage()
{
    m_x = (width() - m_w) / 2.0;
    m_y = (height() - m_h) / 2.0;
    update();
}

void GraphicView::mousePressEvent(QMouseEvent *e)
{
    if (!m_img.isNull())
    {
        m_pressed = true;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        m_pos = e->position();
#else
        m_pos = e->localPos();
#endif
    }
}

void GraphicView::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
}

void GraphicView::mouseMoveEvent(QMouseEvent *e)
{
    if (m_pressed)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        auto offset = e->position() - m_pos;
#else
        auto offset = e->localPos() - m_pos;
#endif

        if (m_x <= 0 && m_x + m_w >= width())
            m_x += offset.x();
        if (m_y <= 0 && m_y + m_h >= height())
            m_y += offset.y();

        adjustImage();

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        m_pos = e->position();
#else
        m_pos = e->localPos();
#endif
        update();
    }
}

void GraphicView::wheelEvent(QWheelEvent *e)
{
    if (m_img.isNull()) return;

    // 滚轮放大
    if (e->angleDelta().y() > 0)
    {
        zoomOutAtPos(e->position());
    }
    // 滚轮缩小
    else if (e->angleDelta().y() < 0)
    {
        zoomInAtPos(e->position());
    }
}

void GraphicView::paintEvent(QPaintEvent *e)
{
    if (m_img.isNull()) return QWidget::paintEvent(e);

    QPainter pt(this);
    pt.setRenderHint(QPainter::Antialiasing);
    QTransform tf;
    // 设置绘图左上角坐标
    tf.translate(m_x, m_y);
    // 设置绘图缩放
    tf.scale(m_factor, m_factor);
    // 应用转换
    pt.setTransform(tf);
    // 从绘图坐开始绘制图片
    pt.drawImage(0, 0, m_img);
    pt.end();

    QWidget::paintEvent(e);
}

void GraphicView::resizeEvent(QResizeEvent *e)
{
    if (m_img.isNull()) return QWidget::resizeEvent(e);

    if (m_w < width() && m_h < height())
    {
        adaptFactor();
    }
    adjustImage();
    QWidget::resizeEvent(e);
}

void GraphicView::zoomInAtPos(const QPointF &pos)
{
    if (m_factor > 0.25 || m_w > width() || m_h > height())
    {
        m_factor /= 1.25;
        // 限制最小缩放倍数
        if (m_factor < 0.25 && m_w < width() && m_h < height()) m_factor = 0.25;
        
        m_x = pos.x() - (pos.x() - m_x) / 1.25;
        m_y = pos.y() - (pos.y() - m_y) / 1.25;
        m_w = m_img.width() * m_factor;
        m_h = m_img.height() * m_factor;
        adjustImage();
        update();
        emit factorChanged(m_factor);
    }
}

void GraphicView::zoomOutAtPos(const QPointF &pos)
{
    if (m_factor < 100)
    {
        m_factor *= 1.25;
        if (m_factor > 100)
            m_factor = 100;
        m_x = pos.x() - (pos.x() - m_x) * 1.25;
        m_y = pos.y() - (pos.y() - m_y) * 1.25;
        m_w = m_img.width() * m_factor;
        m_h = m_img.height() * m_factor;
        adjustImage();
        update();
        emit factorChanged(m_factor);
    }
}

void GraphicView::adaptFactor()
{
    double w = (double)width() / m_img.width();
    double h = (double)height() / m_img.height();
    // 选择长的一边填充窗口
    if (w < h)
    {
        m_factor = w;
        m_w = width();
        m_h = m_img.height() * m_factor;
    }
    else
    {
        m_factor = h;
        m_w = m_img.width() * m_factor;
        m_h = height();
    }
    emit factorChanged(m_factor);
}

void GraphicView::adjustImage()
{
    // 当图像缩放倍率小于25%，且图像大小小于窗口大小时，图像限制在窗口大小
    if (m_w <= width() && m_h <= height() && m_factor < 0.25)
    {
        adaptFactor();
        centerImage();
        return;
    }

    // 图像左边小于窗口左边
    if (m_x > 0 && m_w >= width())
        m_x = 0;

    // 图像顶部小于窗口顶部
    if (m_y > 0 && m_h >= height())
        m_y = 0;

    // 图像右边小于窗口右边
    if (m_x + m_w < width() && m_w >= width())
        m_x = width() - m_w;

    // 图像底部小于窗口底部
    if (m_y + m_h < height() && m_h >= height())
        m_y = height() - m_h;

    if (m_w < width())
        m_x = (width() - m_w) / 2.0;

    if (m_h < height())
        m_y = (height() - m_h) / 2.0;
}
