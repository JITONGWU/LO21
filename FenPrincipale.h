#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include "notes.h"
#include"articleediteur.h"
#include"imageediteur.h"
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

class Page1 : public QMainWindow {
    Q_OBJECT


    QWidget *zoneCentrale;
    QWidget *vide;
    ArticleEditeur *ae;
    ImageEditeur *ie;
    QScrollArea *scrollNote;
    ListeNotes *listWidget;
    QHBoxLayout *layout;
public:
    Page1(QWidget *parent);
public slots:
    void afficherWidget(QListWidgetItem* item);

};



class Page2 : public QMainWindow {

    public:
    Page2(QWidget *parent);

    private:

};



#endif
