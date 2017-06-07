#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include  <QDate>
FenPrincipale::FenPrincipale() {

    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(this), tr("Notes"));
    onglet->addTab(new Page2(this), tr("Relations"));
    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}


Page2::Page2(QWidget *parent){
    zoneCentrale = new QWidget;


    AjoutRelation = new QPushButton("ajouter une relation",this);
    QObject::connect(AjoutRelation,SIGNAL(clicked()),this,SLOT(RelationEditeurVide()));



    listWidget = new ListeRelations;
    vide = new QWidget;

    Relation rvide("","");
    re = new RelationEditeur(rvide,this);
    rv = new RelationEditeur(rvide,this);
    scrollRelation = new QScrollArea;

    layout =new QHBoxLayout;
    couche = new QVBoxLayout;
    layout->addWidget(listWidget,1,0);
    layout->addWidget(re,1,0);
    layout->addWidget(rv,1,0);
    layout->addWidget(vide,1,0);
    re->setVisible(false);
    rv->setVisible(false);
    vide->setVisible(true);
    couche->addWidget(AjoutRelation);
    couche->addLayout(layout);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);



    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));




}


void Page2::afficherWidget(QListWidgetItem* item){

    re->titre->setText(item->text());
  /*  rv->desc->setText(rm.getRelation(item->text()).getDesc());
    for(unsigned int i=0;i<rm.getRelation(item->text()).getNb();i++)
    couples->addItem(rm.getRelation(item->text()).getCouple(i)->getLabel());*/
  //  couples->addItem("Couple1");

    rv->setVisible(false);

    re->setVisible(true);
    vide->setVisible(false);


}
void Page2::RelationEditeurVide(){

    re->setVisible(false);
    vide->setVisible(false);
    rv->setVisible(true);
}


ListeNotes::ListeNotes() {


insertItem(0, new QListWidgetItem("id_article"));
insertItem(1, new QListWidgetItem("id_image"));
insertItem(2, new QListWidgetItem("Note 3"));
insertItem(3, new QListWidgetItem("Note 4"));


//Faire une boucle de i=1 au nbNotes
//Utiliser XML pour lire titre et associé note 1 à son titre;

}

ListeRelations::ListeRelations() {


insertItem(0, new QListWidgetItem("Relation1"));
insertItem(1, new QListWidgetItem("Relation2"));
insertItem(2, new QListWidgetItem("Relation3"));
insertItem(3, new QListWidgetItem("Relation4"));


}

