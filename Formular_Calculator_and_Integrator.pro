#-------------------------------------------------
#
# Project created by QtCreator 2015-07-01T11:31:44
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Formular_Calculator_and_Integrator
TEMPLATE = app
CONFIG +=c++11
QMAKE_CXXFLAGS += -bigobj

SOURCES += main.cpp\
        mainscreen.cpp \
    constantelement.cpp \
    cosinefunctionelement.cpp \
    dividefunctionelement.cpp \
    formulaelement.cpp \
    functionelement.cpp \
    minusfunctionelement.cpp \
    multiplefunctionelement.cpp \
    plusfunctionelement.cpp \
    powerfunctionelement.cpp \
    sinefunctionelement.cpp \
    variableelement.cpp \
    dlgsaveformula.cpp \
    dlgloadformula.cpp \
    xmlfilehandling.cpp \
    qcustomplot.cpp \
    dlgsavegraph.cpp \
    dlggraphviewer.cpp \
    dlgcalareaundercurve.cpp \
    dlgintegration.cpp

HEADERS  += mainscreen.h \
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
    sinefunctionelement.h \
    variableelement.h \
    dlgsaveformula.h \
    dlgloadformula.h \
    xmlfilehandling.h \
    qcustomplot.h \
    dlgsavegraph.h \
    dlggraphviewer.h \
    exprtk.hpp \
    dlgcalareaundercurve.h \
    dlgintegration.h

FORMS    += mainscreen.ui \
    dlgsaveformula.ui \
    dlgloadformula.ui \
    dlgsavegraph.ui \
    dlggraphviewer.ui \
    dlgcalareaundercurve.ui \
    dlgintegration.ui

RESOURCES += \
    resources.qrc
