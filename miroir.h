#ifndef MIROIR_H
#define MIROIR_H

#include <QObject>

class Miroir : public QObject
{
    Q_OBJECT
public:
    explicit Miroir(QObject *parent = 0);

signals:

public slots:
};

#endif // MIROIR_H