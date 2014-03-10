QT += core gui
QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotesManagerNavigationPanel
TEMPLATE = app
DESTDIR = ../bin

SOURCES += main.cpp\
        mainwindow.cpp \
    hierarchicalmodel.cpp \
    hierarchicalview.cpp \
    noteeditor.cpp

HEADERS  += mainwindow.h \
    hierarchicalmodel.h \
    hierarchicalview.h \
    noteeditor.h

FORMS    += mainwindow.ui \
    noteeditor.ui

RESOURCES += \
    image.qrc
