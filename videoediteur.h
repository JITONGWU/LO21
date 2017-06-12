#ifndef VIDEOEDITEUR
#define VIDEOEDITEUR

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
#include "notemanager.h"

class VideoEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots


    QLabel *id1;
    QLabel *titre1;
    QLabel *desc1;
    QLabel *file1;
    QLabel *vfile1;

    QPushButton *save;
   QPushButton *archieve;
   QPushButton *desarchieve;
    QPushButton *supprimer;
    QPushButton *rest;
    QHBoxLayout *buttons;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *cdesc;
    QHBoxLayout *cfile;
    QHBoxLayout *cvfile;
    QVBoxLayout *couche;
    int restaurer;

public:
    bool arc;
    Video *video;
    QLineEdit *id;
    QLineEdit *titre;
    QTextEdit *desc;
    QLineEdit *file;
    QLineEdit *vfile;
    void setRest(int i){restaurer=i;}

    bool newVid;
    explicit VideoEditeur (Video& vid,QWidget *parent=0, bool n=false, int r=(-1), bool a=false);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
        void SendToPage1(QString);

private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveVideo();

    void archiverVideo();
    void SupprimertousVideo();

};




#endif // AUDIOEDITEUR

