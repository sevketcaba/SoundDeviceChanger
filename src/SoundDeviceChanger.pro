#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T13:59:05
#
#-------------------------------------------------

QT       += core gui quick quickwidgets webengine webenginewidgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundDeviceChanger
TEMPLATE = app


SOURCES += main.cpp\
        bcontroller.cpp \
    bdeviceinfo.cpp \
    bdevicemanager.cpp \
    bsettings.cpp \
    awesome/qtawesome.cpp \
    awesome/qtawesomeanim.cpp \
    bdevicewatcher.cpp \
    bdatabaseloader.cpp

HEADERS  += bcontroller.h \
    bdeviceinfo.h \
    bdevicemanager.h \
    bdefinitions.h \
    bsettings.h \
    awesome/qtawesome.h \
    awesome/qtawesomeanim.h \
    bdevicewatcher.h \
    ipolicyconfig.h \
    bdatabaseloader.h

LIBS += -lole32

RESOURCES += \
    resources.qrc
