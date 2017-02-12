#-------------------------------------------------
#
# Project created by QtCreator 2017-02-04T19:23:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIC10CProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    ../Dictionary.cpp \
    ../Matrix.cpp \
    ../Sudoku_Generator.cpp \
    ../Sudoku_Solver.cpp \
    board.cpp


HEADERS  += mainwindow.h \
    ../Dictionary.h \
    ../Matrix.h \
    ../Node.h \
    ../Stack.h \
    ../Sudoku_Generator.h \
    ../Sudoku_Solver.h \
    board.h


FORMS    += mainwindow.ui

DISTFILES += \
    sudokutest.txt
