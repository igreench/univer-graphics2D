#-------------------------------------------------
#
# Project created by QtCreator 2014-04-25T00:23:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageviewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp \
    canvas.cpp \
    texture.cpp \
    triangle.cpp

HEADERS  += mainwindow.h \
    imageview.h \
    canvas.h \
    texture.h \
    triangle.h

FORMS    += mainwindow.ui
