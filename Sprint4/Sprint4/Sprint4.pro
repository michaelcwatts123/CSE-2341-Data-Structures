TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../lib/michaelString.cpp \
    flight.cpp \
    fileparse.cpp \
    city.cpp \
    backtrack.cpp \
    flightplan.cpp \
    test.cpp

HEADERS += \
    ../../lib/michaelString.h \
    ../../lib/michaelvectors.h \
    ../../lib/test.h \
    ../../lib/linkedlist.h \
    ../../lib/listnode.h \
    ../../lib/stack.h \
    flight.h \
    fileparse.h \
    city.h \
    backtrack.h \
    flightplan.h \
    ../../lib/catch.hpp
