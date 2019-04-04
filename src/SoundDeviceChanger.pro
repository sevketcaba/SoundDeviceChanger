#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T13:59:05
#
#-------------------------------------------------

QT       += core gui quick quickwidgets webengine webenginewidgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundDeviceChanger
TEMPLATE = app

include($$PWD/appinfo.pri)

SOURCES += main.cpp\
        bcontroller.cpp \
    bdeviceinfo.cpp \
    bdevicemanager.cpp \
    awesome/qtawesome.cpp \
    awesome/qtawesomeanim.cpp \
    bdevicewatcher.cpp \
    bdatabaseloader.cpp \
    bsettingswindow.cpp \
    bsettings.cpp

HEADERS  += bcontroller.h \
    bdeviceinfo.h \
    bdevicemanager.h \
    bdefinitions.h \
    awesome/qtawesome.h \
    awesome/qtawesomeanim.h \
    bdevicewatcher.h \
    ipolicyconfig.h \
    bdatabaseloader.h \
    bsettingswindow.h \
    bsettings.h

LIBS += -lole32

RESOURCES += \
    resources.qrc
