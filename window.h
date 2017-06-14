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
#include "audioediteur.h"
#include "videoediteur.h"
#include "tacheediteur.h"
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
     public slots:
     void afficherOldNotes(QListWidgetItem *item);
 };


#endif
