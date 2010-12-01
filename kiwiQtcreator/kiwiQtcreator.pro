#-------------------------------------------------
#
# Project created by QtCreator 2010-12-01T19:48:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = kiwiQtcreator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../src/kiwi/core/Node.cpp \
    ../src/kiwi/core/CanonicalFilter.cpp

OTHER_FILES += \
    ../src/kiwi/core/OutputPort.ih \
    ../src/kiwi/core/InputPort.ih

HEADERS += \
    ../src/kiwi/core/Node.hpp \
    ../src/kiwi/core/Filter.hpp \
    ../src/kiwi/core/Container.hpp \
    ../src/kiwi/core/Commons.hpp \
    ../src/kiwi/core/CanonicalFilter.hpp
