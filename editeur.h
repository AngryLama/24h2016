#ifndef EDITEUR_H
#define EDITEUR_H

#include "jeu.h"

class Editeur : public Jeu
{
public:
    Editeur(QRect geometry);
private:
    QString tableau[16][16];
};

#endif // EDITEUR_H
