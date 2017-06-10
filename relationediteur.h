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

class CoupleEditeur;

class RelationEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots



    QLabel *titre1;
    QLabel *desc1;
    QLabel *couples1;
    QLabel *orient1;

    QPushButton *save;
    QPushButton *supprimerC;//pour supprimer une couple
    QHBoxLayout *ctitre;
    QHBoxLayout *cdesc;
    QHBoxLayout *corient;
    QHBoxLayout *ccouples;
    QHBoxLayout *button;
    QVBoxLayout *couche;



public:
    QPushButton *ajouter;//ajouter couple dans une relation
    QLineEdit *titre;
    QTextEdit *desc;
    QListWidget *couples;
    QRadioButton *orient;
    QPushButton *supprimerR;//pour supprimer une relation

    Relation *relation;
    bool newRelation;
    explicit RelationEditeur (Relation& re, QWidget *parent=0, bool newR=true);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveRelation();
    void ajouterCouple();
    void IsOriente();
 // void supprimerCouple();
    void supprimerRelation();


};


class CoupleEditeur:public QDialog{
    Q_OBJECT

    QLineEdit *idx;
    QLineEdit *idy;
    QLineEdit *label;
    QListWidget *notes;


    QLabel *idx1;
    QLabel *idy1;
    QLabel *label1;
    QLabel *notes1;

    QPushButton *save;



    QHBoxLayout *cidx;
    QHBoxLayout *cidy;
    QHBoxLayout *clabel;
    QHBoxLayout *cnotes;
    QVBoxLayout *couche;

    Couple *couple;
    Relation *relation;
    RelationEditeur *relationediteur;
public:
    CoupleEditeur(Relation &relation, QWidget *parent, RelationEditeur& re);
public slots:
    void afficherId(QListWidgetItem* item);
    void saveCouple();



};


#endif // RELATIONEDITEUR

