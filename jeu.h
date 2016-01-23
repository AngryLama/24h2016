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
    Jeu(QString levelPath);
    void creerMiroir(short sens, QGraphicsPolygonItem *poly);

private:
    QList<QGraphicsPolygonItem*> miroir;

};

#endif // JEU_H
