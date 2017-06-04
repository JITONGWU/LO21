#include "FenPrincipale.h"
#include "articleediteur.h"
#include "imageediteur.h"

#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>
#include <QHBoxLayout>

FenPrincipale::FenPrincipale() {

    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(this), tr("Notes"));
    onglet->addTab(new Page2(this), tr("Relations"));
    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}

Page1::Page1(QWidget *parent)
{


    /*** MENU ***/






    // NOTES
    QMenu *menuNotes = menuBar()->addMenu("&Notes");

    QAction *actionAjout = new QAction("&Ajouter une note", this);
    menuNotes->addAction(actionAjout);

  //  QObject::connect(actionAjout,SIGNAL(triggered()),qApp,SLOT(editerArticle("id:citation_babage")));


    QMenu *fichiersRecents = menuNotes->addMenu("Fichiers &récents");
    fichiersRecents->addAction("Fichier_test.txt");

    // RELATIONS

    QMenu *menuRelations = menuBar()->addMenu("&Relations");



    // EDITION

    QMenu *menuEdition = menuBar()->addMenu("&Edition");

    QAction *actionAnnuler = new QAction("&Annuler", this);
    QAction *actionRetablir = new QAction("&Retablir", this);
    menuEdition->addAction(actionAnnuler);
    menuEdition->addAction(actionRetablir);
    actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
    actionRetablir->setShortcut(QKeySequence("Ctrl+Y"));


    /*** TOOL BAR ***/

    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->setMovable(0);
    toolBarFichier->addAction(actionAjout);
    toolBarFichier->addSeparator();


    /*** DOCKS ?  ***/


    // https://qt.developpez.com/doc/4.7/mainwindow/

  /*   QDockWidget *contentsWindow = new QDockWidget(tr("Visionneuse de notes"), this);
     contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea);

     addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

     QListWidget *headingList = new QListWidget(contentsWindow);
     contentsWindow->setWidget(headingList);
     setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

     */



    /*** ZONE CENTRALE ***/

    QDate d1(1997,3,5);
    QDate d2(1998,2,1);
    Article a("id_article","tiretitre",d1,d2,"N","sksdfdsfsdfaskd");
    Image i("id_image","myimage",d1,d2,"A","this is my image","this is my file");
    //initialiser les notes pour tester

    zoneCentrale = new QWidget;
    vide = new QWidget;
    ae = new ArticleEditeur(a,this);
    ie = new ImageEditeur(i,this);
    scrollNote = new QScrollArea;
    listWidget = new ListeNotes;
    layout=new QHBoxLayout;

    scrollNote->setWidgetResizable(true);

    layout->addWidget(listWidget,1,0);
    layout->addWidget(ae,1,0);
    layout->addWidget(ie,1,0);
    layout->addWidget(vide,1,0);
    layout->addWidget(scrollNote,1,0);
    ie->setVisible(false);
    ae->setVisible(false);
    vide->setVisible(true);

    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);



    QObject::connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherWidget(QListWidgetItem*)));

}
void Page1::afficherWidget(QListWidgetItem* item){

    if(item->text()=="id_article") {
    ie->setVisible(false);
    ae->setVisible(true);
    vide->setVisible(false);
    }
    if(item->text()=="id_image") {
    ae->setVisible(false);
    ie->setVisible(true);
    vide->setVisible(false);
    }

}

Page2::Page2(QWidget * parent) {
    QWidget *zoneCentrale = new QWidget;

    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *age = new QLineEdit;

    QFormLayout *layout = new QFormLayout;
    layout->addRow("fljkdlq", nom);
    layout->addRow("jlkfqjdjmq", prenom);
    layout->addRow("jfmqkdfq", age);

    zoneCentrale->setLayout(layout);

    setCentralWidget(zoneCentrale);



}




ListeNotes::ListeNotes() {


insertItem(0, new QListWidgetItem("id_article"));
insertItem(1, new QListWidgetItem("id_image"));
insertItem(2, new QListWidgetItem("Note 3"));
insertItem(3, new QListWidgetItem("Note 4"));


//Faire une boucle de i=1 au nbNotes
//Utiliser XML pour lire titre et associé note 1 à son titre;

}
