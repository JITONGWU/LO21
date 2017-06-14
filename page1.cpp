#include <QUndoCommand>
#include "page1.h"
Page1::Page1(QWidget *parent):QMainWindow(parent){


    QMenu *menuNotes = menuBar()->addMenu("&Notes");

    AjoutArticle = new QPushButton("&Ajouter une article", this);
    AjoutTache= new QPushButton("&Ajouter une tache",this);
    AjoutImage = new QPushButton("Ajouter un Image",this);
    AjoutAudio = new QPushButton("Ajouter un audio",this);
    AjoutVideo = new QPushButton("Ajouter un video",this);
    update=new QPushButton("update",this);
    buttons = new QHBoxLayout;
    buttons->addWidget(AjoutArticle);
    buttons->addWidget(AjoutTache);
    buttons->addWidget(AjoutImage);
    buttons->addWidget(AjoutAudio);
    buttons->addWidget(AjoutVideo);
    buttons->addWidget(update);


    QObject::connect(AjoutArticle,SIGNAL(clicked()),this,SLOT(ArticleEditeurVide()));
        QObject::connect(AjoutImage,SIGNAL(clicked()),this,SLOT(ImageEditeurVide()));
        QObject::connect(AjoutTache,SIGNAL(clicked()),this,SLOT(TacheEditeurVide()));
        QObject::connect(AjoutAudio,SIGNAL(clicked()),this,SLOT(AudioEditeurVide()));
        QObject::connect(AjoutVideo,SIGNAL(clicked()),this,SLOT(VideoEditeurVide()));


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
    QObject::connect(actionAnnuler,SIGNAL(triggered()),this,SLOT(undo()));
    QObject::connect(actionRetablir,SIGNAL(triggered()),this,SLOT(redo()));

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
            if(it.current().type()!=1) listWidget->addItem(it.current().getId());
        }
    }
    Taches->addItems(nm.ordonnerTaches());

    List = new QVBoxLayout;
    List->addWidget(listWidget);
    List->addWidget(NotesArchieve);
    List->addWidget(Taches);
    layout=new QHBoxLayout;
    couche = new QVBoxLayout;
    couche->addLayout(buttons);
    couche->addLayout(layout);
    couche->addWidget(listWidget2, 2, 0);


        Article *avide = new Article("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"");
        Image *ivide = new Image("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
        Tache *tvide = new Tache("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","",QDateTime::currentDateTime(),"");
        Audio *advide = new Audio("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
        Video *vvide = new Video("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");


        av = new ArticleEditeur(*avide,this,true,-1);
        iv = new ImageEditeur(*ivide,this,true,-1,false);
        tv = new TacheEditeur(*tvide,this,true,-1);
        adv = new AudioEditeur(*advide,this,true,-1);
        vv = new VideoEditeur(*vvide,this,true,-1);


        ae = new ArticleEditeur(*avide,this,false,-1);
        ie = new ImageEditeur(*ivide,this,false,-1);
        te = new TacheEditeur(*tvide,this,false,-1);
        ade = new AudioEditeur(*advide,this,false,-1);
        ve = new VideoEditeur(*vvide,this,false,-1);

        ar = new ArticleEditeur(*avide,this,false,0);
        ir = new ImageEditeur(*ivide,this,false,0);
        tar = new TacheEditeur(*tvide,this,false,0);
        adr = new AudioEditeur(*advide,this,false,0);
        vr = new VideoEditeur(*vvide,this,false,0);

        aa = new ArticleEditeur(*avide,this,false,-1,true);
        ia = new ImageEditeur(*ivide,this,false,-1,true);
        ta = new TacheEditeur(*tvide,this,false,-1,true);
        ada = new AudioEditeur(*advide,this,false,-1,true);
        va = new VideoEditeur(*vvide,this,false,-1,true);


    layout->addLayout(List);

    layout->addWidget(av,1,0);
        layout->addWidget(iv,1,0);
        layout->addWidget(tv,1,0);
        layout->addWidget(adv,1,0);
        layout->addWidget(vv,1,0);

        layout->addWidget(ar,1,0);
        layout->addWidget(ir,1,0);
        layout->addWidget(tar,1,0);
        layout->addWidget(adr,1,0);
        layout->addWidget(vr,1,0);


        layout->addWidget(ae,1,0);
        layout->addWidget(ie,1,0);
        layout->addWidget(te,1,0);
        layout->addWidget(ade,1,0);
        layout->addWidget(ve,1,0);

        layout->addWidget(aa,1,0);
        layout->addWidget(ia,1,0);
        layout->addWidget(ta,1,0);
        layout->addWidget(ada,1,0);
        layout->addWidget(va,1,0);


    layout->addWidget(vide,1,0);
    layout->addLayout(arbo);

    ie->setVisible(false);
       iv->setVisible(false);
       ae->setVisible(false);
       av->setVisible(false);
       te->setVisible(false);
       tv->setVisible(false);
       ade->setVisible(false);
       adv->setVisible(false);
       ve->setVisible(false);
       vv->setVisible(false);

       ar->setVisible(false);
       ir->setVisible(false);
       tar->setVisible(false);
       adr->setVisible(false);
       vr->setVisible(false);

       aa->setVisible(false);
       ia->setVisible(false);
       ta->setVisible(false);
       ada->setVisible(false);
       va->setVisible(false);


    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(NotesArchieve,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherNotesArch(QListWidgetItem*)));

    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherArbo(QListWidgetItem*)));
    QObject::connect(av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
    QObject::connect(iv,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
    QObject::connect(adv,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
    QObject::connect(vv,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));

    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));
    QObject::connect(update,SIGNAL(clicked()),this,SLOT(Update()));
    QObject::connect(NotesArchieve,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));
    QObject::connect(Taches,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(listWidget2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(restaurerVersion(QListWidgetItem*)));

}

void Page1::Update(){
    listWidget->clear();
    NotesArchieve->clear();
    Taches->clear();
    NotesManager &nm = NotesManager::getManager();
    for(NotesManager::Iterator it= nm.getIterator();!it.isDone();it.next()){
        if(it.current().getEmp()=="A") NotesArchieve->addItem(it.current().getId());
        else{
            if(it.current().type()!=1) listWidget->addItem(it.current().getId());
        }
    }
    Taches->addItems(nm.ordonnerTaches());
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

