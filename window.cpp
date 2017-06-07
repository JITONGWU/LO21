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
FenPrincipale::FenPrincipale(NotesManager &n, RelationManager &r) {

    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(n,r,this), tr("Notes"));
    onglet->addTab(new Page2(n,r,this), tr("Relations"));
    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}


Page2::Page2(NotesManager &n, RelationManager &r, QWidget *parent):
    nm(n),rm(r),QWidget(parent){
    zoneCentrale = new QWidget;


    AjoutRelation = new QPushButton("ajouter une relation",this);
    QObject::connect(AjoutRelation,SIGNAL(clicked()),this,SLOT(RelationEditeurVide()));



    listR = new ListeRelations(rm);
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
    re->desc->setText(rm.getRelation(item->text())->getDesc());

    for(unsigned int i=0;i<rm.getRelations().size();i++)
    listR->addItem(rm.getRelations().at(i));

    rv->setVisible(false);
    vide->setVisible(false);
    re->setVisible(true);


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

ListeRelations::ListeRelations(RelationManager &rm) {

for(unsigned int i=0;i<rm.getRelations().size();i++)
    insertItem(i,new QListWidgetItem(rm.getRelations().at(i)));

}

