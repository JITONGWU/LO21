#ifndef RELATIONEDITEUR
#define RELATIONEDITEUR

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <QListWidget>
#include <QDialog>
#include "relation.h"
#include "relationmanager.h"
#include "window.h"
class CoupleEditeur;
class RelationEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots



    QLabel *titre1;
    QLabel *desc1;
    QLabel *couples1;

    QPushButton *save;
    QPushButton *ajouter;
    QPushButton *supprimer;

    QHBoxLayout *ctitre;
    QHBoxLayout *cdesc;
    QHBoxLayout *ccouples;
    QHBoxLayout *button;
    QVBoxLayout *couche;



public:

    QLineEdit *titre;
    QTextEdit *desc;
    QListWidget *couples;
    Relation *relation;

    explicit RelationEditeur (Relation& re,QWidget *parent=0);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveRelation();
    void ajouterCouple();


};


class CoupleEditeur:public QDialog{
    Q_OBJECT

    QLineEdit *idx;
    QLineEdit *idy;
    QLineEdit *label;


    QLabel *idx1;
    QLabel *idy1;
    QLabel *label1;

    QPushButton *save;



    QHBoxLayout *cidx;
    QHBoxLayout *cidy;
    QHBoxLayout *clabel;
    QVBoxLayout *couche;
    ListeNotes *notes;
    Couple *couple;
    Relation *relation;
public:
    CoupleEditeur(Relation &re,QWidget *parent=0);
public slots:
    void afficherId(QListWidgetItem* item);
    void saveCouple();
    void activerSave(QString);

};


#endif // RELATIONEDITEUR

