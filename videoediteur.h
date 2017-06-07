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

class VideoEditeur: public QWidget
{
    Q_OBJECT     //macro pour pouvoir utiliser les signals et les slots

    QLineEdit *id;
    QLineEdit *titre;
    QTextEdit *desc;
    QLineEdit *file;
    QLineEdit *vfile;

    QLabel *id1;
    QLabel *titre1;
    QLabel *desc1;
    QLabel *file1;
    QLabel *vfile1;

    QPushButton *save;
    QHBoxLayout *cid;
    QHBoxLayout *ctitre;
    QHBoxLayout *cdesc;
    QHBoxLayout *cfile;
    QHBoxLayout *cvfile;
    QVBoxLayout *couche;

    Video *video; //pointeur vers l'article à afficher par la fenetre

public:
    explicit VideoEditeur (Video& vid,QWidget *parent=0);
    //explicit pour empêcher la conversion implicite de article vers Article

signals:
private slots:
    void activerSave(QString ="");
    //la valeur par défaut c'est pour pouvoir la connecter avec deux signals
    //l'un avec un parametre qstring et l'autre sans parametre
public slots:
    void saveVideo();


};


#endif // VIDEOEDITEUR

