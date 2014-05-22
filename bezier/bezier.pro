#-------------------------------------------------
#
# Project created by QtCreator 2014-05-18T22:03:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bezier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    canvas.cpp \
    bezier.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    canvas.h \
    bezier.h

FORMS    += mainwindow.ui
