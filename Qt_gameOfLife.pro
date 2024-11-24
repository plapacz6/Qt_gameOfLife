#-------------------------------------------------
#
# Project created by QtCreator 2022-12-27T05:07:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_gameOfLife
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

INCLUDEPATH += /usr/local/include/gtest
LIBS += -lgtest -lgtest_main -lpthread

SOURCES += \
    TQ_GolfBoardPreview.cpp \
    T_GolfIndex.cpp \
    T_GolfPatternDescription.cpp \
        main.cpp \
        mainwindow.cpp \
    T_Golf_engine.cpp \
    tests/test_T_GolfIndex.cpp \
    tests/test_T_GolfPatternDescription.cpp

HEADERS += \
    TQ_GolfBoardPreview.h \
    T_GolfIndex.h \
    T_GolfPatternDescription.h \
        mainwindow.h \
    T_Golf_engine.h

FORMS += \
        mainwindow.ui
