#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "documentparser.h"
#include "runquery.h"
#include "indexhandler.h"
#include <iostream>

/**
 * Provides user interface to the rest of the search engine system.
 *
 * Owner: Evan
 */
class SearchEngine
{
    void maintenanceMode();
    void interactiveMode();
public:

    SearchEngine();
    void run();
};

#endif // SEARCHENGINE_H
