#ifndef ARTICLEEDITEUR
#define ARTICLEEDITEUR
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include "notes.h"
class ArticleEditeur: public QDialog
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots

    QLineEdit *id;
    QLineEdit *titre;
    QTextEdit *text;

    QLabel *id1;
    QLabel *titre1;
    QLabel *text1;

    QPushButton *save;

    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *ctext;
    QVBoxLayout *couche;

    Article *article; //pointeur vers l'article Ã  afficher par la fenetre

public:
    explicit ArticleEditeur (Article& article,QWidget *parent=0,bool n=false);
    //explicit pour empÃªcher la conversion implicite de article vers Article

signals:
private slots:
    void activerSave(QString ="");
    //la valeur par dÃ©faut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveArticle();


};

#endif // ARTICLEEDITEUR


