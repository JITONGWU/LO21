#include "articleediteur.h"
#include "Notes.h"
#include <QMessageBox>

ArticleEditeur::ArticleEditeur(Article &art, QWidget *parent):

    QWidget(parent),article(&art)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de article avec le parametre art
{
    //tous les widget créés ont comme parent l'objet de type articleediteur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    text=new QTextEdit(this);
    save=new QPushButton("sauvegarder",this);

    id1=new QLabel("identificateur",this);
    titre1=new QLabel("Titre",this);
    text1=new QLabel("Texte",this);

    cid=new QHBoxLayout;
    cid->addWidget(id1);
    cid->addWidget(id);


    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    ctext=new QHBoxLayout ;
    ctext->addWidget(text1);
    ctext->addWidget(text);

    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(ctext);
    couche->addWidget(save);

    id->setReadOnly(true);

    id->setText(article->getText());
    titre->setText(article->getTitle());
    text->setText(article->getText());

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(activerSave()));

}
void ArticleEditeur::saveArticle(){
    article->setTitle(titre->text());
    article->setText(text->toPlainText());
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);

}
void ArticleEditeur::activerSave(QString){
    save->setEnabled(true);
}
