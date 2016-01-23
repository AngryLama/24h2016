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
    void sourisBougee(QPoint);
    void sourisCliquee();

private slots:
    void on_touchePressee(int touche);
    void on_sourisBougee(QPoint position);
    void on_sourisCliquee();

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    QGraphicsScene *sceneJeu,*sceneMenu;
    QPen *pen;
    QGraphicsRectItem *curseur,*boutonMenu[2];
};

#endif // MAINWINDOW_H
