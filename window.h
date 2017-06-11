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
class Page3 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;

    QPushButton *restaurer;
    QPushButton *supprimer;
    QListWidget *corbeille;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:

    Page3(QWidget *parent);
public slots:
    void Restaurer();
    void Supprimer();

};
class Page1 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;

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


    ArticleEditeur *av;

    ImageEditeur *iv;
    QListWidget *listWidget;
    QListWidget *NotesArchieve;
    QListWidget *Taches;
    QVBoxLayout *List;
    QHBoxLayout *layout;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:

    Page1(QWidget *parent);
public slots:
    void afficherWidget(QListWidgetItem* item);
    void ArticleEditeurVide();
    void ImageEditeurVide();
    void afficherArbo(QListWidgetItem*);



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
};



#endif
