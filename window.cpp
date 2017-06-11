#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include <QDateTime>
FenPrincipale::FenPrincipale() {
    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(this), tr("Notes"));
    onglet->addTab(new Page2(this), tr("Relations"));
    onglet->addTab(new Page3(this), tr("Corbeille"));

    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}

Page1::Page1(QWidget *parent):QMainWindow(parent){


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

    ascend = new QLabel;
    ascend->setText("Ascendentes");
    descend = new QLabel;
    descend->setText("Descendentes");
    arbo = new QVBoxLayout;
    listAscend = new QListWidget;
    listDescend = new QListWidget;
    arbo->addWidget(ascend);
    arbo->addWidget(listAscend);
    arbo->addWidget(descend);
    arbo->addWidget(listDescend);
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
  //  QObject::connect(actionAnnuler,SIGNAL(clicked()),this,SLOT());
  //  QObject::connect(actionRetablir,SIGNAL(clicked()),this,SLOT(ArticleEditeurVide()));


    /*** DOCKS ?  ***/


    // https://qt.developpez.com/doc/4.7/mainwindow/

     QDockWidget *contentsWindow = new QDockWidget(tr("Visionneuse de notes"), this);
     contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea);
     addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);
     QListWidget *headingList = new QListWidget(contentsWindow);
     contentsWindow->setWidget(headingList);
     setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);




    /*** ZONE CENTRALE ***/


    zoneCentrale = new QWidget;
    vide = new QWidget;



    listWidget = new QListWidget;
    listWidget2 = new ListeOldNotes;
    listWidget2->setVisible(false);
    NotesArchieve = new QListWidget;
    Taches = new QListWidget;

    NotesManager &nm = NotesManager::getManager();
    for(NotesManager::Iterator it= nm.getIterator();!it.isDone();it.next()){
        if(it.current().getEmp()=="A") NotesArchieve->addItem(it.current().getId());
        else{
            if(it.current().type()==1) Taches->addItem(it.current().getId());
            else listWidget->addItem(it.current().getId());
        }
    }

    List = new QVBoxLayout;
    List->addWidget(listWidget);
    List->addWidget(NotesArchieve);
    List->addWidget(Taches);
    layout=new QHBoxLayout;
    couche = new QVBoxLayout;
    couche->addLayout(buttons);
    couche->addLayout(layout);
    Article *avide = new Article("this is id","this is title",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"this is text");

    Image *ivide = new Image("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
    av = new ArticleEditeur(*avide,this,true);
    iv = new ImageEditeur(*ivide,this,true);
    ae = new ArticleEditeur(*avide,this,false);
    ie = new ImageEditeur(*ivide,this,false);

    layout->addLayout(List);

    layout->addWidget(av,1,0);
    layout->addWidget(iv,1,0);
    layout->addWidget(ae,1,0);
    layout->addWidget(ie,1,0);

    layout->addWidget(vide,1,0);
    layout->addLayout(arbo);

    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);

    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherArbo(QListWidgetItem*)));
    QObject::connect(av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));
}
void Page1::receive(QString id){
    listWidget->addItem(id);
}
void Page1::afficherArbo(QListWidgetItem* item){
    listAscend->clear();
    listDescend->clear();
    RelationManager &rm= RelationManager::getManager();
    listAscend->addItems(rm.getAscendents(item->text()));
    listDescend->addItems(rm.getDescendents(item->text()));
}

void Page1::afficherWidget(QListWidgetItem* item){
    //mettre tous les editeur setvisible(false)

    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
    NotesManager &nm = NotesManager::getManager();
    switch (nm.getNote(item->text()).type()) {   //choisir quelle editeur on a besoin.
   // case 1:break;
    case 2:
            Article &choisir=static_cast<Article&>(nm.getNote(item->text()));
            ae->article = &choisir;
            ae->id->setText(item->text());
            ae->titre->setText(choisir.getTitle());
            ae->t->setText(choisir.getT());
            qDebug()<<choisir.getT()<<"getT reussi\n";

            ae->setVisible(true);
        break;
   // case 3:
   //     break;
   // case 4:break;
   // case 5:break;
   //default: throw NotesException("error");
    //    break;
    }

}
void Page1::ArticleEditeurVide(){
    qDebug()<<av->article->getT()<<"lalaaall\n";
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(true);
    vide->setVisible(false);
}
void Page1::ImageEditeurVide(){
    ie->setVisible(false);
    iv->setVisible(true);
    ae->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
}


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
static void addCoupleDansReference(const QString& id,QString& s){
    NotesManager &nm = NotesManager::getManager();
    // lier tous les attributs de type string
    QStringList lst=s.split("ref{",QString::SkipEmptyParts,Qt::CaseSensitive);  // majuscule  ? minuscule ?
   for(int i=1;i<lst.count();i++)
    {
        QStringList l=lst.at(i).split("}",QString::SkipEmptyParts, Qt::CaseSensitive);
        QString idy=l.at(0);
        //std::cout<<rechercherNote(idy)<<std::endl;
        if(nm.rechercherNote(idy)) {//si on trouve les notes avec id= l.at(0)
            Couple *cp=new Couple("ref"+id,&(nm.getNote(id)),&(nm.getNote(idy)));
            Reference::getRef()->addCouple(cp);
    }
}
}

