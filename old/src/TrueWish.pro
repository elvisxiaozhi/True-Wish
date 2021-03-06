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
    customlabel.cpp \
    customlineedit.cpp \
    expenditure.cpp \
    income.cpp \
    main.cpp \
    maincontent.cpp \
    mainwindow.cpp \
    paintedwidget.cpp \
    sidebar.cpp \
    titlebar.cpp \
    wish.cpp \
    core/database.cpp \
    wishlist.cpp \
    inandexwidget.cpp \
    wishdetail.cpp \
    customprogressbar.cpp

HEADERS += \
    customlabel.h \
    customlineedit.h \
    expenditure.h \
    income.h \
    maincontent.h \
    mainwindow.h \
    paintedwidget.h \
    sidebar.h \
    titlebar.h \
    wish.h \
    core/database.h \
    wishlist.h \
    inandexwidget.h \
    wishdetail.h \
    customprogressbar.h

FORMS += \
        mainwindow.ui \
    maincontent.ui \
    inandex.ui \
    wish.ui \
    wishlist.ui

RESOURCES += \
    ../icons/icons.qrc

SUBDIRS += \
    TrueWish.pro
