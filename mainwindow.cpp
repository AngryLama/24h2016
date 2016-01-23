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
    jeu=new Vue(geometry(),this);
    if( !connect(jeu,SIGNAL(touchePressee(int)),this,SLOT(on_touchePressee(int))) )
        qDebug() << "Erreur de connexion du signal touchePressee au slot on_touchePressee";
    if( !connect(jeu,SIGNAL(sourisBougee(QPoint)),this,SLOT(on_sourisBougee(QPoint))) )
        qDebug() << "Erreur de connexion du signal sourisBougee au slot on_sourisBougee";
    if( !connect(jeu,SIGNAL(sourisCliquee()),this,SLOT(on_sourisCliquee())) )
        qDebug() << "Erreur de connexion du signal sourisCliquee au slot on_sourisCliquee";

    //Création de la scène
    sceneMenu = new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    jeu->setScene(sceneMenu);
    jeu->setBackgroundBrush(QBrush(QPixmap(":/Images/bgMenu.jpg").scaledToHeight(geometry().height()-10)));

    //Initialisation du pinceau
    pen=new QPen(QBrush(Qt::white),10);

    //Création du menu
    boutonMenu[0]=new QGraphicsRectItem(QRect(0,0,650,150));
    boutonMenu[0]->setBrush(QBrush(QPixmap(":/Images/boutonJouer.png").scaledToHeight(boutonMenu[0]->rect().height())));
    boutonMenu[0]->setPos(310,150);
    sceneMenu->addItem(boutonMenu[0]);

    boutonMenu[1]=new QGraphicsRectItem(QRect(0,0,650,150));
    boutonMenu[1]->setBrush(QBrush(QPixmap(":/Images/boutonEditeur.png").scaledToHeight(boutonMenu[1]->rect().height())));
    boutonMenu[1]->setPos(310,450);
    sceneMenu->addItem(boutonMenu[1]);
    curseur=new QGraphicsRectItem(0,0,80,80);
    curseur->setBrush(QBrush(QPixmap(":/Images/curseurMenu.png").scaledToHeight(curseur->rect().height())));
    sceneMenu->addItem(curseur);
}

MainWindow::~MainWindow()
{
    sceneJeu->clear();
    delete sceneJeu;
    sceneMenu->clear();
    delete sceneMenu;
    delete pen;
    delete jeu;
    delete ui;
}

void MainWindow::on_touchePressee(int touche)
{

}

void MainWindow::on_sourisBougee(QPoint position)
{
    if(jeu->scene()==sceneMenu){
        curseur->setPos(position);
        //Verification de la collision
        QList<QGraphicsItem*> listeItem = curseur->collidingItems();
        if (listeItem.length()>0)
        {
            if (listeItem.last()==boutonMenu[0]) //Si il y a collision avec Jouer, alors on charge l'image hover
                boutonMenu[0]->setBrush(QBrush(QPixmap(":/Images/boutonJouerON.png").scaledToHeight(boutonMenu[0]->rect().height())));
            else boutonMenu[0]->setBrush(QBrush(QPixmap(":/Images/boutonJouer.png").scaledToHeight(boutonMenu[0]->rect().height())));

            if (listeItem.last()==boutonMenu[1]) //Si il y a collision avec Editeur, alors on charge l'image hover
                boutonMenu[1]->setBrush(QBrush(QPixmap(":/Images/boutonEditeurON.png").scaledToHeight(boutonMenu[0]->rect().height())));
            else boutonMenu[1]->setBrush(QBrush(QPixmap(":/Images/boutonEditeur.png").scaledToHeight(boutonMenu[0]->rect().height())));
        }
    }
}

void MainWindow::on_sourisCliquee()
{
    if(jeu->scene()==sceneMenu){
        QList<QGraphicsItem*> listeItem;
        listeItem = curseur->collidingItems();
        if (listeItem.length()>0)
        {
            if(listeItem.last()==boutonMenu[0])
            {
                //Choix du niveau
                QString temp[16][16];
                sceneJeu=new Jeu(geometry(),temp);
                jeu->setScene(sceneJeu);
            }
            if(listeItem.last()==boutonMenu[1])
            {
                //Lancer l'éditeur
                sceneEditeur=new Editeur(geometry());
                jeu->setScene(sceneEditeur);
            }
        }
    }
}
