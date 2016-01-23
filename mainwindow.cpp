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

    //Création du menu
    boutonMenu[0]=new QGraphicsRectItem(QRect(0,0,650,150));
    boutonMenu[0]->setBrush(QBrush(QPixmap(":/Boutons/Solo inactif.png").scaledToHeight(boutonMenu[0]->rect().height())));
    boutonMenu[0]->setPos(310,150);
    sceneMenu->addItem(boutonMenu[0]);

    boutonMenu[1]=new QGraphicsRectItem(QRect(0,0,650,150));
    boutonMenu[1]->setBrush(QBrush(QPixmap(":/Boutons/Versus inactif.png").scaledToHeight(boutonMenu[1]->rect().height())));
    boutonMenu[1]->setPos(310,450);
    sceneMenu->addItem(boutonMenu[1]);
    curseur=new QGraphicsEllipseItem(0,0,20,20);
    curseur->setBrush(QBrush(Qt::white));
    sceneMenu->addItem(curseur);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creerMiroir(short sens, QGraphicsPolygonItem *poly)
{
    QVector<QPoint> tempVect;
    switch (sens) {
    case GH:
    {
        tempVect<<QPoint(40,0)<<QPoint(40,40)<<QPoint(0,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case DH:
    {
        tempVect<<QPoint(0,0)<<QPoint(40,0)<<QPoint(40,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case GB:
    {
        tempVect<<QPoint(0,0)<<QPoint(40,0)<<QPoint(40,40);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    case DB:
    {
        tempVect<<QPoint(0,40)<<QPoint(0,0)<<QPoint(40,0);
        QPolygon temp(tempVect);
        poly = new QGraphicsPolygonItem(temp);
        break;
    }
    default:
        break;
    }
}
