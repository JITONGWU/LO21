#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notes.h"
#include <QtGui>
#include <QtCore>
#include<QWidget>
#include <QHBoxLayout>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
