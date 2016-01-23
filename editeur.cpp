#include "editeur.h"

Editeur::Editeur(QRect geometry):Jeu(geometry,tableau)
{
    pen=new QPen(Qt::white,5);
    for(int x=0;x<8;x++){
        selection[x]=new QGraphicsRectItem(0,0,40,40);
        //selection[x]
        selection[x]->setPen(*pen);
    }


    for(int x=0;x<8;x++)
        addItem(selection[x]);
}

Editeur::~Editeur()
{
    for(int x=0;x<8;x++)
        delete selection[x];
    delete pen;
}
