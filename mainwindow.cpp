#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->grpLvlBase->hide();
    ui->grpLvlEdit->hide();

    //Importation de la police d'ecriture
    QFontDatabase::addApplicationFont(":/Spyv3l.ttf"); //Spylord Laser

    //Création de la vue
    jeu=new Vue(geometry(),this);
    if( !connect(jeu,SIGNAL(sourisBougee(QPoint)),this,SLOT(on_sourisBougee(QPoint))) )
        qDebug() << "Erreur de connexion du signal sourisBougee au slot on_sourisBougee";
    if( !connect(jeu,SIGNAL(sourisCliquee()),this,SLOT(on_sourisCliquee())) )
        qDebug() << "Erreur de connexion du signal sourisCliquee au slot on_sourisCliquee";
    if( !connect(jeu,SIGNAL(sourisRelachee()),this,SLOT(on_sourisRelachee())) )
        qDebug() << "Erreur de connexion du signal sourisRelachee au slot on_sourisRelachee";

    //Création de la scène
    sceneMenu = new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    jeu->setScene(sceneMenu);
    jeu->setBackgroundBrush(QBrush(QPixmap(":/Images/bgMenu.jpg").scaledToHeight(geometry().height()-10)));

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

    //Création du jeu
    sceneJeu=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    //Création de l'éditeur
    sceneEditeur=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);
    pen=new QPen(Qt::white,5);
    for(int x=0;x<6;x++){
        selection[x]=new QGraphicsRectItem(0,0,80,80);
        selection[x]->setPos(1100,40+(110*x));
        selection[x]->setPen(*pen);
    }

    selection[0]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(selection[0]->rect().height())));
    selection[1]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(selection[0]->rect().height())));
    selection[2]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(selection[0]->rect().height())));
    selection[3]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(selection[0]->rect().height())));
    selection[4]->setBrush(QBrush(QPixmap(":/Laser/Mur H.png").scaledToHeight(selection[0]->rect().height())));
    selection[5]->setBrush(QBrush(QPixmap(":/Laser/Mur V.png").scaledToHeight(selection[0]->rect().height())));

    for(int x=0;x<6;x++)
        sceneEditeur->addItem(selection[x]);

    //Connexion à la base de données
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("niveaux.sqlite");
    if( db.open() )
        qDebug() << "Ouverture de la base de donnees avec succes";
    else qDebug() << "Echec d'ouverture de la base de donnees";
}

MainWindow::~MainWindow()
{
    sceneEditeur->clear();
    delete sceneEditeur;
    delete pen;
    db.close();
    delete sceneJeu;
    sceneMenu->clear();
    delete sceneMenu;
    delete jeu;
    delete ui;
}

void MainWindow::on_sourisBougee(QPoint position)
{
    curseur->setPos(position);
    if(jeu->scene()==sceneMenu){
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
    QList<QGraphicsItem*> listeItem;
    listeItem = curseur->collidingItems();
    if (listeItem.length()>0)
    {
        if(jeu->scene()==sceneMenu){
            if(listeItem.last()==boutonMenu[0])
            {
                //Choix du niveau
                //sceneNiveaux = new choixNiveau(geometry());
                //sceneNiveaux->addItem(curseur);
                cadre=new QGraphicsRectItem(0,0,640,640);
                cadre->setPos(320,40);
                cadre->setPen(*pen);
                sceneJeu->addItem(cadre);
                sceneJeu->addItem(curseur);
                jeu->setScene(sceneJeu);
            }
            if(listeItem.last()==boutonMenu[1])
            {
                //Lancer l'éditeur
                cadre=new QGraphicsRectItem(0,0,640,640);
                cadre->setPos(320,40);
                cadre->setPen(*pen);
                sceneEditeur->addItem(cadre);
                sceneEditeur->addItem(curseur);
                jeu->setScene(sceneEditeur);
            }
        }
        if(jeu->scene()==sceneEditeur){

        }
    }
}

void MainWindow::on_sourisRelachee()
{

}
