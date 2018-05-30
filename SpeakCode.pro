#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T23:07:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpeakCode
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    settings.cpp \
    about.cpp \
    spk_core.cpp \
    writer.cpp

HEADERS += \
        mainwindow.h \
    settings.h \
    about.h \
    spk_core.h \
    writer.h

FORMS += \
        mainwindow.ui \
    settings.ui \
    about.ui

DISTFILES +=

RESOURCES += \
    abouticon.qrc

INCLUDEPATH += $$PWD/Sphinx/include \
               $$PWD/Sphinx/base_include \
               $$PWD/Sphinx/base_include/sphinxbase \
               $$PWD/libpocketsphinx

LIBS += -L/usr/local/lib \
        -lpocketsphinx.3 \
        -lsphinxad \
        -lsphinxbase

APP_FILES.files = $$PWD/settingsFile $$PWD/Sphinx/en-us-semi $$PWD/Sphinx/TAR0572
APP_FILES.path = Contents/MacOS

QMAKE_BUNDLE_DATA += APP_FILES

QMAKE_BUNDLE_DATA += settingsFile


QMAKE_CXXFLAGS += -std=c++11 -O2 -DHAVE_CONFIG_H

