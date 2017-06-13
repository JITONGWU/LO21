#include "window.h"

Page2::Page2(QWidget *parent):QMainWindow(parent)
{
    zoneCentrale = new QWidget;


    AjoutRelation = new QPushButton("ajouter une relation",this);
    QObject::connect(AjoutRelation,SIGNAL(clicked()),this,SLOT(RelationEditeurVide()));

    supprimerR = new QPushButton("supprimer une relation",this);
    QObject::connect(supprimerR,SIGNAL(clicked()),this,SLOT(supprimerRelation()));

    update = new QPushButton("update",this);
    QObject::connect(update,SIGNAL(clicked()),this,SLOT(Update()));


    listR = new ListeRelation;
    vide = new QWidget;

    Relation* rvide = new Relation("","");
    re = new RelationEditeur(*rvide,this,false);//visualiser une relation existante
    rv = new RelationEditeur(*rvide,this); // add new relation

    buttons = new QHBoxLayout;
    buttons->addWidget(AjoutRelation);
    buttons->addWidget(supprimerR);
    buttons->addWidget(update);
    layout =new QHBoxLayout;
    couche = new QVBoxLayout;
    layout->addWidget(listR,1,0);
    layout->addWidget(re,1,0);
    layout->addWidget(rv,1,0);
    layout->addWidget(vide,1,0);
    re->setVisible(false);
    rv->setVisible(false);
    vide->setVisible(true);
    couche->addLayout(buttons);
    couche->addLayout(layout);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(listR,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));
    QObject::connect(rv,SIGNAL(SendToPage2(QString)),this,SLOT(receive(QString)));
}
void Page2::receive(QString titre){
    listR->addItem(titre);
}
void Page2::Update(){
    listR->clear();
    for(RelationManager::Iterator it = RelationManager::getManager().getIterator();!it.isDone();it.next())
        listR->addItem(it.current().getTitre());
}

void Page2::afficherWidget(QListWidgetItem* item){
    re->orient->setEnabled(false);
    re->titre->setReadOnly(true);
    supprimerR->setEnabled(true);
    re->desc->setReadOnly(false);
    re->ajouter->setEnabled(true);

    Relation *choisir=RelationManager::getManager().getRelation(item->text());
    re->relation=choisir;
    re->titre->setText(item->text());
    re->desc->setText(choisir->getDesc());
    //la relation reference ne peut pas être modifiée ni ajouter couples
    if(choisir->getTitre()=="reference") {
        supprimerR->setEnabled(false);
        re->desc->setReadOnly(true);
        re->ajouter->setEnabled(false);
    }

    if(choisir->getOrient())  re->orient->setChecked(true);

    re->couples->clear();
    for(unsigned int i=0;i<choisir->getNbCouples();i++){
        if(choisir->getCoupleParIndice(i)->getEtat()!="C")
      re->couples->addItem(choisir->getCoupleParIndice(i)->getLabel());

    }

    rv->setVisible(false);
    vide->setVisible(false);
    re->setVisible(true);


}
void Page2::RelationEditeurVide(){
    rv->titre->clear();
    rv->desc->clear();
    rv->couples->clear();
    rv->orient->setChecked(false);
    vide->setVisible(false);
    re->setVisible(false);
    rv->setVisible(true);
}
void Page2::supprimerRelation(){
    RelationManager &rm = RelationManager::getManager();
    rm.supprimerRelation(listR->currentRow());
    listR->takeItem(listR->currentRow());
    QMessageBox::information(this,"supprimer","bien supprimer une relation");
}
ListeRelation::ListeRelation(){
    for(RelationManager::Iterator it = RelationManager::getManager().getIterator();!it.isDone();it.next())
        addItem(it.current().getTitre());
}
