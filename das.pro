#-------------------------------------------------
#
# Project created by QtCreator 2011-12-01T19:44:38
#
#-------------------------------------------------

QT       += core
QT       += xml
QT       += network
QT       -= gui

TARGET = das
CONFIG   += console
CONFIG   += network
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    config.cpp \
    querysender.cpp \
    abstractnetworkclient.cpp \
    tcpclient.cpp \
    networkprotocol.cpp \
    vars.cpp \
    loopthread.cpp \
    modbustcp.cpp

HEADERS += \
    config.h \
    querysender.h \
    abstractnetworkclient.h \
    tcpclient.h \
    networkprotocol.h \
    vars.h \
    loopthread.h \
    modbustcp.h


























































