#include "imageediteur.h"
#include <QMessageBox>
#include "imageediteur.h"
#include "relation.h"
#include "relationmanager.h"


ImageEditeur::ImageEditeur(Image &im, QWidget *parent, bool n, int r, bool a):

    QWidget(parent),image(&im),newI(n),restaurer(r),arc(a)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    desc=new QTextEdit(this);
    file=new QLineEdit(this);
    save=new QPushButton("sauvegarder",this);
    rest =new QPushButton("restaurer",this);
    supprimer=new QPushButton("supprimer",this);
    archieve =new QPushButton("archiver",this);
    desarchieve =new QPushButton("desarchiver",this);
    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    file1= new QLabel("file",this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);
    buttons = new QHBoxLayout;
    buttons->addWidget(archieve);
    buttons->addWidget(save);
    buttons->addWidget(supprimer);
        buttons->addWidget(desarchieve);

    buttons->addWidget(rest);


    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    cdesc=new QHBoxLayout ;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    cfile=new QHBoxLayout ;
    cfile->addWidget(file1);
    cfile->addWidget(file);

    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(cdesc);
    couche->addLayout(cfile);
    couche->addLayout(buttons);

    if(arc==true){

   titre->setReadOnly(true);
   desc->setReadOnly(true);
   file->setReadOnly(true);

   save->setVisible(false);
   supprimer->setVisible(false);
   archieve->setVisible(false);


   desarchieve->setEnabled(true);

    } else{



        save->setEnabled(true);
        archieve->setEnabled(true);
        desarchieve->setVisible(false);}

    if(n==false){
    id->setReadOnly(true);

    id->setText(image->getId());
    titre->setText(image->getTitle());
    desc->setText(image->getDescpt());
    file->setText(image->getFicher());
    }

    if(restaurer<0) { rest->setVisible(false);}
     else {save->setVisible(false); supprimer->setVisible(false); archieve->setVisible(false);}
    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(rest,SIGNAL(clicked()),this,SLOT(saveImage()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveImage()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(suppriemrtousImage()));
    QObject::connect(archieve,SIGNAL(clicked()),this,SLOT(archiverImage()));
    QObject::connect(desarchieve,SIGNAL(clicked()),this,SLOT(desarchiver()));

}

void ImageEditeur::activerSave(QString){
    save->setEnabled(true);
}



void ImageEditeur::saveImage(){
    QString avant=image->getTitle()+image->getDescpt();
    NotesManager::getManager().supprimerCoupleDansReference(id->text(),avant);
    if(restaurer >=0) {
      qDebug()<<"restaurer??";
        NotesManager::getManager().restaurerVersionNote(image,restaurer);
        QMessageBox::information(this,"restauration","bien restaurer");
        setVisible(false);
}
    else {

        if(newI==false) {
        qDebug()<<"newI=false";
        Note* imTemp= NotesManager::getManager().copieNote(id->text()); // dÃ©finir un constructeur de recopie s'il n'existe pas dÃ©jÃ
        imTemp->setTitle(titre->text());// Tester référence
        imTemp->setDateDerModif(QDateTime::currentDateTime());
        static_cast<Image*>(imTemp)->setDesc(desc->toPlainText()); // Tester référence
        static_cast<Image*>(imTemp)->setFile(file->text());//Tester référence
        imTemp->setEtat(non_traite);

        NotesManager::getManager().nouvelleVersion(imTemp);
       }
    else {
        image->setId(id->text());
        image->setTitle(titre->text());
        image->setDesc(desc->toPlainText());
        NotesManager::getManager().addNote(image);
        emit SendToPage1(id->text());
    }
        QString apres= titre->text()+desc->toPlainText();
        NotesManager::getManager().addCoupleDansReference(id->text(),apres);
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);}

  DemandeSave();
}














void ImageEditeur::archiverImage(){

    NotesManager::getManager().archiverNoteX(image->getId());
     RelationManager::getManager().archiverLesCoupleContenantNoteX (image->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

void ImageEditeur::suppriemrtousImage()   {
    if(Reference::getRef()->supprimeroupas(image->getId())){

    NotesManager::getManager().supprimertousNotes(image->getId());
    RelationManager::getManager().supprimerLesCoupleContenantNoteX(image->getId());
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(image->getId());
        RelationManager::getManager().archiverLesCoupleContenantNoteX (image->getId());

        QMessageBox::information(this,"archiver","bien archiver");
    }


}



void ImageEditeur::DemandeSave(){
for(NotesManager::Iterator it=NotesManager::getManager().getIterator();!it.isDone();it.next()){
    if(it.current().getEmp()=="A"){

            if(Reference::getRef()->supprimeroupas(it.current().getId())){
                 qDebug("sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");

                 QMessageBox message(QMessageBox::NoIcon, "Supprimer", "vous pouvez suppriemr le note  "+it.current().getId(), QMessageBox::Yes | QMessageBox::No,  NULL);

                 if(message.exec() == QMessageBox::Yes)
                 {
                         SupprimertousImage2(it.current().getId());

                 } else{message.close();}


            }

    }

}

}


void ImageEditeur::desarchiver(){
    NotesManager::getManager().desarchiver(image->getId());
}

void ImageEditeur::SupprimertousImage2(QString id){
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
