#-------------------------------------------------
#
# Project created by QtCreator 2014-02-17T18:25:18
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = hsp2
TEMPLATE = app


SOURCES += main.cpp\
        firewallwindow.cpp \
    functionwrapper.cpp \
    settingsmanager.cpp

HEADERS  += firewallwindow.h \
    functionwrapper.h \
    settingsmanager.h \
    defines.h

FORMS    += firewallwindow.ui

OTHER_FILES +=

RESOURCES += \
    res.qrc
