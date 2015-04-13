#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T23:00:29
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = scada_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    packet.cpp \
    scadadevice.cpp \
    sensor.cpp \
    scadaserver.cpp \
    deviceinterface.cpp

HEADERS += \
    packet.h \
    scadadevice.h \
    sensor.h \
    scadaserver.h \
    deviceinterface.h
