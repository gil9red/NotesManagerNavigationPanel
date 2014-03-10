QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotesManagerNavigationPanel
TEMPLATE = app
DESTDIR = ../bin

#include( notesmodel/notesmodel.pri )

SOURCES += main.cpp\
        mainwindow.cpp \
    hierarchicalmodel.cpp \
    hierarchicalview.cpp

HEADERS  += mainwindow.h \
    hierarchicalmodel.h \
    hierarchicalview.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
