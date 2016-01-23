#ifndef CHOIXNIVEAU_H
#define CHOIXNIVEAU_H

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>

class choixNiveau : public QGraphicsScene
{
    Q_OBJECT
public:
    choixNiveau(QRect geometry);

private:
    QGraphicsRectItem *cadre;
};

#endif // CHOIXNIVEAU_H
