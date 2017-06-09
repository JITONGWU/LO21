#include "articleediteur.h"
#include <QMessageBox>

ArticleEditeur::ArticleEditeur(Article &art, QWidget *parent, bool n):

    QWidget(parent),article(&art)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de article avec le parametre art
 {
    //tous les widget créés ont comme parent l'objet de type articleediteur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    t=new QTextEdit(this);
    save=new QPushButton("sauvegarder",this);

    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    t1=new QLabel("Texte",this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);


    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    ct=new QHBoxLayout ;
    ct->addWidget(t1);
    ct->addWidget(t);

    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(ct);
    couche->addWidget(save);

     if(n==false){
    id->setReadOnly(true);

    id->setText(article->getId());
    titre->setText(article->getTitle());
    t->setText(article->getT());
    }

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(t,SIGNAL(textChanged()),this,SLOT(activerSave()));

}
void ArticleEditeur::saveArticle(){
   article->setTitle(titre->text());
   article->setT(t->toPlainText());
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void ArticleEditeur::activerSave(QString){
    save->setEnabled(true);
}

