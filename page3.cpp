#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include <QDateTime>
Page3::Page3(QWidget *parent):QMainWindow(parent)
{
    zoneCentrale = new QWidget;
    corbeille = new QListWidget;

    restaurer = new QPushButton("restaurer une note",this);
    supprimer = new QPushButton("supprimer une note",this);
    update = new QPushButton ("update la corbeille",this);
    restaurer->setEnabled(false);
    supprimer->setEnabled(false);


    NotesManager &nm = NotesManager::getManager();
    for(NotesManager::IteratorCorb it=nm.getIteratorCorb();!it.isDone();it.next())
        if(it.current().getEtat()==actuelle){ qDebug()<<it.current().getEtat();
    corbeille->addItem(it.current().getId());}
    buttons = new QHBoxLayout;
    buttons->addWidget(restaurer);
    buttons->addWidget(supprimer);
    buttons->addWidget(update);


    couche = new QVBoxLayout;

    couche->addWidget(corbeille);
    couche->addLayout(buttons);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    QObject::connect(restaurer,SIGNAL(clicked()),this,SLOT(Restaurer()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(Supprimer()));
    QObject::connect(update,SIGNAL(clicked()),this,SLOT(Update()));

    QObject::connect(corbeille,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Activer(QListWidgetItem*)));


}
void Page3::Activer(QListWidgetItem *itm)
{  restaurer->setEnabled(true);
   supprimer->setEnabled(true);
   choix=itm->text();
}


void Page3::Restaurer(){

    NotesManager::getManager().restaurerDeCorbeille(corbeille->currentItem()->text());

    RelationManager::getManager().restaurerLesCoupleContenantNoteX(corbeille->currentItem()->text());
     qDebug()<<"hahahhaha\n";
                         corbeille->takeItem(corbeille->currentRow());
                        restaurer->setEnabled(false);
                        supprimer->setEnabled(false);}


void Page3::Supprimer(){NotesManager::getManager().supprimerDefinitivement(choix);
                        corbeille->takeItem(corbeille->currentRow());
                        restaurer->setEnabled(false);
                        supprimer->setEnabled(false);}



void Page3::Update(){
    corbeille->clear();
    NotesManager &nm = NotesManager::getManager();
    for(NotesManager::IteratorCorb it=nm.getIteratorCorb();!it.isDone();it.next())
        if(it.current().getEtat()==actuelle){
    corbeille->addItem(it.current().getId());}

}
