#include "videoediteur.h"
#include <QMessageBox>
#include "relationmanager.h"
#include "relation.h"

VideoEditeur::VideoEditeur(Video &vid, QWidget *parent, bool n, int r, bool a):

    QWidget(parent),video(&vid), newVid(n), restaurer(r),arc(a)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    desc=new QTextEdit(this);
    file=new QLineEdit(this);
    vfile=new QLineEdit(this);
    save=new QPushButton("sauvegarder",this);
    archieve=new QPushButton("archiever",this);
    desarchieve=new QPushButton("desarchiver",this);
    supprimer =new QPushButton("supprimer",this);
    rest =new QPushButton("restaurer",this);

    buttons = new QHBoxLayout;
    buttons->addWidget(archieve);
    buttons->addWidget(save);
    buttons->addWidget(supprimer);
    buttons->addWidget(rest);


    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    file1= new QLabel("file",this);
    vfile1=new QLabel("fichier video", this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);


    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    cdesc=new QHBoxLayout ;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    cfile=new QHBoxLayout ;
    cfile->addWidget(file1);
    cfile->addWidget(file);

    cvfile=new QHBoxLayout ;
    cvfile->addWidget(vfile1);
    cvfile->addWidget(vfile);

    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(cdesc);
    couche->addLayout(cfile);
    couche->addLayout(cvfile);
    couche->addLayout(buttons);

    if(arc==true){

   titre->setReadOnly(true);
   desc->setReadOnly(true);
   file->setReadOnly(true);
   vfile->setReadOnly(true);


   save->setVisible(false);
   supprimer->setVisible(false);
   archieve->setVisible(false);


   desarchieve->setEnabled(true);

    } else{



        save->setEnabled(true);
        supprimer->setEnabled(true);
        archieve->setEnabled(true);
        desarchieve->setVisible(false);}

    if(n=false) {
    id->setReadOnly(true);}

    if(restaurer<0) { rest->setVisible(false);}
 else {save->setVisible(false); supprimer->setVisible(false); archieve->setVisible(false);}

    id->setText(video->getId());
    titre->setText(video->getTitle());
    desc->setText(video->getDescpt());
    file->setText(video->getFicher());
    vfile->setText(video->getVFile());

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(rest,SIGNAL(clicked()),this,SLOT(saveVideo()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveVideo()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(vfile,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(archieve,SIGNAL(clicked()),this,SLOT(archiverVideo()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(SupprimertousVideo()));



}
void VideoEditeur::saveVideo(){
    QString avant=video->getTitle()+video->getDescpt();
    NotesManager::getManager().supprimerCoupleDansReference(id->text(),avant);

    if(restaurer >=0) {
          qDebug()<<"restaurer??";
            NotesManager::getManager().restaurerVersionNote(video,restaurer);
            QMessageBox::information(this,"restauration","bien restaurer");
            setVisible(false);
    }
        else {

        if(newVid==false) {
            Note* vidTemp= NotesManager::getManager().copieNote(id->text());
            vidTemp->setDateDerModif(QDateTime::currentDateTime());
            vidTemp->setTitle(titre->text());
            static_cast<Video*>(vidTemp)->setDesc(desc->toPlainText());
            static_cast<Video*>(vidTemp)->setVFile(vfile->text());
            NotesManager::getManager().nouvelleVersion(vidTemp);

           }
        else {
            video->setId(id->text());
            video->setTitle(titre->text());
            video->setDesc(desc->toPlainText());
            video->setVFile(vfile->text());
            NotesManager::getManager().addNote(video);
            emit SendToPage1(id->text());
        }





    QString apres= titre->text()+desc->toPlainText();
    NotesManager::getManager().addCoupleDansReference(id->text(),apres);
         QMessageBox::information(this,"sauvegarder","bien sauvegarder");
         save->setEnabled(false);}

    DemandeSave();


}
void VideoEditeur::activerSave(QString){
    save->setEnabled(true);
}

void VideoEditeur::archiverVideo(){

    NotesManager::getManager().archiverNoteX(video->getId());

    RelationManager::getManager().archiverLesCoupleContenantNoteX (video->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

void VideoEditeur::SupprimertousVideo(){
    if(Reference::getRef()->supprimeroupas(video->getId())){

   NotesManager::getManager().supprimertousNotes(video->getId());
     RelationManager::getManager().supprimerLesCoupleContenantNoteX(video->getId());
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(video->getId());
         RelationManager::getManager().archiverLesCoupleContenantNoteX(video->getId());

        QMessageBox::information(this,"archiver","bien archiver");
    }


}



void VideoEditeur::DemandeSave(){
for(NotesManager::Iterator it=NotesManager::getManager().getIterator();!it.isDone();it.next()){
    if(it.current().getEmp()=="A"){

            if(Reference::getRef()->supprimeroupas(it.current().getId())){
                 qDebug("sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");

                 QMessageBox message(QMessageBox::NoIcon, "Supprimer", "vous pouvez suppriemr le note  "+it.current().getId(), QMessageBox::Yes | QMessageBox::No,  NULL);

                 if(message.exec() == QMessageBox::Yes)
                 {
                         SupprimertousVideo2(it.current().getId());

                 } else{message.close();}


            }

    }

}

}


void VideoEditeur::desarchiver(){
    NotesManager::getManager().desarchiver(video->getId());
}

void VideoEditeur::SupprimertousVideo2(QString id){
    if(Reference::getRef()->supprimeroupas(id)){

   NotesManager::getManager().supprimertousNotes(id);
     RelationManager::getManager().supprimerLesCoupleContenantNoteX(id);
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(id);
         RelationManager::getManager().archiverLesCoupleContenantNoteX (id);

        QMessageBox::information(this,"archiver","bien archiver");
    }

}

