#ifndef VUE_H
#define VUE_H

#include <QGraphicsView>
#include <QMouseEvent>

class Vue : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Vue(QRect geometry, QWidget *parent = 0);

signals:
    void sourisBougee(QPoint);
    void sourisCliquee();

public slots:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // VUE_H
