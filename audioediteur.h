#ifndef AUDIOEDITEUR
#define AUDIOEDITEUR

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
#include <QMediaPlayer>
#include "notes.h"
#include "notemanager.h"

class AudioEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots


    QLabel *id1;
    QLabel *titre1;
    QLabel *desc1;
    QLabel *file1;
    QLabel *afile1;

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
    QHBoxLayout *cafile;
    QVBoxLayout *couche;
    int restaurer;


public:
    bool arc;
    Audio *audio;
    QLineEdit *id;
    QLineEdit *titre;
    QLineEdit *desc;
    QLineEdit *file;
    QLineEdit *afile;
    QMediaPlayer *sound;
    QPushButton *start;

    void setRest(int i){restaurer=i;}


    bool newAud;
    explicit AudioEditeur (Audio& aud,QWidget *parent=0, bool n=false, int r=(-1), bool a=false);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
    void SendToPage1(QString);

private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveAudio();

    void archiverAudio();
    void SupprimertousAudio();
    void SupprimertousAudio2(QString id);
    void desarchiver();
    void DemandeSave();
    void getFile();
    void play();
};




#endif // AUDIOEDITEUR

