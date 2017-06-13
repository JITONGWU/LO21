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
    QObject::connect(actionAnnuler,SIGNAL(clicked()),this,SLOT(undo()));
    QObject::connect(actionRetablir,SIGNAL(clicked()),this,SLOT(redo()));

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
    QObject::connect(tv,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
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
            if(it.current().type()==1) Taches->addItem(it.current().getId());
            else listWidget->addItem(it.current().getId());
        }
    }
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

        ve->setVisible(false);
        vv->setVisible(false);
        ie->setVisible(false);
        iv->setVisible(false);
        ae->setVisible(false);
        av->setVisible(false);
        te->setVisible(false);
        tv->setVisible(false);
        ade->setVisible(false);
        adv->setVisible(false);
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
        vide->setVisible(false);
    NotesManager &nm = NotesManager::getManager();
    switch (nm.getNote(item->text()).type()) {   //choisir quelle editeur on a besoin.
         case 1:{
                Tache &choisir=static_cast<Tache&>(nm.getNote(item->text()));
                te->tache = &choisir;
                te->id->setText(item->text());
                te->titre->setText(choisir.getTitle());
                te->action->setText(choisir.getAction());
               // te->echeance->setDateTime(choisir.getExpDate());
                te->setVisible(true);}
            break;
        case 2: {
                Article &choisir=static_cast<Article&>(nm.getNote(item->text()));
                ae->article = &choisir;
                ae->id->setText(item->text());
                ae->titre->setText(choisir.getTitle());
                ae->t->setText(choisir.getT());
                qDebug()<<choisir.getT()<<"getT reussi\n";
                ae->setVisible(true);}
            break;
        case 3:
                 {
                Image &choisir=static_cast<Image&>(nm.getNote(item->text()));
                ie->image = &choisir;
                ie->id->setText(item->text());
                ie->titre->setText(choisir.getTitle());
                ie->desc->setText(choisir.getDescpt());
                ie->file->setText(choisir.getFicher());

                ie->movie->setFileName(choisir.getFicher());
                ie->position->setMovie(ie->movie);
                ie->movie->start();
                ie->position->show();

                ie->setVisible(true);}
            break;
       case 4: {
                Audio &choisir=static_cast<Audio&>(nm.getNote(item->text()));
                ade->audio = &choisir;
                ade->id->setText(item->text());
                ade->titre->setText(choisir.getTitle());
                ade->desc->setText(choisir.getDescpt());
                ade->file->setText(choisir.getFicher());
                ade->afile->setText(choisir.getAFile());

                ade->sound->setMedia(QUrl::fromLocalFile(ade->afile->text()));
                ade->start->setVisible(true);

                ade->setVisible(true);}
            break;

        case 5: { Video &choisir=static_cast<Video&>(nm.getNote(item->text()));
                ve->video = &choisir;
                ve->id->setText(item->text());
                ve->titre->setText(choisir.getTitle());
                ve->desc->setText(choisir.getDescpt());
                ve->file->setText(choisir.getFicher());
                ve->vfile->setText(choisir.getVFile());

                ve->player->setMedia(QUrl::fromLocalFile(ve->vfile->text()));
                ve->vw->setGeometry(100,100,300,400);
                ve->vw->show();
                ve->player->play();

                ve->setVisible(true);}break;
       //default: throw NotesException("error");
        //    break;
        }
    }

void Page1::afficherNotesArch(QListWidgetItem* item){

    //mettre tous les editeur setvisible(false)

        ve->setVisible(false);
        vv->setVisible(false);
        ie->setVisible(false);
        iv->setVisible(false);
        ae->setVisible(false);
        av->setVisible(false);
        te->setVisible(false);
        tv->setVisible(false);
        ade->setVisible(false);
        adv->setVisible(false);
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
        vide->setVisible(false);
    NotesManager &nm = NotesManager::getManager();
    switch (nm.getNote(item->text()).type()) {   //choisir quelle editeur on a besoin.
         case 1:{
                Tache &choisir=static_cast<Tache&>(nm.getNote(item->text()));
                ta->tache = &choisir;
                ta->id->setText(item->text());
                ta->titre->setText(choisir.getTitle());
                ta->action->setText(choisir.getAction());
               // te->echeance->setDateTime(choisir.getExpDate());


                ta->setVisible(true);}
            break;
        case 2: {
                qDebug() <<"archive article" ;
                Article &choisir=static_cast<Article&>(nm.getNote(item->text()));
                aa->article = &choisir;
                aa->id->setText(item->text());
                aa->titre->setText(choisir.getTitle());
                aa->t->setText(choisir.getT());
                qDebug()<<choisir.getT()<<"getT reussi\n";

                aa->setVisible(true);}
            break;
        case 3:
                 {
                Image &choisir=static_cast<Image&>(nm.getNote(item->text()));
                ia->image = &choisir;
                ia->id->setText(item->text());
                ia->titre->setText(choisir.getTitle());
                ia->desc->setText(choisir.getDescpt());
                ia->file->setText(choisir.getFicher());

                ia->setVisible(true);}
            break;
       case 4: {
                Audio &choisir=static_cast<Audio&>(nm.getNote(item->text()));
                ada->audio = &choisir;
                ada->id->setText(item->text());
                ada->titre->setText(choisir.getTitle());
                ada->desc->setText(choisir.getDescpt());
                ada->file->setText(choisir.getFicher());
                ada->afile->setText(choisir.getAFile());

                ada->setVisible(true);}
            break;

        case 5: { Video &choisir=static_cast<Video&>(nm.getNote(item->text()));
                va->video = &choisir;
                va->id->setText(item->text());
                va->titre->setText(choisir.getTitle());
                va->desc->setText(choisir.getDescpt());
                va->file->setText(choisir.getFicher());
                va->vfile->setText(choisir.getVFile());

                va->setVisible(true);}break;
       //default: throw NotesException("error");
        //    break;
        }

    }
void Page1::ArticleEditeurVide(){
    Article *avid = new Article("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"");
    av->article=avid;
    av->id->clear();
    av->titre->clear();
    av->t->clear();

    qDebug()<<av->article->getT()<<"lalaaall\n";
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(true);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
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
    vide->setVisible(false);
}

void Page1::AudioEditeurVide(){
    Audio *advid = new Audio("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
    adv->id->clear();
    adv->titre->clear();
    adv->desc->clear();
    adv->file->clear();
    adv->afile->clear();
    adv->audio=advid;
   // qDebug()<<av->article->getT()<<"lalaaall\n";
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(true);
    ade->setVisible(false);
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
    vide->setVisible(false);
}

void Page1::ImageEditeurVide(){
    Image *ivid = new Image("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
    iv->id->clear();
    iv->titre->clear();
    iv->desc->clear();
    iv->file->clear();
    iv->image=ivid;
    ie->setVisible(false);
    iv->setVisible(true);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
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
    vide->setVisible(false);
}
void Page1::TacheEditeurVide(){
    Tache *tvid = new Tache("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","",QDateTime::currentDateTime(),"");
    tv->id->clear();
    tv->titre->clear();
    tv->action->clear();
    tv->echeance->clear();
    tv->tache=tvid;
    ie->setVisible(false);
    iv->setVisible(false);
    te->setVisible(false);
    tv->setVisible(true);
    ae->setVisible(false);
    av->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
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
    vide->setVisible(false);
}


void Page1::VideoEditeurVide(){
    Video *vvid = new Video("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
    vv->id->clear();
    vv->titre->clear();
    vv->desc->clear();
    vv->file->clear();
    vv->vfile->clear();
    vv->video=vvid;
    ie->setVisible(false);
    iv->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(true);
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
    vide->setVisible(false);
}


ListeNotes::ListeNotes() {

 for(unsigned int i=0;i<NotesManager::getManager().getNb();i++)
     if(NotesManager::getManager().getNote(i)->getEmp()=="N")
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
          qDebug()<<j<<it.current().getId(); qDebug()<<"item clické"<<ident;
          if (id==ident) {
              qDebug()<<"id==ident";
              this->setVisible(true);

              QString num=QString::number(i+1);qDebug()<<num;
              qDebug()<<"j dans afficher OldNotes"<<j;
              this->insertItem(j, new QListWidgetItem("Version anterieure n" +  num));
              i++;}
          else { QListWidgetItem *item2 = new QListWidgetItem("");
                this->insertItem(j, item2); item2->setHidden(true);
                this->setRowHidden(j, true);
    }
                j++;
                it.next();
            }




        }


void Page1::restaurerVersion(QListWidgetItem* item) {
    ve->setVisible(false);
    vv->setVisible(false);
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    ade->setVisible(false);
    adv->setVisible(false);
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
    vide->setVisible(false);

    unsigned int j=item->listWidget()->row(item);
    qDebug()<<"restaurer versions :"<<j;
    qDebug()<<NotesManager::getManager().getOldVersion(j)->getId();
    if (NotesManager::getManager().getOldVersion(j)==NULL) { throw NotesException("error, impossible de trouver cette note");}
    switch(NotesManager::getManager().getOldVersion(j)->type()) {

        case 1:{
            Tache &choisir=static_cast<Tache&>(NotesManager::getManager().getOldVersion2(j));
            tar->tache = &choisir;
            tar->id->setText(choisir.getId());
            qDebug()<<"choisir id"<<choisir.getId();
            tar->titre->setText(choisir.getTitle());
            tar->action->setText(choisir.getAction());
           // te->echeance->setDateTime(choisir.getExpDate());
            tar->setRest(j);

            tar->setVisible(true);}break;
       case 2:{
            Article &choisir=static_cast<Article&>(NotesManager::getManager().getOldVersion2(j));
            qDebug()<<choisir.getId()<<choisir.getTitle()<<choisir.getT();
            ar->article = &choisir;
            ar->id->setText(choisir.getId());
            ar->titre->setText(choisir.getTitle());
            ar->t->setText(choisir.getT());
           // te->echeance->setDateTime(choisir.getExpDate());
            ar->setRest(j);

            ar->setVisible(true);}break;
         case 3:{
            Image &choisir=static_cast<Image&>(NotesManager::getManager().getOldVersion2(j));
            ir->image = &choisir;
            ir->id->setText(choisir.getId());
            ir->titre->setText(choisir.getTitle());
            ir->desc->setText(choisir.getDescpt());
            ir->file->setText(choisir.getFicher());
            ir->setRest(j);

            ir->setVisible(true);}break;
          case 4:{
            Audio &choisir=static_cast<Audio&>(NotesManager::getManager().getOldVersion2(j));
            adr->audio = &choisir;
            adr->id->setText(choisir.getId());
            adr->titre->setText(choisir.getTitle());
            adr->desc->setText(choisir.getDescpt());
            adr->file->setText(choisir.getFicher());
            adr->afile->setText(choisir.getAFile());
            adr->setRest(j);

            adr->setVisible(true);}break;
          case 5:{
            Video &choisir=static_cast<Video&>(NotesManager::getManager().getOldVersion2(j));
            vr->video = &choisir;
            vr->id->setText(choisir.getId());
            vr->titre->setText(choisir.getTitle());
            vr->desc->setText(choisir.getDescpt());
            vr->file->setText(choisir.getFicher());
            vr->vfile->setText(choisir.getVFile());
            vr->setRest(j);

            vr->setVisible(true);}break;
           default: qDebug()<<"default"; break;
          }
    }
