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
    QFontDatabase::addApplicationFont(":/Laser Rod.ttf"); //Laser Rod

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

    texteGagne=new QGraphicsRectItem(0,0,1280,360);
    texteGagne->setBrush(QBrush(QPixmap(":/Images/Gagne.png").scaledToHeight(texteGagne->rect().height())));
    texteGagne->setPos(0,height()/4);
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
        selectionJeu[x]->setPos(1050,40+(110*x));
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
        affNbSelection[x]->setFont(QFont("Laser Rod",40));
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
    scrollOffi=1;
    scrollCustom=1;
    titre[0]=new QGraphicsTextItem("OFFICIEL");
    titre[0]->setDefaultTextColor(QColor(Qt::white));
    titre[0]->setPos(width()/6,10);
    titre[0]->setFont(QFont("Laser Rod",25));
    sceneNiveaux->addItem(titre[0]);

    titre[1]=new QGraphicsTextItem("CUSTOM");
    titre[1]->setDefaultTextColor(QColor(Qt::white));
    titre[1]->setPos((width()/2)+(width()/6),10);
    titre[1]->setFont(QFont("Laser Rod",25));
    sceneNiveaux->addItem(titre[1]);

    ligne[0]=new QGraphicsLineItem(QLine(0,0,0,(height()/3)*2));
    ligne[0]->setPen(*pen);
    ligne[0]->setPos(width()/2,0);
    sceneNiveaux->addItem(ligne[0]);

    ligne[1]=new QGraphicsLineItem(QLine(0,0,width(),0));
    ligne[1]->setPen(*pen);
    ligne[1]->setPos(0,(height()/3)*2);
    sceneNiveaux->addItem(ligne[1]);

    boutonScroll[0]=new QGraphicsRectItem(0,0,40,40);
    boutonScroll[0]->setBrush(QBrush(QPixmap(":/Images/Gauche.png").scaledToHeight(boutonScroll[0]->rect().height())));
    boutonScroll[0]->setPos(60,ligne[1]->pos().y()-60);
    sceneNiveaux->addItem(boutonScroll[0]);

    boutonScroll[1]=new QGraphicsRectItem(0,0,40,40);
    boutonScroll[1]->setBrush(QBrush(QPixmap(":/Images/Droite.png").scaledToHeight(boutonScroll[1]->rect().height())));
    boutonScroll[1]->setPos(ligne[0]->pos().x()-105,ligne[1]->pos().y()-60);
    sceneNiveaux->addItem(boutonScroll[1]);

    boutonScroll[2]=new QGraphicsRectItem(0,0,40,40);
    boutonScroll[2]->setBrush(QBrush(QPixmap(":/Images/Gauche.png").scaledToHeight(boutonScroll[2]->rect().height())));
    boutonScroll[2]->setPos(ligne[0]->pos().x()+60,ligne[1]->pos().y()-60);
    sceneNiveaux->addItem(boutonScroll[2]);

    boutonScroll[3]=new QGraphicsRectItem(0,0,40,40);
    boutonScroll[3]->setBrush(QBrush(QPixmap(":/Images/Droite.png").scaledToHeight(boutonScroll[3]->rect().height())));
    boutonScroll[3]->setPos(width()-105,ligne[1]->pos().y()-60);
    sceneNiveaux->addItem(boutonScroll[3]);

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
    sceneGagne->clear();
    delete sceneGagne;
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

void MainWindow::calculLaser(short x, short y, short sens)
{
    bool verifObjet=false;
    switch (sens) {
    case GD:
    {
        while(x<TAILLE && !verifObjet)
        {
            if(currentPattern[x][y]=="")
            {
                tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Laser droit H.png").scaledToHeight(tableauJeu[x][depart]->rect().height())));
                x++;
            }else{
                verifObjet=true;
            }
        }
        break;
    }
    case DG:
    {
        while(x>-1 && !verifObjet)
        {
            if(currentPattern[x][y]=="")
            {
                tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Laser droit H.png").scaledToHeight(tableauJeu[x][depart]->rect().height())));
                x--;
            }else{
                verifObjet=true;
            }
        }
        break;
    }
    case HB:
    {
        while(y<TAILLE && !verifObjet)
        {
            if(currentPattern[x][y]=="")
            {
                tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Laser droit V.png").scaledToHeight(tableauJeu[x][depart]->rect().height())));
                y++;
            }else{
                verifObjet=true;
            }
        }
        break;
    }
    case BH:
    {
        while(y>-1 && !verifObjet)
        {
            if(currentPattern[x][y]=="")
            {
                tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Laser droit V.png").scaledToHeight(tableauJeu[x][depart]->rect().height())));
                y--;
            }else{
                verifObjet=true;
            }
        }
        break;
    }
    default:
        break;
    }
    if(verifObjet)
    {
        if(currentPattern[x][y]=="GH")
        {
            tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GH laser.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
            if(sens==GD)
                calculLaser(x,y-1,BH);
            if(sens==HB)
                calculLaser(x-1,y,DG);
        }
        if(currentPattern[x][y]=="DH")
        {
            tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DH laser.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
            if(sens==HB)
                calculLaser(x+1,y,GD);
            if(sens==DG)
                calculLaser(x,y-1,BH);
        }
        if(currentPattern[x][y]=="GB")
        {
            tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir GB laser.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
            if(sens==GD)
                calculLaser(x,y+1,HB);
            if(sens==BH)
                calculLaser(x-1,y,DG);
        }
        if(currentPattern[x][y]=="DB")
        {
            tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Miroir DB laser.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
            if(sens==BH)
                calculLaser(x+1,y,GD);
            if(sens==DG)
                calculLaser(x,y+1,HB);
        }
        if(currentPattern[x][y]=="TIE")
        {
            for(int x=0;x<TAILLE;x++)
            {
                for(int y=0;y<TAILLE;y++)
                {
                    tableauJeu[x][y]->setBrush(QBrush());
                }
            }
            for(int x=0;x<4;x++)
                affNbSelection[x]->hide();
            sceneGagne->addItem(retourMenuGagne);
            sceneGagne->addItem(curseur);
            jeu->setScene(sceneGagne);
        }
    }
}

void MainWindow::affichageNiveaux(int colonnes, short mode)
{
    //Requete
    if(mode==OFFI)
    {
        qDeleteAll(offi);
        offi.clear();
    }else{
        qDeleteAll(custom);
        custom.clear();
    }
    QSqlQuery query("select nom,off from Niveaux;");
    if(query.exec()){
        while(query.next()){
            QGraphicsTextItem *temp=new QGraphicsTextItem(query.value(0).toString());
            temp->setDefaultTextColor(QColor(Qt::white));
            temp->setFont(QFont("Laser Rod",15));
            if(query.value(1).toInt() && mode==OFFI)
            {
                offi<<temp;
            }
            if(!query.value(1).toInt() && mode==CUSTOM){
                custom<<temp;
            }
        }
    } else qDebug() << "Echec de la requete";

    //Affichage
    colonnes*=5;
    if(mode==OFFI)
    {
        scrollOffi/=5;
        for(int x=0;x<offi.length();x++)
        {
            if(x<colonnes)
            {
                offi[x]->setPos(40,120+55*x);
                sceneNiveaux->addItem(offi[x]);
            }
            if(x>=colonnes && x<(colonnes*2))
            {
                offi[x]->setPos(220,120+55*(x-5));
                sceneNiveaux->addItem(offi[x]);
            }
            if(x>=(colonnes*2) && x<(colonnes*3))
            {
                offi[x]->setPos(400,120+55*(x-10));
                sceneNiveaux->addItem(offi[x]);
            }
        }
    }else{
        scrollCustom/=5;
        for(int x=0;x<custom.length();x++)
        {
            if(x<colonnes)
            {
                custom[x]->setPos((width()/2)+40,120+55*x);
                sceneNiveaux->addItem(custom[x]);
            }
            if(x>=colonnes && x<(colonnes*2))
            {
                custom[x]->setPos((width()/2)+220,120+55*(x-5));
                sceneNiveaux->addItem(custom[x]);
            }
            if(x>=(colonnes*2) && x<(colonnes*3))
            {
                custom[x]->setPos((width()/2)+400,120+55*(x-10));
                sceneNiveaux->addItem(custom[x]);
            }
        }
    }
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
    if(jeu->scene()==sceneEditeur || jeu->scene()==sceneJeu || jeu->scene()==sceneNiveaux || jeu->scene()==sceneGagne)
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
                    //Affichage des niveaux
                    affichageNiveaux(1,OFFI);
                    affichageNiveaux(1,CUSTOM);

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
                        listeItem.removeOne(ligne[1]);
                        //Lance la partie
                        if(listeItem.last()==boutonNiveaux[0]){
                            for(int x=0;x<TAILLE;x++)
                            {
                                for(int y=0;y<TAILLE;y++)
                                {
                                    currentPattern[x][y].clear();
                                    if(pattern[x][y]=="TIE")
                                    {
                                        currentPattern[x][y]="TIE";
                                        tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Images/chasseur.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
                                    }
                                    if(pattern[x][y]=="M")
                                    {
                                        currentPattern[x][y]="M";
                                        tableauJeu[x][y]->setBrush(QBrush(QPixmap(":/Laser/Mur.png").scaledToHeight(tableauJeu[x][y]->rect().height())));
                                    }
                                }
                            }
                            for(int x=0;x<4;x++)
                            {
                                affNbSelection[x]->show();
                            }
                            calculLaser(0,depart,GD);
                            sceneJeu->addItem(retourMenuGagne);
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
                                        //Scroll
                                        if(listeItem.last()==boutonScroll[0])
                                        {
                                            if(scrollOffi>1)
                                                affichageNiveaux(scrollOffi-1,OFFI);
                                        }else{
                                            if(listeItem.last()==boutonScroll[1])
                                            {
                                                if(scrollOffi<offi.length()/5)
                                                    affichageNiveaux(scrollOffi+1,OFFI);
                                            }else{
                                                if(listeItem.last()==boutonScroll[2])
                                                {
                                                    if(scrollCustom>1)
                                                        affichageNiveaux(scrollCustom-1,CUSTOM);
                                                }else{
                                                    if(listeItem.last()==boutonScroll[3])
                                                    {
                                                        if(scrollCustom<custom.length()/5)
                                                            affichageNiveaux(scrollCustom+1,CUSTOM);
                                                    }else{
                                                        for(int x=0;x<4;x++)
                                                            listeItem.removeOne(boutonScroll[x]);
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
                                                            query.prepare("select grille0,grille1,grille2,grille3,grille4,grille5,grille6,grille7,depart from Niveaux where nom=:nom and off=:off;");
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
                                                                    for(int y=0;y<TAILLE;y++)
                                                                        departJeu[y]->setBrush(QBrush());
                                                                    departJeu[query.value(8).toInt()]->setBrush(QBrush(QPixmap(":/Images/fighter.png").scaledToHeight(departJeu[query.value(8).toInt()]->rect().height())));
                                                                    depart=query.value(8).toInt();
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
                            if(listeItem.last()==retourMenuGagne)
                            {
                                for(int x=0;x<TAILLE;x++)
                                {
                                    for(int y=0;y<TAILLE;y++)
                                    {
                                        tableauJeu[x][y]->setBrush(QBrush());
                                    }
                                }
                                for(int x=0;x<4;x++)
                                    affNbSelection[x]->hide();
                                sceneMenu->addItem(curseur);
                                jeu->setScene(sceneMenu);
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
                                if(currentPattern[x][y]!="" && currentPattern[x][y]!="M" && currentPattern[x][y]!="TIE")
                                {
                                    verifTableau=true;
                                    cx=x;
                                    cy=y;
                                }
                            }
                        }
                    }
                    if(verifTableau)
                    {
                        if(currentPattern[cx][cy]=="GH")
                        {
                            affNbSelection[0]->setText(QString::number(affNbSelection[0]->text().toInt()+1));
                        }
                        if(currentPattern[cx][cy]=="DH")
                        {
                            affNbSelection[1]->setText(QString::number(affNbSelection[1]->text().toInt()+1));
                        }
                        if(currentPattern[cx][cy]=="GB")
                        {
                            affNbSelection[2]->setText(QString::number(affNbSelection[2]->text().toInt()+1));
                        }
                        if(currentPattern[cx][cy]=="DB")
                        {
                            affNbSelection[3]->setText(QString::number(affNbSelection[3]->text().toInt()+1));
                        }
                        currentPattern[cx][cy].clear();
                        tableauJeu[cx][cy]->setBrush(QBrush());

                    }
                    for(int x=0;x<TAILLE;x++)
                    {
                        for(int y=0;y<TAILLE;y++)
                        {
                            if(currentPattern[x][y]=="")
                                tableauJeu[x][y]->setBrush(QBrush());
                        }
                    }
                    calculLaser(0,depart,GD);
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
                    departEditeur=cx;
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
                            if(currentPattern[x][y]!="M" && currentPattern[x][y]!="TIE")
                            {
                                verifTableau=true;
                                cx=x;
                                cy=y;
                            }
                        }
                    }
                }
                if(verifTableau && currentSelectionJeu>-1)
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
                        for(int x=0;x<TAILLE;x++)
                        {
                            for(int y=0;y<TAILLE;y++)
                            {
                                if(currentPattern[x][y]=="")
                                    tableauJeu[x][y]->setBrush(QBrush());
                            }
                        }
                        calculLaser(0,depart,GD);
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
    query.bindValue(":depart",departEditeur);
    QMessageBox message;
    if(query.exec()){
        message.setText("Ajouté avec succès");
    } else message.setText("Echec de l'ajout");
    message.exec();
    sceneMenu->addItem(curseur);
    jeu->setScene(sceneMenu);
}
