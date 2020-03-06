#-------------------------------------------------
#
# Project created by QtCreator 2019-05-10T21:27:51
#
#-------------------------------------------------

QT       += core gui
QT+=xml
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab9
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    adddialog.cpp \
    sqlite_storage.cpp \
    auth.cpp

HEADERS += \
        mainwindow.h \
    optional.h \
    storage.h \
    adddialog.h \
    sqlite_storage.h \
    user.h \
    auth.h \
    lection.h \
    topic.h \
    adddialog.h


FORMS += \
        mainwindow.ui \
    adddialog.ui \
    auth.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/sqlite/data.sqlite \
    data/xml/capitals.xml \
    data/xml/countries.xml \
    data/csv/capitals.csv \
    data/csv/countries.csv
