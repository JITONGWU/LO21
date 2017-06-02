#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include"relation.h"
#include<Qlist>
#include<QMessageBox>
#include "Notes.h"
#include "relationmanager.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
//#include "NoteEditeur.h"

using namespace std;
int main(int argc, char *argv[])
{

        QApplication app(argc, argv);
        QString fichierNotes = "notes.xml";
        QString fichierRelations ="relations.xml";
        NotesManager& m=NotesManager::getManager();
        RelationManager & r=RelationManager::getManager();
        //Reference & ref=Reference::getRef();
        m.setFilename(fichierNotes);
        r.setFilename(fichierRelations);

        m.load();
        r.load();
        //Note& a=m.getNote("id:avant_propos");
        //NoteEditeur fenetre(a);
        //fenetre.show();
        return app.exec();
}
