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
#include "dialognomniveau.h"

#define TAILLE 8

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
    void on_sourisCliquee(int touche);
    void on_sourisRelachee();
    void on_DialogAccepted(QString);

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    QGraphicsScene *sceneNiveaux,*sceneMenu,*sceneJeu,*sceneEditeur;
    QGraphicsRectItem *curseur,*boutonMenu[2];
    QSqlDatabase db;

    //Jeu
    QGraphicsRectItem *cadreJeu, *cases[TAILLE][TAILLE];
    QString pattern[TAILLE][TAILLE];

    //Editeur
    QGraphicsRectItem *tableau[TAILLE][TAILLE], *indicDepart[TAILLE], *selection[6], *btnSave, *btnMP;
    QString base[TAILLE][TAILLE];
    short currentSelectionEditeur,depart;
    QPen *pen;
    DialogNomNiveau *dialNomNiv;

    //Selecteur de niveaux
    QGraphicsTextItem *titre[2];
    QGraphicsRectItem *zone[2],*boutonNiveaux[4],*apercu[TAILLE][TAILLE],*cadreApercu;
    QList<QGraphicsTextItem*> offi,custom;
    QGraphicsLineItem *ligne[2];
    short currentSelectionNiveaux;
    bool isOffiSelectionNiveaux,isModification;
    QString tempModif;
};

#endif // MAINWINDOW_H
