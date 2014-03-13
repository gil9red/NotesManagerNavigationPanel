QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotesManagerNavigationPanel
TEMPLATE = app
DESTDIR = ../bin

include( NavigationPanel/NavigationPanel.pri )

SOURCES += main.cpp\
        mainwindow.cpp \
    noteeditor.cpp

HEADERS  += mainwindow.h \
    noteeditor.h

FORMS    += mainwindow.ui \
    noteeditor.ui
