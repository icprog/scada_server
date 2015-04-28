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
    scadaserver.cpp \
    deviceinterface.cpp \
    sensorconnection.cpp \
    hmi_connection.cpp \
    common/humanmachineinterface.cpp \
    common/packet.cpp \
    common/scadadevice.cpp \
    common/sensor.cpp

HEADERS += \
    scadaserver.h \
    deviceinterface.h \
    sensorconnection.h \
    hmi_connection.h \
    common/humanmachineinterface.h \
    common/packet.h \
    common/scadadevice.h \
    common/sensor.h
