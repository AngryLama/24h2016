#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Importation de la police d'ecriture
        QFontDatabase::addApplicationFont(":/Spyv3l.ttf"); //Spylord Laser

        //Création de la vue
        jeu=new VueJeu(geometry(),this);
        connect(jeu,SIGNAL(touchePressee(int)),this,SLOT(on_touchePressee(int)));
        connect(jeu,SIGNAL(toucheRelachee(int)),this,SLOT(on_toucheRelachee(int)));
        connect(jeu,SIGNAL(sourisBougee(QPoint)),this,SLOT(on_sourisBougee(QPoint)));
        connect(jeu,SIGNAL(sourisCliquee()),this,SLOT(on_sourisCliquee()));

        //Création de la scène
        sceneJeu = new QGraphicsScene(0,0,640,640);
        sceneMenu = new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

        jeu->setScene(sceneMenu);

        //Initialisation du pinceau
        pen=new QPen(QBrush(Qt::white),10);

        //Création du joueur 1
        joueur1=new Joueur(QRect(0,0,10,120));
        joueur1->setPen(*pen);
        joueur1->setPos(30,(height()/2)-(joueur1->rect().height()/2));
        sceneJeu->addItem(joueur1);

        //Création du menu
        boutonMenu[0]=new Bouton(QRect(0,0,650,150));
        boutonMenu[0]->setBrush(QBrush(QPixmap(":/Boutons/Solo inactif.png").scaledToHeight(boutonMenu[0]->rect().height())));
        boutonMenu[0]->setPos(310,150);
        sceneMenu->addItem(boutonMenu[0]);

        boutonMenu[1]=new Bouton(QRect(0,0,650,150));
        boutonMenu[1]->setBrush(QBrush(QPixmap(":/Boutons/Versus inactif.png").scaledToHeight(boutonMenu[1]->rect().height())));
        boutonMenu[1]->setPos(310,450);
        sceneMenu->addItem(boutonMenu[1]);
        curseur=new QGraphicsEllipseItem(0,0,20,20);
        curseur->setBrush(QBrush(Qt::white));
        sceneMenu->addItem(curseur);
        mode=AUCUN;
}

MainWindow::~MainWindow()
{
    delete ui;
}
