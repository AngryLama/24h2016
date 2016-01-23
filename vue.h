#ifndef VUE_H
#define VUE_H

#include <QObject>

class Vue : public QObject
{
    Q_OBJECT
public:
    explicit Vue(QObject *parent = 0);

signals:

public slots:
};

#endif // VUE_H