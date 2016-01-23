#include "vue.h"

Vue::Vue(QRect geometry, QWidget *parent) : QGraphicsView(parent)
{
    setGeometry(geometry);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(Qt::black));
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setMouseTracking(true);
}

void Vue::mouseMoveEvent(QMouseEvent *event)
{
    emit sourisBougee(event->pos());
}

void Vue::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        emit sourisCliquee();
}

void Vue::mouseReleaseEvent(QMouseEvent *event)
{
    emit sourisRelachee();
}
