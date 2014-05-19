#-------------------------------------------------
#
# Project created by QtCreator 2014-02-17T18:25:18
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = fortress
TEMPLATE = app


SOURCES += main.cpp\
        firewallwindow.cpp \
    settingsmanager.cpp \
    filedownloader.cpp \
    fortressgenerator.cpp \
    rulesmanager.cpp

HEADERS  += firewallwindow.h \
    settingsmanager.h \
    defines.h \
    filedownloader.h \
    fortressgenerator.h \
    rulesmanager.h

FORMS    += firewallwindow.ui

OTHER_FILES +=

RESOURCES += \
    res.qrc

LIBS += -lqjson
