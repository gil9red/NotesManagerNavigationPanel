QT += xml

HEADERS += \
    $$PWD/hierarchicalview.h \
    $$PWD/hierarchicalmodel.h \
    $$PWD/basemodelitem.h \
    $$PWD/notemodelitem.h \
    $$PWD/foldermodelitem.h \
    $$PWD/trashmodelitem.h

SOURCES += \
    $$PWD/hierarchicalview.cpp \
    $$PWD/hierarchicalmodel.cpp \
    $$PWD/basemodelitem.cpp \
    $$PWD/notemodelitem.cpp \
    $$PWD/foldermodelitem.cpp \
    $$PWD/trashmodelitem.cpp

RESOURCES += $$PWD/NavigationPanel.qrc
