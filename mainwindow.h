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
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "vue.h"
#include "laser.h"
#include "choixniveau.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sourisBougee(QPoint position);
    void on_sourisCliquee();
    void on_sourisRelachee();

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    QGraphicsScene *sceneNiveaux,*sceneMenu,*sceneJeu,*sceneEditeur;
    QGraphicsRectItem *curseur,*boutonMenu[2];
    QSqlDatabase db;

    //Jeu
    QGraphicsRectItem *cadre;
    QGraphicsRectItem *cases[16][16];

    //Editeur
    QString tableau[16][16];
    QGraphicsRectItem *selection[6];
    QPen *pen;
};

#endif // MAINWINDOW_H
