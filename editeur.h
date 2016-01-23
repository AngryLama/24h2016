#ifndef EDITEUR_H
#define EDITEUR_H

#include <QGraphicsRectItem>
#include "jeu.h"

class Editeur : public Jeu
{
public:
    Editeur(QRect geometry);
    ~Editeur();
private:
    QString tableau[16][16];
    QGraphicsRectItem *selection[8];
    QPen *pen;
};

#endif // EDITEUR_H
