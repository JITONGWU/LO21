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
    Article avide("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"");

    Image ivide("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
    av = new ArticleEditeur(avide,this,true);
    iv = new ImageEditeur(ivide,this,true);

    layout->addLayout(List);

    layout->addWidget(av,1,0);
    layout->addWidget(iv,1,0);
    layout->addWidget(vide,1,0);
    layout->addLayout(arbo);

   // ie->setVisible(false);
    iv->setVisible(false);
   // ae->setVisible(false);
    av->setVisible(false);

    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherArbo(QListWidgetItem*)));


}
void Page1::afficherArbo(QListWidgetItem* item){
    listAscend->clear();
    listDescend->clear();
    RelationManager &rm= RelationManager::getManager();
    listAscend->addItems(rm.getAscendents(item->text()));
    listDescend->addItems(rm.getDescendents(item->text()));
}

void Page1::afficherWidget(QListWidgetItem* item){
    NotesManager &nm = NotesManager::getManager();

    if(nm.getNote(item->text()).type()==2){ //Article
        av->id->setText(item->text());
        av->titre->setText(nm.getNote(item->text()).getTitle());
        av->t->setText(static_cast<Article&>(nm.getNote(item->text())).getT());
    }


    iv->setVisible(false);
    vide->setVisible(false);
    av->setVisible(true);



}
void Page1::ArticleEditeurVide(){
     //ie->setVisible(false);
     //ae->setVisible(false);
     iv->setVisible(false);
     vide->setVisible(false);
     av->setVisible(true);
}
void Page1::ImageEditeurVide(){
  //  ie->setVisible(false);
   // ae->setVisible(false);
    av->setVisible(false);
    vide->setVisible(false);
    iv->setVisible(true);
}



void addCoupleDansReference(const QString& id,QString& s){
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

