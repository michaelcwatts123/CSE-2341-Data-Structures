TEMPLATE = app
CONFIG += console c++11 \
    c++11
SOURCES += main.cpp \
    tests.cpp \
    porter2_stemmer.cpp \
    csvparser.c \
    documentparser.cpp \
    indexedterm.cpp \
    indexhandler.cpp \
    runquery.cpp \
    input.cpp \
    searchengine.cpp

HEADERS += catch.hpp \
    porter2_stemmer.h \
    util/hash.h \
    util/stringview.h \
    avltree.hpp \
    hashtable.hpp \
    indexinterface.hpp \
    csvparser.h \
    documentparser.h \
    indexedterm.h \
    indexhandler.h \
    runquery.h \
    input.h \
    adaptor.hpp \
    searchengine.h
