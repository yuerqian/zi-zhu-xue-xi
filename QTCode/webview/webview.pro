#-------------------------------------------------
#
# Project created by QtCreator 2018-12-25T16:57:05
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webview.cpp \
    jscontest.cpp

HEADERS  += mainwindow.h \
    webview.h \
    jscontest.h

FORMS    += mainwindow.ui
