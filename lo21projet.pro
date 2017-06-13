#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T21:52:37
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS = /FS
TARGET = lo21projet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    notes.cpp \
    relation.cpp \
    relationmanager.cpp \
    articleediteur.cpp \
    imageediteur.cpp \
    relationediteur.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    notes.h \
    relation.h \
    relationmanager.h \
    articleediteur.h \
    imageediteur.h \
    relationediteur.h \
    window.h

FORMS    += mainwindow.ui

DISTFILES += \
    notes.xml \
    relations.xml
