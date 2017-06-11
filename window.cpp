#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
//#include "relationediteur.h"
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
  //  QObject::connect(actionAnnuler,SIGNAL(clicked()),this,SLOT());
  //  QObject::connect(actionRetablir,SIGNAL(clicked()),this,SLOT(ArticleEditeurVide()));


    /*** DOCKS ?  ***/


    // https://qt.developpez.com/doc/4.7/mainwindow/




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


    Article *avide = new Article("this is id","this is title",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"this is text");
    Image *ivide = new Image("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
    Tache *tvide = new Tache("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","",QDateTime::currentDateTime(),"");
    Audio *advide = new Audio("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
    Video *vvide = new Video("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");


    av = new ArticleEditeur(*avide,this,true,-1);
    iv = new ImageEditeur(*ivide,this,true,-1);
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

    vide->setVisible(true);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(Taches,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherArbo(QListWidgetItem*)));
    QObject::connect(av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString)));
    QObject::connect(Taches,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));
    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),listWidget2,SLOT(afficherOldNotes(QListWidgetItem*)));
    QObject::connect(listWidget2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(restaurerVersion(QListWidgetItem*)));
}
/*void Page1::receive(QString id){
    listWidget->addItem(id);
}
void Page1::afficherArbo(QListWidgetItem* item){
    listAscend->clear();
    listDescend->clear();
    RelationManager &rm= RelationManager::getManager();
    listAscend->addItems(rm.getAscendents(item->text()));
    listDescend->addItems(rm.getDescendents(item->text()));
}
*/
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

            ade->setVisible(true);}
        break;

    case 5: { Video &choisir=static_cast<Video&>(nm.getNote(item->text()));
            ve->video = &choisir;
            ve->id->setText(item->text());
            ve->titre->setText(choisir.getTitle());
            ve->desc->setText(choisir.getDescpt());
            ve->file->setText(choisir.getFicher());
            ve->vfile->setText(choisir.getVFile());

            ve->setVisible(true);}break;
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
    vide->setVisible(false);
}

void Page1::AudioEditeurVide(){
   // qDebug()<<av->article->getT()<<"lalaaall\n";
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(true);
    ve->setVisible(false);
    vv->setVisible(false);
        ar->setVisible(false);
    ir->setVisible(false);
    tar->setVisible(false);
    adr->setVisible(false);
    vr->setVisible(false);
    vide->setVisible(false);
}

void Page1::ImageEditeurVide(){
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
    vide->setVisible(false);
}
void Page1::TacheEditeurVide(){
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
    vide->setVisible(false);
}


void Page1::VideoEditeurVide(){
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

 // QObject::connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(restaurerVersion(j)));



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
/*
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

*/
