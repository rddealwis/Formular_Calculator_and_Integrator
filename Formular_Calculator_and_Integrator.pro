#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T11:31:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Formular_Calculator_and_Integrator
TEMPLATE = app


SOURCES += main.cpp\
        mainscreen.cpp \
    aboutcalculator.cpp \
    help.cpp

HEADERS  += mainscreen.h \
    aboutcalculator.h \
    help.h

FORMS    += mainscreen.ui \
    aboutcalculator.ui \
    help.ui

RESOURCES += \
    resources.qrc
