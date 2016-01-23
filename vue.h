#ifndef VUE_H
#define VUE_H

#include <QGraphicsView>
#include <QKeyEvent>

class Vue : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Vue(QRect geometry, QWidget *parent = 0);

signals:
    void touchePressee(int);

    void toucheRelachee(int);

    void sourisBougee(QPoint);

    void sourisCliquee();

public slots:
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);
};

#endif // VUE_H
