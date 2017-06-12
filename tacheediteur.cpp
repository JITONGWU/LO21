#include "tacheediteur.h"
#include <QMessageBox>
#include "relationmanager.h"
#include "relation.h"

TacheEditeur::TacheEditeur(Tache &ta, QWidget *parent, bool n, int j, bool a):

    QWidget(parent),tache(&ta), newT(n), restaurer(j)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    action=new QTextEdit(this);
    echeance=new QDateTimeEdit(this);
   // priorite=new QComboBox(this);

    save=new QPushButton("sauvegarder",this);
    archieve=new QPushButton("archiever",this);
    desarchieve=new QPushButton("archiever",this);

    supprimer =new QPushButton("supprimer",this);
    rest =new QPushButton("Restaurer",this);

    buttons = new QHBoxLayout;

    buttons->addWidget(archieve);
    buttons->addWidget(save);
    buttons->addWidget(supprimer);
    buttons->addWidget(rest);


    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    action1=new QLabel("Action",this);
    echeance1= new QLabel("Echeance",this);
 //   priorite1=new QLabel("Priorite",this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);


    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    caction=new QHBoxLayout ;
    caction->addWidget(action1);
    caction->addWidget(action);

    cecheance=new QHBoxLayout ;
    cecheance->addWidget(echeance1);
    cecheance->addWidget(echeance);


    /*cpriorite=new QHBoxLayout ;

    priorite->addItem("Forte");
    priorite->addItem("Normale");
    priorite->addItem("Faible");
    cpriorite->addWidget(priorite1);
    cpriorite->addWidget(priorite);*/


    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(caction);
    couche->addLayout(cecheance);
  //  couche->addWidget(cpriorite);
    couche->addLayout(buttons);

    if(arc==true){

   titre->setReadOnly(true);
   titre->setReadOnly(true);
   action->setReadOnly(true);
   echeance->setReadOnly(true);

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


    save->setEnabled(false);

    id->setText(tache->getId());
    titre->setText(tache->getTitle());
    action->setText(tache->getAction());
    echeance->setDateTime(tache->getExpDate());
  //  priorite->setText(tache->getPriority());

if(restaurer<0) { rest->setVisible(false);}
 else {save->setVisible(false); supprimer->setVisible(false); archieve->setVisible(false);}



    setLayout(couche);

    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveTache()));
    QObject::connect(rest,SIGNAL(clicked()),this,SLOT(saveTache()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(action,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(echeance,SIGNAL(dateChanged()),this,SLOT(activerSave()));
    //QObject::connect(priorite,SIGNAL(currentIndexChanged()),this,SLOT(activerSave()));
    QObject::connect(archieve,SIGNAL(clicked()),this,SLOT(archiverTache()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(SupprimertousTache()));




}
void TacheEditeur::saveTache(){


   // image->setTitle(titre->text());
    //image->setDesc(desc->toPlainText());


 /*  Tache tTemp = *tache;
    tTemp.setTitle(titre->text());
    tTemp.setAction(action->toPlainText());
    tTemp.setExpDate(echeance->toString("dd.MM.yyyy"));
  //  tTemp.setPriority(priorite->SelectedItem.toString());

    NotesManager::getManager().addTache(tTemp); */
    if(restaurer >=0) {
        NotesManager::getManager().restaurerVersionNote(tache,restaurer);
        QMessageBox::information(this,"restauration","bien restaurer");
}
    else {


            if(newT==false) {
            Note* tTemp = NotesManager::getManager().copieNote(id->text());
            tTemp->setTitle(titre->text());

            tTemp->setDateDerModif(QDateTime::currentDateTime());
            static_cast<Tache*>(tTemp)->setAction(action->toPlainText());
            static_cast<Tache*>(tTemp)->setExpDate(echeance->dateTime());

            NotesManager::getManager().nouvelleVersion(tTemp);

       }
    else {
        tache->setId(id->text());
        tache->setTitle(titre->text());
        tache->setAction(action->toPlainText());
        tache->setExpDate(echeance->dateTime());
        NotesManager::getManager().addNote(tache);
        emit SendToPage1(id->text());
    }


    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false); }

}
void TacheEditeur::activerSave(QString){
    save->setEnabled(true);
}


void TacheEditeur::archiverTache(){

    NotesManager::getManager().archiverNoteX(tache->getId());

    RelationManager::getManager().archiverLesCoupleContenantNoteX (tache->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

void TacheEditeur::SupprimertousTache(){
    if(Reference::getRef()->supprimeroupas(tache->getId())){

   NotesManager::getManager().supprimertousNotes(tache->getId());
     RelationManager::getManager().supprimerLesCoupleContenantNoteX(tache->getId());
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(tache->getId());
         RelationManager::getManager().archiverLesCoupleContenantNoteX(tache->getId());

        QMessageBox::information(this,"archiver","bien archiver");
    }


}


