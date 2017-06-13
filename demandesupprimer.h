#ifndef DEMANDESUPPRIMER_H
#define DEMANDESUPPRIMER_H

#endif // DEMANDESUPPRIMER_H


#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include "articleediteur.h"
#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class DialogSup : public QDialog
{
        Q_OBJECT

public:

        DialogSup(QWidget *parent , QString id, ArticleEditeur *p);
        ~DialogSup();

private:
        ArticleEditeur *par;
        QHBoxLayout *H;
        QVBoxLayout *V;

        QLabel *label;
        QString id;
        QPushButton *oui;
        QPushButton *non;
public slots:
        void SupprimerArticle();


};

#endif // FINDDIALOG_H
