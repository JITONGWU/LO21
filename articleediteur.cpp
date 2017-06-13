#include "articleediteur.h"
#include <QMessageBox>
#include "relationmanager.h"
#include "relation.h"
#include "demandesupprimer.h"
ArticleEditeur::ArticleEditeur(Article &art, QWidget *parent, bool n, int r, bool a):

    QWidget(parent),article(&art),newA(n), restaurer(r), arc(a)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de article avec le parametre art
 {

//      if(article->getEmp()=="A") ad=true;else ad=false;

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
    supprimertous =new QPushButton("supprimer toutes ses version",this);
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


   save->setEnabled(false);
   supprimertous->setEnabled(false);
   archieve->setEnabled(false);


   desarchieve->setEnabled(true);

    } else{



        //save->setEnabled(true);
       // supprimertous->setEnabled(true);
//        archieve->setEnabled(true);


        desarchieve->setEnabled(false);}


     if(n==false){
    id->setReadOnly(true);
     }

    id->setText(article->getId());
    titre->setText(article->getTitle());
    t->setText(article->getT());






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
    QObject::connect(desarchieve,SIGNAL(clicked()),this,SLOT(desarchiver()));


}
void ArticleEditeur::saveArticle(){
    QString avant=article->getT()+article->getTitle();
    NotesManager::getManager().supprimerCoupleDansReference(id->text(),avant);
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

    DemandeSave();


}









void ArticleEditeur::DemandeSave(){
for(NotesManager::Iterator it=NotesManager::getManager().getIterator();!it.isDone();it.next()){
    if(it.current().getEmp()=="A"){

            if(Reference::getRef()->supprimeroupas(it.current().getId())){
                 qDebug("sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");

                 QMessageBox message(QMessageBox::NoIcon, "Supprimer", "vous pouvez suppriemr le note  "+it.current().getId(), QMessageBox::Yes | QMessageBox::No,  NULL);

                 if(message.exec() == QMessageBox::Yes)
                 {
                         SupprimertousArticle2(it.current().getId());

                 } else{message.close();}


            }

    }

}

}









void ArticleEditeur::activerSave(QString){
    save->setEnabled(true);
}



void ArticleEditeur::ArchiverArticle(){

    NotesManager::getManager().archiverNoteX(article->getId());

    RelationManager::getManager().archiverLesCoupleContenantNoteX (article->getId());

    QMessageBox::information(this,"archiver","bien archiver");
}

    void ArticleEditeur::SupprimertousArticle2(QString id){
        if(Reference::getRef()->supprimeroupas(id)){

       NotesManager::getManager().supprimertousNotes(id);
         RelationManager::getManager().supprimerLesCoupleContenantNoteX(id);
        QMessageBox::information(this,"supprimer","bien supprimer");}
        else{
            NotesManager::getManager().archiverNoteX(id);
             RelationManager::getManager().archiverLesCoupleContenantNoteX (id);

            QMessageBox::information(this,"archiver","bien archiver");
        }

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



void ArticleEditeur::desarchiver(){
    NotesManager::getManager().desarchiver(article->getId());
}
