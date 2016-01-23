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
#include "editeur.h"
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

private slots:
    void on_sourisBougee(QPoint position);
    void on_sourisCliquee();
    void on_sourisRelachee();

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    Jeu *sceneJeu;
    Editeur *sceneEditeur;
    QGraphicsScene *sceneNiveaux,*sceneMenu;
    QGraphicsRectItem *curseur,*boutonMenu[2];
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
