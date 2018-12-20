TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../lib/michaelString.cpp \
    entry.cpp \
    fileparse.cpp \
    fileoutput.cpp

HEADERS += \
    ../../lib/michaelString.h \
    ../../lib/michaelvectors.h \
    ../../lib/test.h \
    entry.h \
    fileparse.h \
    ../../Sprint1/Sprint1/catch.hpp \
    fileoutput.h
