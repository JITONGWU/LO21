#include "audioediteur.h"
#include <QMessageBox>

AudioEditeur::AudioEditeur(Audio &aud, QWidget *parent):

    QWidget(parent),audio(&aud)
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

    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    file1= new QLabel("file",this);
    afile1=new QLabel("fichier video", this);

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
    couche->addWidget(save);

    id->setReadOnly(true);

    id->setText(audio->getId());
    titre->setText(audio->getTitle());
    desc->setText(audio->getDescpt());
    file->setText(audio->getFicher());
    afile->setText(audio->getVFile());

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveImage()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(afile,SIGNAL(textChanged()),this,SLOT(activerSave()));


}
void AudioEditeur::saveAudio(){


   // image->setTitle(titre->text());
    //image->setDesc(desc->toPlainText());


    Audio adTemp = *audio;
    adTemp.setTitle(titre->text());
    adTemp.setDesc(desc->toPlainText());

    NotesManager::getManager().addAudio(adTemp);

    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void ImageEditeur::activerSave(QString){
    save->setEnabled(true);
}



