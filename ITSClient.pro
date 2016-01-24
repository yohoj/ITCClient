#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T20:49:56
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ITSClient
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    videothread.cpp \
    config.cpp \
    md5.cpp

HEADERS  += widget.h \
    protocol.h \
    videothread.h \
    config.h \
    md5.h

FORMS    += widget.ui \
    config.ui

LIBS += -ltinyxml

