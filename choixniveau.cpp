#include "choixniveau.h"

choixNiveau::choixNiveau(QRect geometry) : QGraphicsScene(0,0,geometry.width()-10,geometry.height()-10)
{
    //Création du cadre
    cadre=new QGraphicsRectItem(0,0,640,640);
    cadre->setPos(320,40);
    cadre->setPen(QPen(Qt::white,5));
    addItem(cadre);
}

