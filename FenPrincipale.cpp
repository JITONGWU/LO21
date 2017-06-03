#include "FenPrincipale.h"

#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QAction>

FenPrincipale::FenPrincipale() {

    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(), tr("Notes"));
    onglet->addTab(new Page2(), tr("Relations"));
    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}

Page1::Page1()
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




    QWidget *zoneCentrale = new QWidget;

    QLineEdit *id = new QLineEdit;
    QLineEdit *title = new QLineEdit;
    QLineEdit *text = new QLineEdit;

    QGridLayout *layoutG = new QGridLayout;
    QFormLayout *form = new QFormLayout;
    form->addRow("id", id);
    form->addRow("titre", title);
    form->addRow("texte", text);

    //QScrollArea *scrollNote = new QScrollArea;
    //

    ListeNotes *listWidget = new ListeNotes;


    layoutG->addWidget(listWidget,1,0);
    QScrollArea *scrollRelation = new QScrollArea;
    scrollRelation->setWidgetResizable(true);
    layoutG->addWidget(scrollRelation,1,2);


    layoutG->addLayout(form, 1,1),
    zoneCentrale->setLayout(layoutG);
    setCentralWidget(zoneCentrale);




}


Page2::Page2() {
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


insertItem(0, new QListWidgetItem("Note 1"));
insertItem(1, new QListWidgetItem("Note 2"));
insertItem(2, new QListWidgetItem("Note 3"));
insertItem(3, new QListWidgetItem("Note 4"));

//Faire une boucle de i=1 au nbNotes
//Utiliser XML pour lire titre et associé note 1 à son titre;

}
