QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = calepin
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += MainWindow.h \
           Personne.h \
    cpersonnetablemodele.h \
    cpersonnedelegate.h
SOURCES += main.cpp \
           MainWindow.cpp \
           Personne.cpp \
    cpersonnetablemodele.cpp \
    cpersonnedelegate.cpp
