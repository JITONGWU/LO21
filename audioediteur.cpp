#include "audioediteur.h"
#include <QMessageBox>

AudioEditeur::AudioEditeur(Audio &aud, QWidget *parent, bool n, int r):

    QWidget(parent),audio(&aud), newAud(n), restaurer(r)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    desc=new QTextEdit(this);
    file=new QLineEdit(this);
    afile=new QLineEdit(this);
    save=new QPushButton("sauvegarder",this);
    archieve=new QPushButton("archiever",this);
    supprimer =new QPushButton("supprimer",this);
    rest=new QPushButton("restaurer",this);

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
    couche->addLayout(cfile);
    couche->addLayout(cafile);
    couche->addLayout(buttons);

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
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(afile,SIGNAL(textChanged()),this,SLOT(activerSave()));


}
void AudioEditeur::saveAudio(){


   // image->setTitle(titre->text());
    //image->setDesc(desc->toPlainText());

/*
    Audio adTemp = *audio;
    adTemp.setTitle(titre->text());
    adTemp.setDesc(desc->toPlainText());

    NotesManager::getManager().addAudio(adTemp); */


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
        static_cast<Audio*>(audTemp)->setDesc(desc->toPlainText());
        static_cast<Audio*>(audTemp)->setAFile(afile->text());
        NotesManager::getManager().nouvelleVersion(audTemp);

       }
    else {
        audio->setId(id->text());
        audio->setTitle(titre->text());
        audio->setDesc(desc->toPlainText());
        audio->setAFile(afile->text());
        NotesManager::getManager().addNote(audio);
        emit SendToPage1(id->text());
    }

    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
}
void AudioEditeur::activerSave(QString){
    save->setEnabled(true);
}



