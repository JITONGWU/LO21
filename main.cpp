#include <QApplication>
#include<iostream>
#include<Qlist>
#include<QFile>
#include<QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "window.h"
#include "notes.h"
#include "relationmanager.h"
#include "relation.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   FenPrincipale f;
   f.show();

    return app.exec();
}
