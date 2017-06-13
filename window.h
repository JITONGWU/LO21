#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE
#include "audioediteur.h"
#include "videoediteur.h"
#include "tacheediteur.h"
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
#include <QMessageBox>
#include "relationmanager.h"
#include "articleediteur.h"
#include "imageediteur.h"
#include "relationediteur.h"
class FenPrincipale : public QMainWindow {
  public:
    FenPrincipale();

};
class ListeNotes : public QListWidget {

    public:

    ListeNotes();

    private:

};
class ListeRelation : public QListWidget {

    public:

    ListeRelation();

    private:

};
class ListeOldNotes : public QListWidget {

     Q_OBJECT
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
class Page3 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;
    QString choix;
    QPushButton *restaurer;
    QPushButton *supprimer;
    QPushButton *update;
    QListWidget *corbeille;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:

    Page3(QWidget *parent);
public slots:
    void Activer(QListWidgetItem*);
    void Restaurer();
    void Supprimer();
    void Update();
 private slots:
};
class Page1 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;
 QPushButton *update;
    QPushButton *AjoutArticle;
    QPushButton *AjoutTache;
    QPushButton *AjoutImage;
    QPushButton *AjoutAudio;
    QPushButton *AjoutVideo;

    QLabel * ascend;
    QLabel *descend;
    QVBoxLayout *arbo;
    QListWidget *listAscend;
    QListWidget *listDescend;

    QWidget *vide;



    QListWidget *listWidget;
    ListeOldNotes *listWidget2;
    QListWidget *NotesArchieve;
    QListWidget *Taches;
    QVBoxLayout *List;
    QHBoxLayout *layout;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:
    ArticleEditeur *av;
       ImageEditeur *iv;
       TacheEditeur *tv;
       AudioEditeur *adv;
       VideoEditeur *vv;

       ArticleEditeur *ae;
       ImageEditeur *ie;
       TacheEditeur *te;
       AudioEditeur *ade;
       VideoEditeur *ve;

       ArticleEditeur *ar;
       ImageEditeur *ir;
       TacheEditeur *tar;
       AudioEditeur *adr;
       VideoEditeur *vr;

       ArticleEditeur *aa;
       ImageEditeur *ia;
       TacheEditeur *ta;
       AudioEditeur *ada;
       VideoEditeur *va;


    Page1(QWidget *parent);
public slots:
    void afficherWidget(QListWidgetItem* item);
    void ArticleEditeurVide();
    void ImageEditeurVide();
    void afficherArbo(QListWidgetItem*);
    void TacheEditeurVide();
    void AudioEditeurVide();
    void VideoEditeurVide();
    void restaurerVersion(QListWidgetItem* item);
    void afficherNotesArch(QListWidgetItem*);


    void Update();
private slots:
    void receive(QString id);


};

class RelationEditeur;
class Page2 : public QMainWindow
{
    friend class NotesManager;
    friend class RelationManager;

    Q_OBJECT

    QWidget *zoneCentrale;
    QPushButton *AjoutRelation;
    QPushButton *supprimerR;//pour supprimer une relation
    QPushButton *update;
    QWidget *vide;
    RelationEditeur *re;
    RelationEditeur *rv;
    QScrollArea *scrollRelation;
    QHBoxLayout *buttons;
    QHBoxLayout *layout;
    QVBoxLayout *couche;

public:
    ListeRelation *listR;
    Page2(QWidget *parent);
private slots:
    void receive(QString titre);//recevoir le signal de relation editeur
public slots:
    void afficherWidget(QListWidgetItem* item);
    void RelationEditeurVide();
    void supprimerRelation();
    void Update();
};



#endif
