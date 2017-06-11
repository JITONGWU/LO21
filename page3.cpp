#include "window.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>
#include <QDate>
Page3::Page3(QWidget *parent):QMainWindow(parent)
{
    zoneCentrale = new QWidget;


    restaurer = new QPushButton("restaurer une note",this);
    supprimer = new QPushButton("supprimer une note",this);
    QObject::connect(restaurer,SIGNAL(clicked()),this,SLOT(Restaurer()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(Supprimer()));

    corbeille = new QListWidget;
    //NotesManager &nm = NotesManager::getManager();
   // for(unsigned int i=0;i<nm.)
    //    corbeille->addItem(it.current().getTitre());
    buttons = new QHBoxLayout;
    buttons->addWidget(restaurer);
    buttons->addWidget(supprimer);

    couche = new QVBoxLayout;

    couche->addWidget(corbeille);
    couche->addLayout(buttons);

    zoneCentrale->setLayout(couche);
    setCentralWidget(zoneCentrale);
    //QObject::connect(Page1::av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString));
    //QObject::connect(Page1::av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString));
    //QObject::connect(Page1::av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString));
    //QObject::connect(Page1::av,SIGNAL(SendToPage1(QString)),this,SLOT(receive(QString));
    Page1::a

}
void Page3::Restaurer(){}
void Page3::Supprimer(){}
/*void Page3::receive(QString id){
    //corbeille->takeItem(id);
}
*/
