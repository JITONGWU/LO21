#ifndef ARTICLEEDITEUR
#define ARTICLEEDITEUR
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
#include "notes.h"
class ArticleEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots



    QLabel *id1;
    QLabel *titre1;
    QLabel *t1;

    QPushButton *save;
    QPushButton *archieve;
    QPushButton *supprimer;
    QHBoxLayout *buttons;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *ct;
    QVBoxLayout *couche;

     //pointeur vers l'article à afficher par la fenetre

public:
    bool newA;
    Article *article;
    QLineEdit *id;
    QLineEdit *titre;
    QTextEdit *t;
    explicit ArticleEditeur (Article& article,QWidget *parent=0,bool n=true);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
    void SendToPage1(QString);
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveArticle();


};

#endif // ARTICLEEDITEUR


