#ifndef MIROIR_H
#define MIROIR_H

#include <QObject>
#include <QGraphicsPolygonItem>

enum{
    GH,
    DH,
    GB,
    DB
};

class Miroir : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    explicit Miroir(short sens, QObject *parent = 0);
    ~Miroir();

signals:

public slots:

private:
    QLine *segment[2];
};

#endif // MIROIR_H
