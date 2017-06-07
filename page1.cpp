#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include  <QDate>
Page1::Page1(QWidget *parent)
{


    /*** MENU ***/






    // NOTES
    QMenu *menuNotes = menuBar()->addMenu("&Notes");

    AjoutArticle = new QPushButton("&Ajouter une article", this);
    AjoutTache= new QPushButton("&Ajouter une tache",this);
    AjoutImage = new QPushButton("Ajouter un Image",this);
    AjoutAudio = new QPushButton("Ajouter un audio",this);
    AjoutVideo = new QPushButton("Ajouter un video",this);
    buttons = new QHBoxLayout;
    buttons->addWidget(AjoutArticle);
    buttons->addWidget(AjoutTache);
    buttons->addWidget(AjoutImage);
    buttons->addWidget(AjoutAudio);
    buttons->addWidget(AjoutVideo);


    QObject::connect(AjoutArticle,SIGNAL(clicked()),this,SLOT(ArticleEditeurVide()));
    QObject::connect(AjoutImage,SIGNAL(clicked()),this,SLOT(ImageEditeurVide()));



    QMenu *fichiersRecents = menuNotes->addMenu("Fichiers &récents");
    fichiersRecents->addAction("Fichier_test.txt");



    // EDITION

    QMenu *menuEdition = menuBar()->addMenu("&Edition");

    QAction *actionAnnuler = new QAction("&Annuler", this);
    QAction *actionRetablir = new QAction("&Retablir", this);
    menuEdition->addAction(actionAnnuler);
    menuEdition->addAction(actionRetablir);
    actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
    actionRetablir->setShortcut(QKeySequence("Ctrl+Y"));


    /*** DOCKS ?  ***/


    // https://qt.developpez.com/doc/4.7/mainwindow/

  /*   QDockWidget *contentsWindow = new QDockWidget(tr("Visionneuse de notes"), this);
     contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea);

     addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

     QListWidget *headingList = new QListWidget(contentsWindow);
     contentsWindow->setWidget(headingList);
     setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

     */



    /*** ZONE CENTRALE ***/

    QDate d1(1997,3,5);
    QDate d2(1998,2,1);
    Article a("id_article","tiretitre",d1,d2,"N","sksdfdsfsdfaskd");
    Image i("id_image","myimage",d1,d2,"A","this is my image","this is my file");
    //initialiser les notes pour tester

    zoneCentrale = new QWidget;
    vide = new QWidget;
    ae = new ArticleEditeur(a,this);

    ie = new ImageEditeur(i,this);
    scrollNote = new QScrollArea;
    listWidget = new ListeNotes;
    layout=new QHBoxLayout;
    couche = new QVBoxLayout;
    couche->addLayout(buttons);
    couche->addLayout(layout);
    scrollNote->setWidgetResizable(true);
    Article avide("","",QDate::currentDate(),QDate::currentDate(),"N","");
    Article avide2("","2",QDate::currentDate(),QDate::currentDate(),"N","");
    Image ivide("","",QDate::currentDate(),QDate::currentDate(),"N","","");
    av = new ArticleEditeur(avide,this,true);
    iv = new ImageEditeur(ivide,this,true);

    layout->addWidget(listWidget,1,0);
    layout->addWidget(ae,1,0);
    layout->addWidget(av,1,0);
    layout->addWidget(ie,1,0);
    layout->addWidget(iv,1,0);
    layout->addWidget(vide,1,0);
    layout->addWidget(scrollNote,1,0);

    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);

    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);



    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));

}
void Page1::afficherWidget(QListWidgetItem* item){

    if(item->text()=="id_article") {
    Article avide2("","2",QDate::currentDate(),QDate::currentDate(),"N","");

    ie->setVisible(false);
    iv->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
    ae = new ArticleEditeur(avide2,this);
    ae->setVisible(true);
    }
    if(item->text()=="id_image") {
        ae->setVisible(false);
        iv->setVisible(false);
        av->setVisible(false);
        vide->setVisible(false);
        ie->setVisible(true);
    }

}
void Page1::ArticleEditeurVide(){
     ie->setVisible(false);
     ae->setVisible(false);
     iv->setVisible(false);
     vide->setVisible(false);
     av->setVisible(true);
}
void Page1::ImageEditeurVide(){
    ie->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
    iv->setVisible(true);
}
