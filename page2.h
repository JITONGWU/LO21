#ifndef PAGE2_H
#define PAGE2_H
#include "window.h"


class RelationEditeur;
class Page2 : public QMainWindow
{
    friend class NotesManager;
    friend class RelationManager;

    Q_OBJECT

    QWidget *zoneCentrale;
    QPushButton *AjoutRelation;
    QPushButton *supprimerR;//pour supprimer une relation
    QPushButton *update;
    QWidget *vide;
    RelationEditeur *re;
    RelationEditeur *rv;
    QScrollArea *scrollRelation;
    QHBoxLayout *buttons;
    QHBoxLayout *layout;
    QVBoxLayout *couche;

public:
    ListeRelation *listR;
    Page2(QWidget *parent);
private slots:
    void receive(QString titre);//recevoir le signal de relation editeur
public slots:
    void afficherWidget(QListWidgetItem* item);
    void RelationEditeurVide();
    void supprimerRelation();
    void Update();
};


#endif // PAGE2_H
