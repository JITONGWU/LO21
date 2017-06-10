#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <QFormLayout>
#include <QGridLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <QMainWindow>
#include <QTabWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QMdiArea>
#include <QScrollArea>


#include "relationmanager.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"

class FenPrincipale : public QMainWindow {
  public:
    FenPrincipale(QWidget *parent=0);

};
class ListeNotes : public QListWidget {

    public:

    ListeNotes();

    private:

};

class ListeOldNotes : public QListWidget {
    Q_OBJECT;
    public:
    ListeOldNotes();
    friend class Page1;
    private:

  //  ArticleEditeur *ae;
   // ImageEditeur *ie;
    public slots:
    void afficherOldNotes(QListWidgetItem *item);
   // void restaurerVersion(int j);


};


class ListeRelations : public QListWidget {

    public:


 //   ListeRelations();

    private:

};

class Page1 : public QMainWindow {
    Q_OBJECT
    friend class NotesManager;
    friend class RelationManager;
    QWidget *zoneCentrale;

    QPushButton *AjoutArticle;
    QPushButton *AjoutTache;
    QPushButton *AjoutImage;
    QPushButton *AjoutAudio;
    QPushButton *AjoutVideo;

    QWidget *vide;

    ImageEditeur *ajoutImage;

    ArticleEditeur *ae;
    ArticleEditeur *av;

    ImageEditeur *ie;
    ImageEditeur *iv;

    QScrollArea *scrollNote;
    ListeOldNotes *listWidget2;
    ListeNotes *listWidget;
    QHBoxLayout *layout;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:

    Page1(QWidget *parent);

public slots:
    void afficherWidget(QListWidgetItem* item);
    void ArticleEditeurVide();
    void ImageEditeurVide();
    void ajouterArticle();
    void ajouterImage();
   // void afficherOldNotes(QListWidgetItem *item);



};



class Page2 : public QMainWindow
{
    friend class NotesManager;
    friend class RelationManager;

    Q_OBJECT

    QWidget *zoneCentrale;

     QPushButton *AjoutRelation;
    QWidget *vide;
 /*   RelationEditeur *re;
    RelationEditeur *rv;
    QScrollArea *scrollRelation;
    ListeRelations *listR; */
    QHBoxLayout *layout;
    QVBoxLayout *couche;


public:

    Page2(QWidget *parent);

public slots:
   // void afficherWidget(QListWidgetItem* item);
   // void RelationEditeurVide();

};



#endif
