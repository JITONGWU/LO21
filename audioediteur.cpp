#include "audioediteur.h"
#include <QMessageBox>
#include "relationmanager.h"
#include "relation.h"

AudioEditeur::AudioEditeur(Audio &aud, QWidget *parent, bool n, int r,bool a):

    QWidget(parent),audio(&aud), newAud(n), restaurer(r),arc(a)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de audio avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type AudioEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    desc=new QLineEdit(this);
    file=new QLineEdit(this);
    afile=new QLineEdit(this);
    save=new QPushButton("sauvegarder",this);
    archieve=new QPushButton("archiever",this);
    desarchieve=new QPushButton("archiever",this);
    supprimer =new QPushButton("supprimer",this);
    rest=new QPushButton("restaurer",this);
    start = new QPushButton("start audio",this);
    start->setVisible(false);

    sound = new QMediaPlayer;
    buttons = new QHBoxLayout;
    buttons->addWidget(archieve);
    buttons->addWidget(save);
    buttons->addWidget(supprimer);
    buttons->addWidget(rest);

    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    file1= new QLabel("file",this);
    afile1=new QLabel("fichier audio", this);

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

    cafile=new QHBoxLayout ;
    cafile->addWidget(afile1);
    cafile->addWidget(afile);

    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(cdesc);
   // couche->addLayout(cfile);
    couche->addLayout(cafile);
    couche->addWidget(start);
    couche->addLayout(buttons);

    if(arc==true){

   titre->setReadOnly(true);
   desc->setReadOnly(true);
   file->setReadOnly(true);
   afile->setReadOnly(true);


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
    else {save->setVisible(false);
        supprimer->setVisible(false);
        archieve->setVisible(false);}

    id->setText(audio->getId());
    titre->setText(audio->getTitle());
    desc->setText(audio->getDescpt());
    file->setText(audio->getFicher());
    afile->setText(audio->getAFile());

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(rest,SIGNAL(clicked()),this,SLOT(saveAudio()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveAudio()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(afile,SIGNAL(textEdited(QString)),this,SLOT(getFile()));
    QObject::connect(archieve,SIGNAL(clicked()),this,SLOT(archiverAudio()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(SupprimertousAudio()));
    QObject::connect(start,SIGNAL(clicked()),this,SLOT(play()));


}



void AudioEditeur::saveAudio(){
    QString avant=audio->getTitle()+audio->getDescpt();
    NotesManager::getManager().supprimerCoupleDansReference(id->text(),avant);
    if(restaurer >=0) {
          qDebug()<<"restaurer??";
            NotesManager::getManager().restaurerVersionNote(audio,restaurer);
            QMessageBox::information(this,"restauration","bien restaurer");
            setVisible(false);
    }
        else {

        if(newAud==false) {
            Note* audTemp= NotesManager::getManager().copieNote(id->text());
            audTemp->setDateDerModif(QDateTime::currentDateTime());
            audTemp->setTitle(titre->text());
            static_cast<Audio*>(audTemp)->setDesc(desc->text());
            static_cast<Audio*>(audTemp)->setAFile(afile->text());
            NotesManager::getManager().nouvelleVersion(audTemp);

           }
        else {
            audio->setId(id->text());
            audio->setTitle(titre->text());
            audio->setDesc(desc->text());
            audio->setAFile(afile->text());
            NotesManager::getManager().addNote(audio);
            emit SendToPage1(id->text());
        }
        QString apres= titre->text()+desc->text();
        NotesManager::getManager().addCoupleDansReference(id->text(),apres);
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);}

  DemandeSave();
}


void AudioEditeur::activerSave(QString){
    save->setEnabled(true);
}

void AudioEditeur::archiverAudio(){

    NotesManager::getManager().archiverNoteX(audio->getId());

    RelationManager::getManager().archiverLesCoupleContenantNoteX (audio->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

void AudioEditeur::SupprimertousAudio(){
    if(Reference::getRef()->supprimeroupas(audio->getId())){

   NotesManager::getManager().supprimertousNotes(audio->getId());
     RelationManager::getManager().supprimerLesCoupleContenantNoteX(audio->getId());
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(audio->getId());
         RelationManager::getManager().archiverLesCoupleContenantNoteX (audio->getId());

        QMessageBox::information(this,"archiver","bien archiver");
    }


}

void AudioEditeur::DemandeSave(){
for(NotesManager::Iterator it=NotesManager::getManager().getIterator();!it.isDone();it.next()){
    if(it.current().getEmp()=="A"){

            if(Reference::getRef()->supprimeroupas(it.current().getId())){
                 qDebug("sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");

                 QMessageBox message(QMessageBox::NoIcon, "Supprimer", "vous pouvez suppriemr le note  "+it.current().getId(), QMessageBox::Yes | QMessageBox::No,  NULL);

                 if(message.exec() == QMessageBox::Yes)
                 {
                         SupprimertousAudio2(it.current().getId());

                 } else{message.close();}


            }

    }

}

}


void AudioEditeur::desarchiver(){
    NotesManager::getManager().desarchiver(audio->getId());
}

void AudioEditeur::SupprimertousAudio2(QString id){
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

void AudioEditeur::getFile(){/////////////////////
    QString filename = QFileDialog::getOpenFileName(this,tr("Open audio"), "/home/new audio", tr("audio Files (*.mp3)"));
    file->setText(filename);
}
void AudioEditeur::play(){
    sound->play();
}
