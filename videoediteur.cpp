#include "videoediteur.h"
#include <QMessageBox>

VideoEditeur::VideoEditeur(Video &vid, QWidget *parent):

    QWidget(parent),video(&vid)
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
    couche->addWidget(save);

    id->setReadOnly(true);

    id->setText(video->getId());
    titre->setText(video->getTitle());
    desc->setText(video->getDescpt());
    file->setText(video->getFicher());
    vfile->setText(video->getVFile());

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveImage()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(vfile,SIGNAL(textChanged()),this,SLOT(activerSave()));


}
void VideoEditeur::saveVideo(){


   // image->setTitle(titre->text());
    //image->setDesc(desc->toPlainText());


    Video vidTemp = *video;
    vidTemp.setTitle(titre->text());
    vidTemp.setDesc(desc->toPlainText());

    NotesManager::getManager().addVideo(vidTemp);

    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void ImageEditeur::activerSave(QString){
    save->setEnabled(true);
}


