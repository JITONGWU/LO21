#include "articleediteur.h"
#include <QMessageBox>

ArticleEditeur::ArticleEditeur(Article &art, QWidget *parent, bool n):

    QDialog(parent),article(&art)
    //apple au constructeur de qwidget en lui donnant en parametre "parent"
    //initialisation de article avec le parametre art
 {
    //tous les widget crÃ©Ã©s ont comme parent l'objet de type articleediteur
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

     if(n==false){
    id->setReadOnly(true);

    id->setText(article->getId());
    titre->setText(article->getTitle());
    text->setText(article->getT());
    }

    setLayout(couche);

    save->setEnabled(false);
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(activerSave()));

}
void ArticleEditeur::saveArticle(){

    QString ident=id->text();
    qDebug()<<ident;
    if(NotesManager::getManager().copieNote(ident)!= NULL) {
        qDebug()<<"entre condition";
        Note* artTemp= NotesManager::getManager().copieNote(ident); // dÃ©finir un constructeur de recopie s'il n'existe pas dÃ©jÃ 
        artTemp->setTitle(titre->text()); //Tester référence
        artTemp->setDateDerModif(QDate::currentDate());
        static_cast<Article*>(artTemp)->setT(text->toPlainText());

        NotesManager::getManager().nouvelleVersion(artTemp); }

    else {
        //Tester références avant constructeur?
        Article *n_article = new Article(id->text(), titre->text(), QDate::currentDate(), QDate::currentDate(), "N", non_traite,0,text->toPlainText());
        NotesManager::getManager().nouvelleVersion(n_article);}

    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);
    NotesManager::getManager().save();
    NotesManager::getManager().load();


}
void ArticleEditeur::activerSave(QString){
    save->setEnabled(true);
}

