#ifndef PAGE1_H
#define PAGE1_H
#include "window.h"
class Page1 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;
    QPushButton *update;
    QPushButton *AjoutArticle;
    QPushButton *AjoutTache;
    QPushButton *AjoutImage;
    QPushButton *AjoutAudio;
    QPushButton *AjoutVideo;

    QLabel * ascend;
    QLabel *descend;
    QVBoxLayout *arbo;
    QListWidget *listAscend;
    QListWidget *listDescend;

    QWidget *vide;



    QListWidget *listWidget;
    ListeOldNotes *listWidget2;
    QListWidget *NotesArchieve;
    QListWidget *Taches;
    QVBoxLayout *List;
    QHBoxLayout *layout;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:
    ArticleEditeur *av;
       ImageEditeur *iv;
       TacheEditeur *tv;
       AudioEditeur *adv;
       VideoEditeur *vv;

       ArticleEditeur *ae;
       ImageEditeur *ie;
       TacheEditeur *te;
       AudioEditeur *ade;
       VideoEditeur *ve;

       ArticleEditeur *ar;
       ImageEditeur *ir;
       TacheEditeur *tar;
       AudioEditeur *adr;
       VideoEditeur *vr;

       ArticleEditeur *aa;
       ImageEditeur *ia;
       TacheEditeur *ta;
       AudioEditeur *ada;
       VideoEditeur *va;


    Page1(QWidget *parent);
public slots:
    void afficherWidget(QListWidgetItem* item);
    void ArticleEditeurVide();
    void ImageEditeurVide();
    void afficherArbo(QListWidgetItem*);
    void TacheEditeurVide();
    void AudioEditeurVide();
    void VideoEditeurVide();
    void restaurerVersion(QListWidgetItem* item);
    void afficherNotesArch(QListWidgetItem*);


    void Update();
private slots:
    void receive(QString id);


};
#endif // PAGE1_H
