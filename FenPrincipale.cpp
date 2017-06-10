#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include <QDate>
FenPrincipale::FenPrincipale(QWidget *parent):QMainWindow(parent) {

    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(this), tr("Notes"));
    onglet->addTab(new Page2(this), tr("Relations"));
    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}

Page1::Page1(QWidget *parent):QMainWindow(parent){


    QMenu *menuNotes = menuBar()->addMenu("&Notes");

    AjoutArticle = new QPushButton("&Ajouter un article", this);
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


    QObject::connect(AjoutArticle,SIGNAL(clicked()),this,SLOT(ajouterArticle()));
    QObject::connect(AjoutImage,SIGNAL(clicked()),this,SLOT(ajouterImage()));



    QMenu *fichiersRecents = menuNotes->addMenu("Fichiers &rÃ©cents");
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


    zoneCentrale = new QWidget;
    vide = new QWidget;


    scrollNote = new QScrollArea;
    listWidget = new ListeNotes;
    listWidget2 = new ListeOldNotes;
    listWidget2->setVisible(false);
    layout=new QHBoxLayout;
    couche = new QVBoxLayout;
    couche->addLayout(buttons);
    couche->addLayout(layout);
    scrollNote->setWidgetResizable(true);
    Article avide("","",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"");

    Image ivide("","",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"","");
    av = new ArticleEditeur(avide,this,true);
    iv = new ImageEditeur(ivide,this,true);

   Article avide2("","2",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"");
    ae = new ArticleEditeur(avide2,this);


   Image ivide2("","2",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"","");
    ie = new ImageEditeur(ivide2,this);

    layout->addWidget(listWidget,1,0);

    layout->addWidget(av,1,0);

    layout->addWidget(iv,1,0);
    layout->addWidget(vide,1,0);
    layout->addWidget(scrollNote,1,0);
    couche->addWidget(listWidget2, 2, 0);

    //ie->setVisible(false);
    iv->setVisible(false);
    //ae->setVisible(false);
    av->setVisible(false);

    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);



    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
   QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));


}



void Page1::afficherWidget(QListWidgetItem* item){

    if(item->text()=="id_article") {
    //Article avide2("","2",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"");

    ie->setVisible(false);
    iv->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
    //ae = new ArticleEditeur(avide2,this);
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


     //ie->setVisible(false);
     //ae->setVisible(false);
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


void Page1::ajouterArticle() {
    qDebug()<<"ajouterArticle";
    Article avide("","",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"");
    ArticleEditeur ajoutArticle(avide,this, true);
    ajoutArticle.exec();

}

void Page1::ajouterImage() {
   Image ivide2("","2",QDate::currentDate(),QDate::currentDate(),"N",non_traite,0,"","");
    ImageEditeur ajoutImage(ivide2,this, true);
    ajoutImage.exec();
}

Page2::Page2(QWidget *parent):QMainWindow(parent)
{
    zoneCentrale = new QWidget;


    AjoutRelation = new QPushButton("ajouter une relation",this);
   /*
    * QObject::connect(AjoutRelation,SIGNAL(clicked()),this,SLOT(RelationEditeurVide()));



    listR = new ListeRelations; */
    vide = new QWidget;
/*
    Relation rvide("","");
    re = new RelationEditeur(rvide,this);
    rv = new RelationEditeur(rvide,this);
    scrollRelation = new QScrollArea;
*/
    layout =new QHBoxLayout;
    couche = new QVBoxLayout;
  /*  layout->addWidget(listR,1,0);
    layout->addWidget(re,1,0);
    layout->addWidget(rv,1,0); */
    layout->addWidget(vide,1,0);
/* re->setVisible(false);
    rv->setVisible(false);
    vide->setVisible(true);
    couche->addWidget(AjoutRelation); */
    couche->addLayout(layout);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);



//    QObject::connect(listR,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));




}
 /*

void Page2::afficherWidget(QListWidgetItem* item){

    re->titre->setText(item->text());
    re->desc->setText(RelationManager::getManager().getRelation(item->text())->getDesc());

    for(unsigned int i=0;i<RelationManager::getManager().size();i++)
    listR->addItem(RelationManager::getManager().at(i)->getTitre());

    rv->setVisible(false);
    vide->setVisible(false);
    re->setVisible(true);


}
void Page2::RelationEditeurVide(){

    re->setVisible(false);
    vide->setVisible(false);
    rv->setVisible(true);
}

*/

ListeNotes::ListeNotes() {

 for(unsigned int i=0;i<NotesManager::getManager().getNb();i++)
        insertItem(i,new QListWidgetItem(NotesManager::getManager().getNote(i)->getId()));

    }
ListeOldNotes::ListeOldNotes() {}



void ListeOldNotes::afficherOldNotes(QListWidgetItem *item) {
    clear();
    unsigned int i=0; unsigned int j=0;
    NotesManager::OldIterator it=NotesManager::getManager().getOldIterator();

    while(!it.isDone()) {

      QString ident=item->text();
      QString id= it.current().getId();
      if (id==ident) {
          this->setVisible(true);

          QString num=QString::number(i+1);
          this->insertItem(i, new QListWidgetItem("Version anterieure n" +  num));
          i++;}

      else {setVisible(false);}
      j++;
      it.next();

    }

 // QObject::connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(restaurerVersion(j)));


}
/*

void ListeOldNotes::restaurerVersion(int j) {

    if (NotesManager::getManager().getOldVersion(j)==NULL) { throw NotesException("error, impossible de trouver cette note");}
    switch(NotesManager::getManager().getOldVersion(j)->type()) {
          case 2:{
             Note *article = NotesManager::getManager().copieOldNote(j);
             ae = new ArticleEditeur(article,this,false,true);
             ae->exec();

          }break;
         case 1:{
              Tache *tache = NotesManager::getManager().copieOldNote(j);
              restaurerTache = new TacheEditeur(tache,Page1,false,true);

          }break;

          case 3:{
              Note *image = NotesManager::getManager().copieOldNote(j);
              ie = new ImageEditeur(image,this,false,true);
              ie->exec();


          }break;

          case 4:{
              Audio *audio = NotesManager::getManager().copieOldNote(j);
              restaurerAudio = new AudioEditeur(audio,Page1,false,true);


          }break;

          case 5:{
              Video *video = NotesManager::getManager().copieOldNote(j);
              restaurerVideo = new VideoEditeur(video,Page1,false,true);


          }break;

           default: qDebug()<<"default"; break;
          }

    }


*/
