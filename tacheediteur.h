#ifndef TACHEEDITEUR
#define TACHEEDITEUR


#include <QApplication>
#include <QWidget>
#include <QDateTimeEdit>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QObject>
#include "notes.h"
#include "notemanager.h"
#include <QComboBox>
class TacheEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots


    QLabel *id1;
    QLabel *titre1;
    QLabel *action1;
    QLabel *echeance1;
//    QLabel *priorite1;

    QPushButton *save;
    QPushButton *archieve;
    QPushButton *supprimer;
    QPushButton *rest;

    QHBoxLayout *buttons;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *caction;
    QHBoxLayout *cecheance;
  //  QHBoxLayout *cpriorite;

    QVBoxLayout *couche;

    int restaurer;
public:
    Tache *tache; //pointeur vers l'article �  afficher par la fenetre
    bool newT;
    QLineEdit *id;
    QLineEdit *titre;
    void setRest(int i) {restaurer = i;}
    QTextEdit *action;
    QDateTimeEdit *echeance;

    //QComboBox *priorite;
    explicit TacheEditeur (Tache& ta,QWidget *parent=0, bool n=false, int r=(-1));
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
            void SendToPage1(QString);
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveTache();


};


#endif // TACHEEDITEUR

