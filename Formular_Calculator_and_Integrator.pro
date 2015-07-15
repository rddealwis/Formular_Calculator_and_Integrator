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
    help.cpp \
    constantelement.cpp \
    cosinefunctionelement.cpp \
    dividefunctionelement.cpp \
    formulaelement.cpp \
    functionelement.cpp \
    minusfunctionelement.cpp \
    multiplefunctionelement.cpp \
    plusfunctionelement.cpp \
    powerfunctionelement.cpp \
    sinefunctionelement.cpp

HEADERS  += mainscreen.h \
    aboutcalculator.h \
    help.h \
    constantelement.h \
    cosinefunctionelement.h \
    dividefunctionelement.h \
    formulaelement.h \
    formulator.h \
    functionelement.h \
    minusfunctionelement.h \
    multiplefunctionelement.h \
    plusfunctionelement.h \
    powerfunctionelement.h \
    sinefunctionelement.h

FORMS    += mainscreen.ui \
    aboutcalculator.ui \
    help.ui

RESOURCES += \
    resources.qrc
