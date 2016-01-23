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
    QList<QGraphicsPolygonItem*> miroir;
    QGraphicsRectItem *cadre;
};

#endif // JEU_H
