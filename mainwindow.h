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
#include <QMessageBox>
#include "vue.h"
#include "dialognomniveau.h"

#define TAILLE 8

enum{
    GD,
    DG,
    HB,
    BH,
    OFFI,
    CUSTOM
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void calculLaser(short x,short y,short sens);
    void affichageNiveaux(int colonnes,short mode);

private slots:
    void on_sourisBougee(QPoint position);
    void on_sourisCliquee(int touche);
    void on_sourisRelachee();
    void on_DialogAccepted(QString);

private:
    Ui::MainWindow *ui;
    Vue *jeu;
    QGraphicsScene *sceneNiveaux,*sceneMenu,*sceneJeu,*sceneEditeur,*sceneGagne;
    QGraphicsRectItem *curseur,*boutonMenu[2];
    QSqlDatabase db;

    //Jeu
    QGraphicsRectItem *cadreJeu, *tableauJeu[TAILLE][TAILLE],*departJeu[TAILLE], *selectionJeu[4];
    QString pattern[TAILLE][TAILLE],currentPattern[TAILLE][TAILLE];
    QLabel *affNbSelection[4];
    short currentSelectionJeu,depart;

    //Editeur
    QGraphicsRectItem *tableauEditeur[TAILLE][TAILLE], *indicDepart[TAILLE], *selectionEditeur[6], *btnSave, *btnMP;
    QString base[TAILLE][TAILLE];
    short currentSelectionEditeur,departEditeur;
    QPen *pen;
    DialogNomNiveau *dialNomNiv;

    //Selecteur de niveaux
    QGraphicsTextItem *titre[2];
    QGraphicsRectItem *zone[2],*boutonNiveaux[4],*apercu[TAILLE][TAILLE],*cadreApercu,*boutonScroll[4];
    QList<QGraphicsTextItem*> offi,custom;
    QGraphicsLineItem *ligne[2];
    short currentSelectionNiveaux,scrollOffi,scrollCustom;
    bool isOffiSelectionNiveaux,isModification;
    QString tempModif;

    //Gagne
    QGraphicsRectItem *texteGagne,*retourMenuGagne;
};

#endif // MAINWINDOW_H
