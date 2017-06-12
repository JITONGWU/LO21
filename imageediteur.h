#ifndef IMAGEEDITEUR_H
#define IMAGEEDITEUR_H
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
#include <QMovie>
#include "notes.h"
class ImageEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots


    QLabel *id1;
    QLabel *titre1;
    QLabel *desc1;
    QLabel *file1;

    QPushButton *save;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *cdesc;
    QHBoxLayout *cfile;
    QVBoxLayout *couche;

    bool newI;


public:

    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *desc;
    QLineEdit *file;
    QMovie *movie;////////////////////////////
    QLabel *position;///////////////////////////
    Image *image; //pointeur vers l'article à afficher par la fenetre

    explicit ImageEditeur (Image& im,QWidget *parent=0,bool n=false);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
    void SendToPage1(QString);

private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveImage();
    void getFile();///////////////////////


};
#endif // IMAGEEDITEUR_H
