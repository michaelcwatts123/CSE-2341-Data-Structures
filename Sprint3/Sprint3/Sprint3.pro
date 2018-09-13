TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../lib/michaelString.cpp \
    fileparse.cpp \
    customsort.cpp

HEADERS += \
    ../../lib/michaelString.h \
    ../../lib/michaelvectors.h \
    fileparse.h \
    customsort.h
