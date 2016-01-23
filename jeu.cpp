#include "jeu.h"

Jeu::Jeu(QString levelPath)
{

}

void Jeu::creerMiroir(short sens, QGraphicsPolygonItem *poly)
{
    QVector<QPoint> tempVect;
    switch (sens) {
    case GH:
    {
        tempVect<<QPoint(40,0)<<QPoint(40,40)<<QPoint(0,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case DH:
    {
        tempVect<<QPoint(0,0)<<QPoint(40,0)<<QPoint(40,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case GB:
    {
        tempVect<<QPoint(0,0)<<QPoint(40,0)<<QPoint(40,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case DB:
    {
        tempVect<<QPoint(0,40)<<QPoint(0,0)<<QPoint(40,0);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    default:
        break;
    }
}
