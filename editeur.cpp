#include "editeur.h"

Editeur::Editeur(QRect geometry):Jeu(geometry,tableau)
{
    pen=new QPen(Qt::white,5);
    for(int x=0;x<6;x++){
        selection[x]=new QGraphicsRectItem(0,0,40,40);
        selection[x]->setPos(1100,100+(60*x));
        selection[x]->setPen(*pen);
    }

    selection[0]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(selection[0]->rect().height())));
    selection[1]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(selection[0]->rect().height())));
    selection[2]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(selection[0]->rect().height())));
    selection[3]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(selection[0]->rect().height())));
    selection[4]->setBrush(QBrush(QPixmap(":/Laser/Mur H.png").scaledToHeight(selection[0]->rect().height())));
    selection[5]->setBrush(QBrush(QPixmap(":/Laser/Mur V.png").scaledToHeight(selection[0]->rect().height())));

    for(int x=0;x<6;x++)
        addItem(selection[x]);
}

Editeur::~Editeur()
{
    for(int x=0;x<8;x++)
        delete selection[x];
    delete pen;
}
