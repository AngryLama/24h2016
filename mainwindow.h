#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QEventLoop>
#include <QFontDatabase>
#include <QLabel>
#include "miroir.h"
#include "vue.h"
#include "laser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void touchePressee(int);
    void toucheRelachee(int);
    void sourisBougee(QPoint);
    void sourisCliquee();

private slots:
    void on_touchePressee(int);
    void on_toucheRelachee(int);
    void on_sourisBougee(QPoint);
    void on_sourisCliquee();

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    QGraphicsScene *sceneJeu,*sceneMenu;
    QGraphicsEllipseItem *curseur;
    QPen *pen;
    QList<int> touchesActives;
    QRect boutonMenu[4];
};

#endif // MAINWINDOW_H
