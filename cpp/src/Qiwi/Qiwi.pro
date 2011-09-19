#-------------------------------------------------
#
# Project created by QtCreator 2011-01-02T02:25:20
#
#-------------------------------------------------

QT       += core gui

TARGET = Qiwi
TEMPLATE = app


SOURCES += main.cpp\
        QiwiMainWindow.cpp \
    NodeView.cpp \
    NodePortView.cpp \
    NodeLinkView.cpp \
    TemporaryPortView.cpp \
    Commons.cpp

HEADERS  += QiwiMainWindow.hpp \
    NodeView.hpp \
    NodePortView.hpp \
    NodeLinkView.hpp \
    Commons.hpp \
    TemporaryPortView.hpp

FORMS    += QiwiMainWindow.ui
