#-------------------------------------------------
#
# Project created by QtCreator 2019-02-17T22:48:04
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrueWish
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    sidebar.cpp \
    titlebar.cpp \
    maincontent.cpp \
    customlineedit.cpp \
    database.cpp \
    customlabel.cpp \
    income.cpp \
    expenditure.cpp \
    customwidget.cpp

HEADERS += \
        mainwindow.h \
    sidebar.h \
    titlebar.h \
    maincontent.h \
    customlineedit.h \
    database.h \
    customlabel.h \
    income.h \
    expenditure.h \
    customwidget.h

FORMS += \
        mainwindow.ui \
    maincontent.ui \
    inandex.ui

RESOURCES += \
    ../icons/icons.qrc
