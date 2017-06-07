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
#include <QComboBox>
class TacheEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots

    QLineEdit *id;
    QLineEdit *titre;

    QTextEdit *action;
    QDateEdit *echeance;

    QComboBox *priorite;

    QLabel *id1;
    QLabel *titre1;
    QLabel *action1;
    QLabel *echeance1;
    QLabel *priorite1;

    QPushButton *save;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *caction;
    QHBoxLayout *cecheance;
    QHBoxLayout *cpriorite;

    QVBoxLayout *couche;

    Tache *tache; //pointeur vers l'article à afficher par la fenetre

public:
    explicit TacheEditeur (Image& ta,QWidget *parent=0);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveTache();


};


#endif // TACHEEDITEUR

