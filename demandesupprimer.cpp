#include "demandesupprimer.h"

#include <QMessageBox>


DialogSup::DialogSup(QWidget *parent , QString i, ArticleEditeur * p):QWidget(parent),id(i),par(p){
    label->setText("vous pouvez supprimer le note "+id+"car la dernier reference vers ce note a ete supprimer , vous voulez le supprimer?");
   oui=new QPushButton("oui",this);

   non =new QPushButton("non",this);
   V=new QVBoxLayout;
   H=new QHBoxLayout;
   H->addWidget(oui);
   H->addWidget(non);
   V->addWidget(label);
   V->addLayout(H);
   setLayout(V);

   QObject::connect(oui,SIGNAL(clicked()),this,SLOT(SupprimerArticle()));
   QObject::connect(non,SIGNAL(clicked()),this,SLOT(close()));

}


void DialogSup::SupprimerArticle(){
    par->SupprimertousArticle();
}


