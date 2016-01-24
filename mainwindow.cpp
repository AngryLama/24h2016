#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect cadre(320,40,640,640);
    pen=new QPen(Qt::white,5);

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

    //Création de scene gagne
    sceneGagne=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    texteGagne=new QGraphicsTextItem("GAGNE");
    texteGagne->setDefaultTextColor(QColor(Qt::white));
    texteGagne->setPos(width()/4,height()/2);
    texteGagne->setFont(QFont("Spylord Laser",250));
    sceneGagne->addItem(texteGagne);

    retourMenuGagne=new QGraphicsRectItem(0,0,120,120);
    retourMenuGagne->setBrush(QBrush(QPixmap(":/Images/Retour.png").scaledToHeight(retourMenuGagne->rect().height())));
    retourMenuGagne->setPos(width()-retourMenuGagne->rect().width()-50,height()-retourMenuGagne->rect().height()-50);

    //Création du curseur
    curseur=new QGraphicsRectItem(0,0,80,80);
    curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
    sceneMenu->addItem(curseur);

    //Création du sélecteur de niveau
    sceneNiveaux=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    //Création du jeu
    sceneJeu=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    cadreJeu=new QGraphicsRectItem(0,0,640,640);
    cadreJeu->setPen(*pen);
    cadreJeu->setPos(cadre.x(),cadre.y());
    sceneJeu->addItem(cadreJeu);

    for(int x=0;x<4;x++){
        selectionJeu[x]=new QGraphicsRectItem(0,0,80,80);
        selectionJeu[x]->setPos(1000,40+(110*x));
        selectionJeu[x]->setPen(*pen);
    }

    selectionJeu[0]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(selectionJeu[0]->rect().height())));
    selectionJeu[1]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(selectionJeu[0]->rect().height())));
    selectionJeu[2]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(selectionJeu[0]->rect().height())));
    selectionJeu[3]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(selectionJeu[0]->rect().height())));

    QPalette palette;
    QLabel *temp=new QLabel(this);
    palette.setColor(temp->backgroundRole(), Qt::white);
    palette.setColor(temp->foregroundRole(), Qt::white);
    for(int x=0;x<4;x++){
        affNbSelection[x]=new QLabel(QString::number(0),this);
        affNbSelection[x]->setFont(QFont("",40));
        affNbSelection[x]->setPalette(palette);
        affNbSelection[x]->setGeometry(selectionJeu[x]->pos().x()+selectionJeu[x]->rect().width()+50,selectionJeu[x]->pos().y(),80,80);
        affNbSelection[x]->hide();
        sceneJeu->addItem(selectionJeu[x]);
    }
    delete temp;

    for(int x=0;x<TAILLE;x++)
    {
        for(int y=0;y<TAILLE;y++)
        {
            tableauJeu[x][y]=new QGraphicsRectItem(0,0,80,80);
            tableauJeu[x][y]->setPos(cadre.x()+80*x,cadre.y()+80*y);
            sceneJeu->addItem(tableauJeu[x][y]);
        }
    }

    for(int x=0;x<TAILLE;x++)
    {
        departJeu[x]=new QGraphicsRectItem(0,0,80,80);
        departJeu[x]->setPos(200,cadre.y()+80*x);
        sceneJeu->addItem(departJeu[x]);
    }


    //Création de l'éditeur
    isModification=false;

    sceneEditeur=new QGraphicsScene(0,0,geometry().width()-10,geometry().height()-10);

    //Création des modèles
    for(int x=0;x<6;x++){
        selectionEditeur[x]=new QGraphicsRectItem(0,0,80,80);
        selectionEditeur[x]->setPos(1100,40+(110*x));
        selectionEditeur[x]->setPen(*pen);
    }

    selectionEditeur[0]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(selectionEditeur[0]->rect().height())));
    selectionEditeur[1]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(selectionEditeur[0]->rect().height())));
    selectionEditeur[2]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(selectionEditeur[0]->rect().height())));
    selectionEditeur[3]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(selectionEditeur[0]->rect().height())));
    selectionEditeur[4]->setBrush(QBrush(QPixmap(":/Laser/Mur.png").scaledToHeight(selectionEditeur[0]->rect().height())));
    selectionEditeur[5]->setBrush(QBrush(QPixmap(":/Images/chasseur.png").scaledToHeight(selectionEditeur[0]->rect().height())));

    for(int x=0;x<6;x++)
        sceneEditeur->addItem(selectionEditeur[x]);

    //Création des indicateurs de départ
    for(int x=0;x<TAILLE;x++)
    {
        indicDepart[x]=new QGraphicsRectItem(0,0,80,80);
        indicDepart[x]->setPos(200,cadre.y()+80*x);
        indicDepart[x]->setBrush(QBrush(QPixmap(":/Images/depart.png").scaledToHeight(selectionEditeur[0]->rect().height())));
        sceneEditeur->addItem(indicDepart[x]);
    }

    for(int x=0;x<TAILLE;x++)
    {
        for(int y=0;y<TAILLE;y++)
        {
            tableauEditeur[x][y]=new QGraphicsRectItem(0,0,80,80);
            tableauEditeur[x][y]->setPos(cadre.x()+80*x,cadre.y()+80*y);
            tableauEditeur[x][y]->setPen(*pen);
            sceneEditeur->addItem(tableauEditeur[x][y]);
        }
    }

    //Création du bouton enregistrer de l'éditeur
    btnSave = new QGraphicsRectItem(0,0,80,80);
    btnSave->setPos(40,40);
    btnSave->setBrush(QBrush(QPixmap(":/Images/Enregistrer.png").scaledToHeight(80)));
    sceneEditeur->addItem(btnSave);

    //Création du bouton menu principal
    btnMP = new QGraphicsRectItem(0,0,80,80);
    btnMP->setPos(40,120);
    btnMP->setBrush(QBrush(QPixmap(":/Images/Retour.png").scaledToHeight(80)));
    sceneEditeur->addItem(btnMP);

    //Création du selecteur de niveaux
    titre[0]=new QGraphicsTextItem("OFFICIEL");
    titre[0]->setDefaultTextColor(QColor(Qt::white));
    titre[0]->setPos(60,10);
    titre[0]->setFont(QFont("Spylord Laser",25));
    sceneNiveaux->addItem(titre[0]);

    titre[1]=new QGraphicsTextItem("CUSTOM");
    titre[1]->setDefaultTextColor(QColor(Qt::white));
    titre[1]->setPos(750,10);
    titre[1]->setFont(QFont("Spylord Laser",25));
    sceneNiveaux->addItem(titre[1]);

    ligne[0]=new QGraphicsLineItem(QLine(0,0,0,(height()/3)*2));
    ligne[0]->setPen(*pen);
    ligne[0]->setPos(width()/2,0);
    sceneNiveaux->addItem(ligne[0]);

    ligne[1]=new QGraphicsLineItem(QLine(0,0,width(),0));
    ligne[1]->setPen(*pen);
    ligne[1]->setPos(0,(height()/3)*2);
    sceneNiveaux->addItem(ligne[1]);

    cadreApercu=new QGraphicsRectItem(0,0,(height()/3)-20,(height()/3)-20);
    cadreApercu->setPen(*pen);
    cadreApercu->setPos((width()/4)-(cadreApercu->rect().width()/2)+50,(height()/3)*2+10);
    sceneNiveaux->addItem(cadreApercu);

    for(int x=0;x<TAILLE;x++)
    {
        for(int y=0;y<TAILLE;y++)
        {
            apercu[x][y]=new QGraphicsRectItem(0,0,cadreApercu->rect().height()/8,cadreApercu->rect().height()/8);
            apercu[x][y]->setPos(cadreApercu->x()+(cadreApercu->rect().height()/8)*x,cadreApercu->y()+(cadreApercu->rect().height()/8)*y);
            sceneNiveaux->addItem(apercu[x][y]);
        }
    }

    boutonNiveaux[0]=new QGraphicsRectItem(0,0,cadreApercu->pos().x()-50,(height()/3)-20);
    boutonNiveaux[0]->setBrush(QPixmap(":/Images/Play.png").scaledToHeight(boutonNiveaux[0]->rect().height()));
    boutonNiveaux[0]->setPos(10,(height()/3)*2+10);

    boutonNiveaux[1]=new QGraphicsRectItem(0,0,cadreApercu->pos().x()-50,(height()/3)-20);
    boutonNiveaux[1]->setBrush(QPixmap(":/Images/Editer fichier.png").scaledToHeight(boutonNiveaux[1]->rect().height()));
    boutonNiveaux[1]->setPos(width()/2.5,(height()/3)*2+10);

    boutonNiveaux[2]=new QGraphicsRectItem(0,0,cadreApercu->pos().x()-50,(height()/3)-20);
    boutonNiveaux[2]->setBrush(QPixmap(":/Images/Supprimer.png").scaledToHeight(boutonNiveaux[2]->rect().height()));
    boutonNiveaux[2]->setPos(width()/1.7,(height()/3)*2+10);

    boutonNiveaux[3]=new QGraphicsRectItem(0,0,cadreApercu->pos().x()-50,(height()/3)-20);
    boutonNiveaux[3]->setBrush(QPixmap(":/Images/Retour.png").scaledToHeight(boutonNiveaux[3]->rect().height()));
    boutonNiveaux[3]->setPos(width()/1.25,(height()/3)*2+10);
    sceneNiveaux->addItem(boutonNiveaux[3]);

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
    sceneJeu->clear();
    delete sceneJeu;
    sceneMenu->clear();
    delete sceneMenu;
    delete jeu;
    delete ui;
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
    if(jeu->scene()==sceneEditeur || jeu->scene()==sceneJeu || jeu->scene()==sceneNiveaux)
    {
        curseur->setPos(position);
    }
}

void MainWindow::on_sourisCliquee(int touche)
{
    curseur->setBrush(QBrush(QPixmap(":/Images/curseurRouge.png").scaledToHeight(curseur->rect().height())));
    QList<QGraphicsItem*> listeItem;
    listeItem = curseur->collidingItems();
    if(touche==Qt::LeftButton)
    {
        if(jeu->scene()==sceneMenu){
            if (listeItem.length()>0)
            {
                if(listeItem.last()==boutonMenu[0])
                {
                    //Choix du niveau
                    QSqlQuery query("select nom,off from Niveaux;");
                    if(query.exec()){
                        while(query.next()){
                            QGraphicsTextItem *temp=new QGraphicsTextItem(query.value(0).toString());
                            temp->setDefaultTextColor(QColor(Qt::white));
                            temp->setFont(QFont("Spylord Laser",15));
                            if(query.value(1).toInt())
                            {
                                offi<<temp;
                            }else{
                                custom<<temp;
                            }
                        }
                    } else qDebug() << "Echec de la requete";

                    //Affichage des niveaux
                    for(int x=0;x<offi.length();x++)
                    {
                        if(x<6)
                        {
                            offi[x]->setPos(40,120+55*x);
                            sceneNiveaux->addItem(offi[x]);
                        }
                    }

                    for(int x=0;x<custom.length();x++)
                    {
                        if(x<6)
                        {
                            custom[x]->setPos((width()/2)+40,120+55*x);
                            sceneNiveaux->addItem(custom[x]);
                        }
                    }

                    sceneNiveaux->addItem(curseur);
                    jeu->setScene(sceneNiveaux);
                }
                if(listeItem.last()==boutonMenu[1])
                {
                    //Lancer l'éditeur
                    sceneEditeur->addItem(curseur);
                    currentSelectionEditeur=-1;
                    jeu->setScene(sceneEditeur);
                }
            }
        }else{
            if(jeu->scene()==sceneEditeur){
                currentSelectionEditeur=-1;
                if (listeItem.length()>0)
                {
                    bool verifSelection=false;
                    for(int x=0;x<6;x++){
                        if(listeItem.last()==selectionEditeur[x]){
                            verifSelection=true;
                            currentSelectionEditeur=x;
                        }
                    }
                    if(verifSelection){
                        curseur->setBrush(selectionEditeur[currentSelectionEditeur]->brush());
                    }
                    if(listeItem.last() == btnSave){
                        if(!isModification)
                        {
                            //IHM pour demander le nom
                            dialNomNiv = new DialogNomNiveau();
                            if(!connect(dialNomNiv, SIGNAL(accepted(QString)), this, SLOT(on_DialogAccepted(QString))))
                                qDebug() << "Erreur connexion signal accepted au slot on_DialogAccepted";
                            dialNomNiv->exec();
                        }else{
                            on_DialogAccepted(tempModif);
                            tempModif.clear();
                        }
                    }
                    if(listeItem.last() == btnMP){
                        //Retour au menu principal
                        for(int y=0;y<TAILLE;y++)
                            indicDepart[y]->setBrush(QBrush(QPixmap(":/Images/depart.png").scaledToHeight(indicDepart[y]->rect().height())));
                        for(int x=0;x<TAILLE;x++)
                        {
                            for(int y=0;y<TAILLE;y++)
                            {
                                base[x][y].clear();
                                tableauEditeur[x][y]->setBrush(QBrush());
                            }
                        }
                        sceneMenu->addItem(curseur);
                        jeu->setScene(sceneMenu);
                    }
                }
            }else{
                if(jeu->scene()==sceneNiveaux){
                    if (listeItem.length()>0)
                    {
                        //Lance la partie
                        if(listeItem.last()==boutonNiveaux[0]){
                            for(int x=0;x<TAILLE;x++)
                            {
                                for(int y=0;y<TAILLE;y++)
                                {
                                    currentPattern[x][y].clear();
                                }
                            }
                            for(int x=0;x<4;x++)
                            {
                                affNbSelection[x]->show();
                            }
                            sceneJeu->addItem(curseur);
                            jeu->setScene(sceneJeu);
                        }else{
                            //Retour au menu
                            if(listeItem.last()==boutonNiveaux[3]){
                                qDeleteAll(offi);
                                offi.clear();
                                qDeleteAll(custom);
                                custom.clear();
                                for(int x=0;x<TAILLE;x++)
                                {
                                    for(int y=0;y<TAILLE;y++)
                                    {
                                        apercu[x][y]->setBrush(QBrush());
                                    }
                                }
                                sceneMenu->addItem(curseur);
                                jeu->setScene(sceneMenu);
                            }else{
                                //Suppression
                                if(listeItem.last()==boutonNiveaux[2]){
                                    QSqlQuery query;
                                    query.prepare("DELETE FROM Niveaux where nom=:nom AND off=:off");
                                    if(isOffiSelectionNiveaux)
                                        query.bindValue(":nom",offi[currentSelectionNiveaux]->toPlainText());
                                    else query.bindValue(":nom",custom[currentSelectionNiveaux]->toPlainText());
                                    query.bindValue(":off",isOffiSelectionNiveaux);
                                    if(query.exec())
                                        qDebug()<<"Suppression avec succès";
                                    else qDebug()<<"Echec de suppression";
                                    sceneNiveaux->removeItem(custom[currentSelectionNiveaux]);
                                    custom.removeAt(currentSelectionNiveaux);
                                    if(currentSelectionNiveaux<custom.length()){
                                        for(int x=currentSelectionNiveaux;x<custom.length();x++)
                                        {
                                            if(x<6){
                                                custom[x]->setPos((width()/2)+40,120+55*x);
                                                sceneNiveaux->addItem(custom[x]);
                                            }
                                        }
                                    }
                                    for(int x=0;x<TAILLE;x++)
                                    {
                                        for(int y=0;y<TAILLE;y++)
                                        {
                                            apercu[x][y]->setBrush(QBrush());
                                        }
                                    }
                                }else{
                                    //Modification
                                    if(listeItem.last() == boutonNiveaux[1])
                                    {
                                        isModification=true;
                                        tempModif=custom[currentSelectionNiveaux]->toPlainText();
                                        qDeleteAll(offi);
                                        offi.clear();
                                        qDeleteAll(custom);
                                        custom.clear();
                                        for(int x=0;x<TAILLE;x++)
                                        {
                                            for(int y=0;y<TAILLE;y++)
                                            {
                                                tableauEditeur[x][y]->setBrush(QBrush());
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Laser/Miroir GH.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="GH";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Laser/Miroir DH.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="DH";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Laser/Miroir GB.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="GB";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Laser/Miroir DB.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="DB";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Laser/Mur.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="M";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Laser/Mur.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                if(apercu[x][y]->brush().texture().toImage() == QPixmap(":/Images/chasseur.png").scaledToHeight(apercu[x][y]->rect().height()).toImage()) {
                                                    base[x][y]="TIE";
                                                    tableauEditeur[x][y]->setBrush(QBrush(QPixmap(":/Images/chasseur.png").scaledToHeight(tableauEditeur[x][y]->rect().height())));
                                                }
                                                apercu[x][y]->setBrush(QBrush());
                                            }
                                        }
                                        sceneEditeur->addItem(curseur);
                                        currentSelectionEditeur=-1;
                                        jeu->setScene(sceneEditeur);
                                    }else{
                                        //Item dynamique
                                        if(listeItem.last()!=boutonNiveaux[0] && listeItem.last()!=boutonNiveaux[1] && listeItem.last()!=boutonNiveaux[2] && listeItem.last()!=ligne[0] && listeItem.last()!=ligne[1] && listeItem.last()!=titre[0] && listeItem.last()!=titre[1]){
                                            for(int x=0;x<TAILLE;x++)
                                            {
                                                for(int y=0;y<TAILLE;y++)
                                                {
                                                    apercu[x][y]->setBrush(QBrush());
                                                }
                                            }
                                            for(int x=0;x<4;x++)
                                            {
                                                affNbSelection[x]->setText(QString::number(0));
                                            }
                                            sceneNiveaux->addItem(boutonNiveaux[0]);
                                        }
                                        //Apercu des niveaux
                                        int memX;
                                        bool verifOffi=false;
                                        for(int x=0;x<offi.length();x++)
                                        {
                                            if(listeItem.last()==offi[x])
                                            {
                                                verifOffi=true;
                                                memX=x;
                                            }
                                        }

                                        bool verifCustom=false;
                                        for(int x=0;x<custom.length();x++)
                                        {
                                            if(listeItem.last()==custom[x])
                                            {
                                                verifCustom=true;
                                                memX=x;
                                            }
                                        }

                                        if(verifOffi || verifCustom)
                                        {
                                            isOffiSelectionNiveaux=verifOffi;
                                            currentSelectionNiveaux=memX;
                                            QSqlQuery query;
                                            query.prepare("select grille0,grille1,grille2,grille3,grille4,grille5,grille6,grille7 from Niveaux where nom=:nom and off=:off;");
                                            if(verifOffi){
                                                sceneNiveaux->removeItem(boutonNiveaux[1]);
                                                sceneNiveaux->removeItem(boutonNiveaux[2]);
                                                query.bindValue(":nom",offi[memX]->toPlainText());
                                                query.bindValue(":off",true);
                                            }else{
                                                sceneNiveaux->addItem(boutonNiveaux[1]);
                                                sceneNiveaux->addItem(boutonNiveaux[2]);
                                                query.bindValue(":nom",custom[memX]->toPlainText());
                                                query.bindValue(":off",false);
                                            }
                                            if(query.exec())
                                            {
                                                while(query.next())
                                                {
                                                    for(int x=0;x<TAILLE;x++)
                                                    {
                                                        QStringList temp=query.value(x).toString().split(";");
                                                        for(int y=0; y<TAILLE; y++){
                                                            pattern[x][y]=temp[y];
                                                            if(temp[y] == "GH") {
                                                                affNbSelection[0]->setText(QString::number(affNbSelection[0]->text().toInt()+1));
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                            if(temp[y] == "DH") {
                                                                affNbSelection[1]->setText(QString::number(affNbSelection[1]->text().toInt()+1));
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                            if(temp[y] == "GB") {
                                                                affNbSelection[2]->setText(QString::number(affNbSelection[2]->text().toInt()+1));
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                            if(temp[y] =="DB") {
                                                                affNbSelection[3]->setText(QString::number(affNbSelection[3]->text().toInt()+1));
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                            if(temp[y] =="M") {
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Mur.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                            if(temp[y] == "TIE") {
                                                                apercu[x][y]->setBrush(QBrush(QPixmap(":/Images/chasseur.png").scaledToHeight(apercu[x][y]->rect().height())));
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }else{
                    if(jeu->scene()==sceneJeu)
                    {
                        if(listeItem.length()>0)
                        {
                            bool verifSelection=false;
                            for(int x=0;x<4;x++){
                                if(listeItem.last()==selectionJeu[x]){
                                    verifSelection=true;
                                    currentSelectionJeu=x;
                                }
                            }
                            if(verifSelection){
                                curseur->setBrush(selectionEditeur[currentSelectionJeu]->brush());
                            }
                        }
                    }else{
                        if(jeu->scene()==sceneGagne)
                        {
                            if(listeItem.length()>0)
                            {
                                if(listeItem.last()==retourMenuGagne)
                                {
                                    sceneMenu->addItem(curseur);
                                    jeu->setScene(sceneMenu);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(touche==Qt::RightButton)
    {
        curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
        if(jeu->scene()==sceneEditeur)
        {
            listeItem = curseur->collidingItems();
            if (listeItem.length()>0)
            {
                QList<QGraphicsItem*> listeItem;
                listeItem = curseur->collidingItems();
                if (listeItem.length()>0)
                {
                    bool verifTableau=false;
                    int cx,cy;
                    for(int x=0;x<TAILLE;x++)
                    {
                        for(int y=0;y<TAILLE;y++)
                        {
                            if(listeItem.last()==tableauEditeur[x][y])
                            {
                                verifTableau=true;
                                cx=x;
                                cy=y;
                            }
                        }
                    }
                    if(verifTableau)
                    {
                        base[cx][cy].clear();
                        tableauEditeur[cx][cy]->setBrush(QBrush());
                    }
                }
            }
        }
    }
}

void MainWindow::on_sourisRelachee()
{
    curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
    if(jeu->scene()==sceneEditeur)
    {
        QList<QGraphicsItem*> listeItem;
        listeItem = curseur->collidingItems();
        if (listeItem.length()>0)
        {
            bool verifTableau=false;
            int cx,cy;
            for(int x=0;x<TAILLE;x++)
            {
                for(int y=0;y<TAILLE;y++)
                {
                    if(listeItem.last()==tableauEditeur[x][y])
                    {
                        verifTableau=true;
                        cx=x;
                        cy=y;
                    }
                }
            }
            if(verifTableau && currentSelectionEditeur!=-1)
            {
                tableauEditeur[cx][cy]->setBrush(selectionEditeur[currentSelectionEditeur]->brush());
                curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
                switch (currentSelectionEditeur) {
                case 0:
                    base[cx][cy]="GH";
                    break;
                case 1:
                    base[cx][cy]="DH";
                    break;
                case 2:
                    base[cx][cy]="GB";
                    break;
                case 3:
                    base[cx][cy]="DB";
                    break;
                case 4:
                    base[cx][cy]="M";
                    break;
                case 5:
                    base[cx][cy]="TIE";
                    break;
                default:
                    break;
                }
            }else{
                bool verifDepart=false;
                for(int x=0;x<TAILLE;x++)
                {
                    if(listeItem.last()==indicDepart[x])
                    {
                        verifDepart=true;
                        cx=x;
                    }
                }
                if(verifDepart)
                {
                    for(int y=0;y<TAILLE;y++)
                        indicDepart[y]->setBrush(QBrush(QPixmap(":/Images/depart.png").scaledToHeight(indicDepart[y]->rect().height())));
                    indicDepart[cx]->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(indicDepart[cx]->rect().height())));
                    depart=cx;
                }else{
                    currentSelectionEditeur=-1;
                    curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
                }
            }
        }
    }else{
        if(jeu->scene()==sceneJeu)
        {
            QList<QGraphicsItem*> listeItem;
            listeItem = curseur->collidingItems();
            listeItem.removeOne(cadreJeu);
            if (listeItem.length()>0)
            {
                bool verifTableau=false;
                int cx,cy;
                for(int x=0;x<TAILLE;x++)
                {
                    for(int y=0;y<TAILLE;y++)
                    {
                        if(listeItem.last()==tableauJeu[x][y])
                        {
                            verifTableau=true;
                            cx=x;
                            cy=y;
                        }
                    }
                }
                if(verifTableau && currentSelectionJeu!=-1)
                {
                    curseur->setBrush(QBrush(QPixmap(":/Images/curseurVert.png").scaledToHeight(curseur->rect().height())));
                    if((affNbSelection[currentSelectionJeu]->text().toInt()-1)>-1)
                    {
                        tableauJeu[cx][cy]->setBrush(selectionJeu[currentSelectionJeu]->brush());
                        affNbSelection[currentSelectionJeu]->setText(QString::number(affNbSelection[currentSelectionJeu]->text().toInt()-1));
                        switch (currentSelectionJeu) {
                        case 0:
                            currentPattern[cx][cy]="GH";
                            break;
                        case 1:
                            currentPattern[cx][cy]="DH";
                            break;
                        case 2:
                            currentPattern[cx][cy]="GB";
                            break;
                        case 3:
                            currentPattern[cx][cy]="DB";
                            break;
                        default:
                            break;
                        }
                        bool verifGagne=true;
                        for(int x=0;x<TAILLE;x++)
                        {
                            for(int y=0;y<TAILLE;y++)
                            {
                                if(pattern[x][y]!=currentPattern[x][y])
                                    verifGagne=false;
                            }
                        }
                        if(verifGagne)
                        {
                            sceneGagne->addItem(curseur);
                            jeu->setScene(sceneGagne);
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_DialogAccepted(QString nom)
{
    bool verif=true;
    QSqlQuery queryVerif("select nom from Niveaux where off=0");
    if(queryVerif.exec())
    {
        while(queryVerif.next())
        {
            if(queryVerif.value(0).toString()==nom)
                verif=false;
        }
    }
    //Requete pour insérer le niveau
    QSqlQuery query;
    if(verif){
        query.prepare("insert into Niveaux (nom, grille0, grille1, grille2, grille3, grille4, grille5, grille6, grille7, off, depart) values (:nom, :grille0, :grille1, :grille2, :grille3, :grille4, :grille5, :grille6, :grille7, :off, :depart);");
        query.bindValue(":off",false);
    }else{
        query.prepare("UPDATE Niveaux set grille0=:grille0, grille1=:grille1, grille2=:grille2, grille3=:grille3, grille4=:grille4, grille5=:grille5, grille6=:grille6, grille7=:grille7, depart=:depart where nom=:nom;");
    }
    query.bindValue(":nom", nom);
    for(int x=0;x<TAILLE;x++){
        QString temp;
        for(int y=0;y<TAILLE;y++){
            temp+=base[x][y]+";";
        }
        temp=temp.left(temp.length()-1);
        query.bindValue(":grille"+QString::number(x),temp);
    }
    query.bindValue(":depart",depart);
    if(query.exec()){
        qDebug() << "Requete réussie";
    } else qDebug() << "Echec de la requete";
}
