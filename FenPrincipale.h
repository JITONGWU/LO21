#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include "Notes.h"
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

class Page1 : public QMainWindow {

    public:
    Page1();

    private:


};



class Page2 : public QMainWindow {

    public:
    Page2();

    private:

};

class ListeNotes : public QListWidget {

    public:
    ListeNotes();

    private:

};


#endif
