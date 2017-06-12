#include "articleediteur.h"
#include <QMessageBox>
#include "relationmanager.h"
#include "relation.h"

ArticleEditeur::ArticleEditeur(Article &art, QWidget *parent, bool n, int r, bool a):

    QWidget(parent),article(&art),newA(n), restaurer(r), arc(a)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de article avec le parametre art
 {


    //tous les widget créés ont comme parent l'objet de type articleediteur

    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    t=new QTextEdit(this);

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

    save=new QPushButton("sauvegarder",this);
    archieve=new QPushButton("archiever",this);
    desarchieve=new QPushButton("desarchiever",this);
    rest=new QPushButton("restaurer",this);
    supprimertous =new QPushButton("supprimer",this);
    buttons = new QHBoxLayout;
    buttons->addWidget(archieve);
    buttons->addWidget(save);
    buttons->addWidget(desarchieve);

    buttons->addWidget(rest);
    buttons->addWidget(supprimertous);
    couche=new QVBoxLayout;
    couche->addLayout(cid);
    couche->addLayout(ctitre);
    couche->addLayout(ct);
    couche->addLayout(buttons);

    if(arc==true){

   titre->setReadOnly(true);
   t->setReadOnly(true);


   save->setVisible(false);
   supprimertous->setVisible(false);
   archieve->setVisible(false);


   desarchieve->setEnabled(true);

    } else{



        save->setEnabled(true);
        supprimertous->setEnabled(true);
        archieve->setEnabled(true);
        desarchieve->setVisible(false);}


     if(n==false){
    id->setReadOnly(true);

    id->setText(article->getId());
    titre->setText(article->getTitle());
    t->setText(article->getT());

}





   /*

    } */


     if(restaurer<0) { rest->setVisible(false);}
      else {save->setVisible(false); supprimertous->setVisible(false); archieve->setVisible(false);}

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(rest,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(t,SIGNAL(textChanged()),this,SLOT(activerSave()));

    QObject::connect(archieve,SIGNAL(clicked()),this,SLOT(ArchiverArticle()));
    QObject::connect(supprimertous,SIGNAL(clicked()),this,SLOT(SupprimertousArticle()));


}
void ArticleEditeur::saveArticle(){
    QString avant=titre->text()+t->toPlainText();
    NotesManager::getManager().supprimerCoupleDansReference(id->text(),avant);

  /* QString ident=id->text();
    qDebug()<<ident;
  if(NotesManager::getManager().copieNote(ident)!= NULL) {
        qDebug()<<"entre condition";
            Note* artTemp= NotesManager::getManager().copieNote(ident); // dÃ©finir un constructeur de recopie s'il n'existe pas dÃ©jÃ
            artTemp->setTitle(titre->text());
            NotesManager::addCoupleDansReference(ident,titre->text()+t->toPlainText());
            //Tester référence
            artTemp->setDateDerModif(QDateTime::currentDateTime());
            static_cast<Article*>(artTemp)->setT(t->toPlainText());
            NotesManager::getManager().nouvelleVersion(artTemp); }
        else {
            //Tester références avant constructeur?
            Article *n_article = new Article(id->text(), titre->text(), QDateTime::currentDateTime(), QDateTime::currentDateTime(), "N", non_traite,0,t->toPlainText());
            NotesManager::getManager().nouvelleVersion(n_article);}
*/





    if(restaurer >=0) {
          qDebug()<<"restaurer??";
            NotesManager::getManager().restaurerVersionNote(article,restaurer);
            QMessageBox::information(this,"restauration","bien restaurer");
            setVisible(false);
    }
        else {
        if(newA==false) {
                Note* artTemp= NotesManager::getManager().copieNote(id->text()); // dÃ©finir un constructeur de recopie s'il n'existe pas dÃ©jÃ
                artTemp->setTitle(titre->text());
              //  NotesManager::addCoupleDansReference(id->text(),titre->text()+t->toPlainText());
                //Tester référence
                artTemp->setDateDerModif(QDateTime::currentDateTime());
                static_cast<Article*>(artTemp)->setT(t->toPlainText());

                NotesManager::getManager().nouvelleVersion(artTemp);
           }
    else {
        article->setId(id->text());
        article->setTitle(titre->text());
        article->setT(t->toPlainText());
        NotesManager::getManager().addNote(article);
        emit SendToPage1(id->text());
        article= new Article("this is id","this is title",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"this is text");
    }
    QString apres= titre->text()+t->toPlainText();
    NotesManager::getManager().addCoupleDansReference(id->text(),apres);
         QMessageBox::information(this,"sauvegarder","bien sauvegarder");
         save->setEnabled(false);}
}
void ArticleEditeur::activerSave(QString){
    save->setEnabled(true);
}



void ArticleEditeur::ArchiverArticle(){

    NotesManager::getManager().archiverNoteX(article->getId());

    RelationManager::getManager().archiverLesCoupleContenantNoteX (article->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

void ArticleEditeur::SupprimertousArticle(){
    if(Reference::getRef()->supprimeroupas(article->getId())){

   NotesManager::getManager().supprimertousNotes(article->getId());
     RelationManager::getManager().supprimerLesCoupleContenantNoteX(article->getId());
    QMessageBox::information(this,"supprimer","bien supprimer");}
    else{
        NotesManager::getManager().archiverNoteX(article->getId());
         RelationManager::getManager().archiverLesCoupleContenantNoteX (article->getId());

        QMessageBox::information(this,"archiver","bien archiver");
    }


}
