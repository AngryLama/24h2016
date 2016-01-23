#ifndef JEU_H
#define JEU_H

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>

//Sens des miroirs
enum{
    GH,
    DH,
    GB,
    DB
};

class Jeu : public QGraphicsScene
{
public:
    Jeu(QRect geometry, QString elements[16][16]);
    void creerMiroir(short sens, QGraphicsPolygonItem *poly);

private:
    QGraphicsRectItem *cadre;
    QGraphicsRectItem *cases[16][16];
};

#endif // JEU_H
