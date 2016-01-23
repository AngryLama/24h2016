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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
        VueJeu *jeu;
        QGraphicsScene *sceneJeu,*sceneMenu;
        QGraphicsLineItem *ligne;
        Joueur *joueur1,*joueur2;
        ParametreJoueur param[2];
        QGraphicsEllipseItem *balle,*curseur;
        QPen *pen;
        QTimer *timerBalle,*timerAnimationJ1,*timerAnimationJ2;
        bool partieLancee;
        Animation *anim[2];
        QLabel *score1,*score2;
        int movex,movey,mode;
        QList<int> touchesActives;
        Bouton *boutonMenu[4];
};

#endif // MAINWINDOW_H
