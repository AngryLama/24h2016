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
    if( !connect(jeu,SIGNAL(sourisCliquee(int)),this,SLOT(on_sourisCliquee(int))) )
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

    //Création du curseur du menu
    curseurMenu=new QGraphicsRectItem(0,0,80,80);
    curseurMenu->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(curseurMenu->rect().height())));
    sceneMenu->addItem(curseurMenu);

    //Création du curseur en jeu
    curseurJeu=new QGraphicsRectItem(0,0,80,80);
    curseurJeu->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(curseurJeu->rect().height())));

    //Création du sélecteur de niveau
    sceneNiveaux=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    //Création du jeu
    sceneJeu=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    //Création de l'éditeur
    QRect cadreEditeur(320,40,640,640);

    sceneEditeur=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);
    pen=new QPen(Qt::white,5);

    //Création des modèles
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

    //Création des indicateurs de départ
    for(int x=0;x<TAILLE;x++)
    {
        indicDepart[x]=new QGraphicsRectItem(0,0,80,80);
        indicDepart[x]->setPos(200,cadreEditeur.y()+80*x);
        indicDepart[x]->setBrush(QBrush(QPixmap(":/Images/depart.png").scaledToHeight(selection[0]->rect().height())));
        sceneEditeur->addItem(indicDepart[x]);
    }

    for(int x=0;x<TAILLE;x++)
    {
        for(int y=0;y<TAILLE;y++)
        {
            tableau[x][y]=new QGraphicsRectItem(0,0,80,80);
            tableau[x][y]->setPos(cadreEditeur.x()+80*x,cadreEditeur.y()+80*y);
            tableau[x][y]->setPen(*pen);
            sceneEditeur->addItem(tableau[x][y]);
        }
    }

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
    sceneNiveaux->clear();
    delete sceneNiveaux;
    delete sceneJeu;
    sceneMenu->clear();
    delete sceneMenu;
    delete jeu;
    delete ui;
}

void MainWindow::on_sourisBougee(QPoint position)
{
    if(jeu->scene()==sceneMenu){
        curseurMenu->setPos(position);
        //Verification de la collision
        QList<QGraphicsItem*> listeItem = curseurMenu->collidingItems();
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
    if(jeu->scene()==sceneEditeur || jeu->scene()==sceneJeu)
    {
        curseurJeu->setPos(position);
    }
}

void MainWindow::on_sourisCliquee(int touche)
{
    QList<QGraphicsItem*> listeItem;
    if(touche==Qt::LeftButton)
    {
        if(jeu->scene()==sceneMenu){
            listeItem = curseurMenu->collidingItems();
            if (listeItem.length()>0)
            {
                if(listeItem.last()==boutonMenu[0])
                {
                    //Choix du niveau

                    /*cadre=new QGraphicsRectItem(0,0,640,640);
                    cadre->setPos(320,40);
                    cadre->setPen(*pen);
                    sceneJeu->addItem(cadre);
                    sceneJeu->addItem(curseur);
                    jeu->setScene(sceneJeu);*/
                }
                if(listeItem.last()==boutonMenu[1])
                {
                    //Lancer l'éditeur
                    sceneEditeur->addItem(curseurJeu);
                    currentSelection=-1;
                    jeu->setScene(sceneEditeur);
                }
            }
        }else{
            if(jeu->scene()==sceneEditeur){
                listeItem = curseurJeu->collidingItems();
                if (listeItem.length()>0)
                {
                    bool verifSelection=false;
                    for(int x=0;x<6;x++){
                        if(listeItem.last()==selection[x]){
                            verifSelection=true;
                            currentSelection=x;
                        }
                    }
                    if(verifSelection){
                        curseurJeu->setBrush(selection[currentSelection]->brush());
                    }
                }
            }
        }
    }
    if(touche==Qt::RightButton)
    {
        if(jeu->scene()==sceneEditeur)
        {
            listeItem = curseurJeu->collidingItems();
            if (listeItem.length()>0)
            {
                QList<QGraphicsItem*> listeItem;
                listeItem = curseurJeu->collidingItems();
                if (listeItem.length()>0)
                {
                    bool verifTableau=false;
                    int cx,cy;
                    for(int x=0;x<TAILLE;x++)
                    {
                        for(int y=0;y<TAILLE;y++)
                        {
                            if(listeItem.last()==tableau[x][y])
                            {
                                verifTableau=true;
                                cx=x;
                                cy=y;
                            }
                        }
                    }
                    if(verifTableau)
                    {
                        tableau[cx][cy]->setBrush(QBrush());
                    }
                }
            }
        }
    }
}

void MainWindow::on_sourisRelachee()
{
    if(jeu->scene()==sceneEditeur)
    {
        QList<QGraphicsItem*> listeItem;
        listeItem = curseurJeu->collidingItems();
        if (listeItem.length()>0)
        {
            bool verifTableau=false;
            int x,y;
            for(x=0;x<TAILLE;x++)
            {
                for(y=0;y<TAILLE;y++)
                {
                    if(listeItem.last()==tableau[x][y])
                    {
                        verifTableau=true;
                    }
                }
            }
            if(verifTableau && currentSelection!=-1)
            {
                tableau[x][y]->setBrush(curseurJeu->brush());
                curseurJeu->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(curseurJeu->rect().height())));
                switch (currentSelection) {
                case 0:
                    base[x][y]="GH";
                    break;
                case 1:
                    base[x][y]="DH";
                    break;
                case 2:
                    base[x][y]="GB";
                    break;
                case 3:
                    base[x][y]="DB";
                    break;
                case 4:
                    base[x][y]="MH";
                    break;
                case 5:
                    base[x][y]="MV";
                    break;
                default:
                    break;
                }
            }else{
                bool verifDepart=false;
                int x;
                for(x=0;x<TAILLE;x++)
                {
                    if(listeItem.last()==indicDepart[x])
                    {
                        verifDepart=true;
                    }
                }
                if(verifDepart)
                {
                    for(int y=0;y<TAILLE;y++)
                        indicDepart[y]->setBrush(QBrush(QPixmap(":/Images/depart.png").scaledToHeight(indicDepart[x]->rect().height())));
                    indicDepart[x]->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(indicDepart[x]->rect().height())));
                    depart=x;
                }else{
                    currentSelection=-1;
                    curseurJeu->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(curseurJeu->rect().height())));
                }
            }
        }
    }
}
