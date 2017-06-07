#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include "notes.h"
#include"articleediteur.h"
#include"imageediteur.h"
#include "relationediteur.h"
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

class FenPrincipale : public QMainWindow {
  public:
    FenPrincipale();

};
class ListeNotes : public QListWidget {

    public:
    ListeNotes();

    private:

};
class ListeRelations : public QListWidget {

    public:
    ListeRelations();

    private:

};

class Page1 : public QMainWindow {
    Q_OBJECT

    QPushButton *AjoutArticle;
    QPushButton *AjoutTache;
    QPushButton *AjoutImage;
    QPushButton *AjoutAudio;
    QPushButton *AjoutVideo;

    QWidget *zoneCentrale;
    QWidget *vide;

    ArticleEditeur *ae;
    ArticleEditeur *av;

    ImageEditeur *ie;
    ImageEditeur *iv;

    QScrollArea *scrollNote;
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


};



class Page2 : public QMainWindow {

    Q_OBJECT

    QWidget *zoneCentrale;

    QPushButton *AjoutRelation;
    QWidget *vide;
    RelationEditeur *re;
    RelationEditeur *rv;
    QScrollArea *scrollRelation;
    ListeRelations *listWidget;
    QHBoxLayout *layout;
    QVBoxLayout *couche;

public:
    Page2(QWidget *parent);

public slots:
    void afficherWidget(QListWidgetItem* item);
    void RelationEditeurVide();

};



#endif
