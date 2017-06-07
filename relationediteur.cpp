#include "relationediteur.h"
#include <QMessageBox>

RelationEditeur::RelationEditeur(Relation &re, QWidget *parent):

    QWidget(parent),relation(&re)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de image avec le parametre im
{
    //tous les widget créés ont comme parent l'objet de type ImageEditeur


    titre=new QLineEdit(this);
    desc=new QTextEdit(this);
    couples = new QListWidget(this);

    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    couples1= new QLabel("couples",this);

    save=new QPushButton("sauvegarder",this);
    supprimer=new QPushButton("supprimer",this);
    ajouter=new QPushButton("ajouter",this);




    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    cdesc=new QHBoxLayout ;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    ccouples=new QHBoxLayout ;
    ccouples->addWidget(couples1);
    ccouples->addWidget(couples);

    button = new QHBoxLayout;
    button->addWidget(supprimer);
    button->addWidget(ajouter);

    couche=new QVBoxLayout;

    couche->addLayout(ctitre);
    couche->addLayout(cdesc);
    couche->addLayout(ccouples);
    couche->addLayout(button);
    couche->addWidget(save);

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveRelation()));
    //QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerCouple()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterCouple()));

    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));

}
void RelationEditeur::saveRelation(){
    relation->setTitre(titre->text());
    relation->setDesc(desc->toPlainText());
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void RelationEditeur::activerSave(QString){
    save->setEnabled(true);
}

void RelationEditeur::ajouterCouple(){

    CoupleEditeur addCouple(*this->relation,this);

    addCouple.exec();

}


CoupleEditeur::CoupleEditeur(Relation& re,QWidget *parent):

    QDialog(parent),relation(&re){

    idx = new QLineEdit ;
    idy = new QLineEdit;
    label = new QLineEdit;

    idx1 = new QLabel ("note1",this);
    idy1 = new QLabel ("note2",this);
    label1 = new QLabel ("label",this);

    notes = new QListWidget;

    save = new QPushButton("sauvegarder",this);

    clabel = new QHBoxLayout;
    clabel->addWidget(label1);
    clabel->addWidget(label);

    cidx = new QHBoxLayout;
    cidx->addWidget(idx1);
    cidx->addWidget(idx);
    cidy = new QHBoxLayout;
    cidy->addWidget(idy1);
    cidy->addWidget(idy);

    couche = new QVBoxLayout;
    couche->addLayout(clabel);
    couche->addLayout(cidx);
    couche->addLayout(cidy);

    couche->addWidget(notes);
    couche->addWidget(save);
    setLayout(couche);
   /* for(unsigned int i=0;i<NotesManager::getNoteManager().getNb();i++)
    notes->addItem(NotesManager::getNoteManager().getNote(i)->getId());*/

    QObject::connect(notes,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherId(QListWidgetItem*)));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveCouple()));


}
void CoupleEditeur::afficherId(QListWidgetItem *item){
    if(idx->text()==nullptr){
        //QString id1=NotesManager::getManager().getNote(item->text())->getId();
        idx->setText("id1");
    }
    else {
        //QString id2=NotesManager::getManager().getNote(item->text())->getId();
        idy->setText("id2");
    }

}
void CoupleEditeur::saveCouple(){
    couple->setLabel(label->text());
    couple->setX(NotesManager::getNoteManager().getNote(idx->text()));
    couple->setY(NotesManager::getNoteManager().getNote(idy->text()));
    relation->getCouples().append(couple);
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void CoupleEditeur::activerSave(QString){
    save->setEnabled(true);
}
