#-------------------------------------------------
#
# Project created by QtCreator 2012-04-23T10:37:18
#
#-------------------------------------------------

QT       += core gui

TARGET = testnumberinput
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    otherdialog.cpp \
    inputdialog.cpp

HEADERS  += maindialog.h \
    otherdialog.h \
    inputdialog.h

FORMS    += maindialog.ui \
    otherdialog.ui \
    inputdialog.ui \
    syszuxpinyin.ui
LIBS += -lsyszuxpinyin
