#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T22:49:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TDMapGui
TEMPLATE = app

CONFIG   += c++11

SOURCES += main.cpp\
    Game/cell.cpp \
    Game/game.cpp \
    Game/map.cpp \
    Game/tower.cpp \
    Graphics/mapscene.cpp \
    Graphics/toweritem.cpp \
    Ui/createmapdialog.cpp \
    Ui/placetowerdialog.cpp \
    Ui/tdmap.cpp \
    Ui/towerinspectordialog.cpp \
    Graphics/critteritem.cpp

HEADERS  += Game/cell.h \
    Game/critter.h \
    Game/game.h \
    Game/tower.h \
    Graphics/mapscene.h \
    Graphics/toweritem.h \
    Ui/createmapdialog.h \
    Ui/placetowerdialog.h \
    Ui/tdmap.h \
    Ui/towerinspectordialog.h \
    Graphics/critteritem.h \
    Game/map.h

FORMS    += Ui/createmapdialog.ui \
    Ui/placetowerdialog.ui \
    Ui/tdmap.ui \
    Ui/towerinspectordialog.ui

INCLUDEPATH += $$PWD/Game \
    $$PWD/Graphics \
    $$PWD/Ui
