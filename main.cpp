#include <QApplication>
#include <iostream>
#include "notes.h"
#include "relation.h"
#include "relationmanager.h"
#include "window.h"
using namespace std ;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"current applicationDirPath: "<<QCoreApplication::applicationDirPath();
    qDebug()<<"current currentPath: "<<QDir::currentPath();
    // QFile("notes.xml");
    //QFile("relation.xml");

    try{
    NotesManager &nm = NotesManager::getManager();
    RelationManager &rm = RelationManager::getManager();
    //QString fichier = QFileDialog::getOpenFileName();
    //QString fichier2 = QFileDialog::getOpenFileName();
    //nm.setFilename(fichier);
    //rm.setFilename(fichier2);
    QDir fn1("notes.xml");
    QDir fn2("relation.xml");
    QString filename1 = fn1.absolutePath();
    QString filename2 = fn2.absolutePath();



    nm.setFilename(filename1);
    rm.setFilename(filename2);
     nm.load();
     rm.load();

/*

    QDateTime d1=QDateTime::currentDateTime();
    QDateTime d2=QDateTime::currentDateTime();
    nm.addArticle("0001","titre1",d1,d2,"N",actuelle,0,"this is text ref{0002}");
    nm.addArticle("0002","titre2",d1,d2,"N",actuelle,0,"this is text");
    nm.addArticle("0003","titre3",d1,d2,"N",actuelle,0,"this is text");
    nm.addArticle("id4","titre4",d1,d2,"N",actuelle,0,"this is text");
    nm.addArticle("id5","titre5",d1,d2,"N",actuelle,0,"this is text");
    nm.addArticle("id6","titre6",d1,d2,"N",actuelle,0,"this is text");
    Couple *cp1=   new Couple("lo21",nm.getNote(0),nm.getNote(1));
    Couple *cp2 = new Couple("nf17",nm.getNote(2),nm.getNote(0));
    Couple *cp3 = new Couple("label3",nm.getNote(0),nm.getNote(5));
    Couple *cp4 = new Couple("label4",nm.getNote(1),nm.getNote(4));
    Relation *r1=new Relation("my relation","desc1");
    Relation *r2=new Relation("my relation2","desc2");
    r1->addCouple(cp1);
    r1->addCouple(cp2);
    r2->addCouple(cp3);
    r2->addCouple(cp4);
    rm.addRelation(r1);
    rm.addRelation(r2);
    Reference::getRef()->addCouple(cp1);

*/
    }
    catch(NotesException& e){
            std::cout<<e.getInfo().toStdString()<<"\n";
        }



    FenPrincipale w;
     w.show();

    return a.exec();
}
