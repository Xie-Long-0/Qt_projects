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
}

void GraphicView::zoomIn()
{
    if (m_factor > 0.25)
    {
        QPointF pos(width() / 2, height() / 2);
        m_factor /= 1.5;
        m_x = pos.x() - (pos.x() - m_x) / 1.5;
        m_y = pos.y() - (pos.y() - m_y) / 1.5;
        update();
        emit factorChanged(m_factor);
    }
}

void GraphicView::zoomOut()
{
    if (m_factor < 100)
    {
        QPointF pos(width() / 2, height() / 2);
        m_factor *= 1.5;
        m_x = pos.x() - (pos.x() - m_x) * 1.5;
        m_y = pos.y() - (pos.y() - m_y) * 1.5;
        update();
        emit factorChanged(m_factor);
    }
}

void GraphicView::resetZoom()
{
    m_factor = 1.0;
    m_x = m_y = 0;
    update();
    emit factorChanged(m_factor);
}

void GraphicView::mousePressEvent(QMouseEvent *e)
{
    m_pressed = true;
    m_pos = e->localPos();
}

void GraphicView::mouseReleaseEvent(QMouseEvent *)
{
    m_pressed = false;
}

void GraphicView::mouseMoveEvent(QMouseEvent *e)
{
    if (m_pressed)
    {
        auto offset = e->localPos() - m_pos;

        m_x += offset.x();
        m_y += offset.y();

        m_pos = e->localPos();
        update();
    }
}

void GraphicView::wheelEvent(QWheelEvent *e)
{
    if (e->angleDelta().y() > 0 && m_factor < 100)
    {
        m_factor *= 1.25;
        m_x = e->position().x() - (e->position().x() - m_x) * 1.25;
        m_y = e->position().y() - (e->position().y() - m_y) * 1.25;
        emit factorChanged(m_factor);
    }
    else if (e->angleDelta().y() < 0 && m_factor > 0.25)
    {
        m_factor /= 1.25;
        m_x = e->position().x() - (e->position().x() - m_x) / 1.25;
        m_y = e->position().y() - (e->position().y() - m_y) / 1.25;
        emit factorChanged(m_factor);
    }
    update();
}

void GraphicView::paintEvent(QPaintEvent *e)
{
    QPainter pt(this);
    pt.setRenderHint(QPainter::Antialiasing);
    QTransform tf;
    // 设置绘画坐标原点
    tf.translate(m_x, m_y);
    // 设置绘图缩放
    tf.scale(m_factor, m_factor);
    pt.setTransform(tf);
    pt.drawImage(0, 0, m_img);
    pt.end();

    QWidget::paintEvent(e);
}

void GraphicView::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}
