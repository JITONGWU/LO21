#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T16:51:12
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

QMAKE = /FS
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += xml


QMAKE_LFLAGS = -std=c++11

TARGET = LO21
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
    relation.cpp \
    notes.cpp \
    relationmanager.cpp \
    window.cpp \
    articleediteur.cpp \
    imageediteur.cpp \
    relationediteur.cpp \
    page3.cpp \
    page2.cpp \
    audioediteur.cpp \
    tacheediteur.cpp \
    videoediteur.cpp \
    xml.cpp \
    page1_newnote.cpp \
    page1_afficherwidget.cpp \
    page1.cpp

HEADERS  += \
    relation.h \
    relationmanager.h \
    window.h \
    articleediteur.h \
    notes.h \
    imageediteur.h \
    relationediteur.h \
    notemanager.h \
    audioediteur.h \
    videoediteur.h \
    tacheediteur.h \
    page1.h \
    page2.h \
    page3.h

FORMS    +=


DISTFILES +=
