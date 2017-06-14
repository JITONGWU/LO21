#ifndef PAGE3_H
#define PAGE3_H
#include "window.h"
class Page3 : public QMainWindow {
    friend class NotesManager;
    friend class RelationManager;
    Q_OBJECT
    QWidget *zoneCentrale;
    QString choix;
    QPushButton *restaurer;
    QPushButton *supprimer;
    QPushButton *update;
    QListWidget *corbeille;
    QHBoxLayout *buttons;
    QVBoxLayout *couche;
public:

    Page3(QWidget *parent);
public slots:
    void Activer(QListWidgetItem*);
    void Restaurer();
    void Supprimer();
    void Update();
 private slots:
};
#endif // PAGE3_H
