#include "tacheediteur.h"
#include <QMessageBox>

TacheEditeur::TacheEditeur(Image &ta, QWidget *parent):

    QWidget(parent),tache(&ta)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    action=new QTextEdit(this);
    echeance=new QDateEdit(this);
    priorite=new QComboBox(this);
    save=new QPushButton("sauvegarder",this);

    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    action=new QLabel("Action",this);
    echeance1= new QLabel("Echeance",this);
    priorite1=new QLabel("Priorite",this);

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


    cpriorite=new QHBoxLayout ;

    priorite->addItem("Forte");
    priorite->addItem("Normale");
    priorite->addItem("Faible");
    cpriorite->addWidget(priorite1);
    cpriorite->addWidget(priorite);


    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(caction);
    couche->addLayout(cecheance);
    couche->addWidget(cpriorite);

    id->setReadOnly(true);

    id->setText(tache->getId());
    titre->setText(tache->getTitle());
    action->setText(tache->getAction());
    echeance->setDate(tache->getExpDate());
    priorite->setText(tache->getPriority());


    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveTache()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(action,SIGNAL(textChanged()),this,SLOT(activerSave()));
    QObject::connect(echeance,SIGNAL(dateChanged()),this,SLOT(activerSave()));
    QObject::connect(priorite,SIGNAL(currentIndexChanged()),this,SLOT(activerSave()));


}
void TacheEditeur::saveTache(){


   // image->setTitle(titre->text());
    //image->setDesc(desc->toPlainText());


    Tache tTemp = *tache;
    tTemp.setTitle(titre->text());
    tTemp.setAction(action->toPlainText());
    tTemp.setExpDate(echeance->toString("dd.MM.yyyy"));
    tTemp.setPriority(priorite->SelectedItem.toString());

    NotesManager::getManager().addTache(tTemp);

    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void TacheEditeur::activerSave(QString){
    save->setEnabled(true);
}




