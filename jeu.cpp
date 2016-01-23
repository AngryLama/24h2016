#include "jeu.h"

Jeu::Jeu(QRect geometry, QString elements[16][16]):QGraphicsScene(0,0,geometry.width()-10,geometry.height()-10)
{
    //Création du cadre
    cadre=new QGraphicsRectItem(0,0,640,640);
    cadre->setPos(320,40);
    cadre->setPen(QPen(Qt::white,5));
    addItem(cadre);
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
