#ifndef LASER_H
#define LASER_H

#include <QObject>

class Laser : public QObject
{
    Q_OBJECT
public:
    explicit Laser(QObject *parent = 0);

signals:

public slots:
};

#endif // LASER_H