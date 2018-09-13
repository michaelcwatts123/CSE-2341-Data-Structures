#define CATCH_CONFIG_RUNNER
#define CSV_IO_NO_THREAD
#include <iostream>
#include <string>
#include "catch.hpp"
#include "csvparser.h"
//Used csv parser found here https://sourceforge.net/projects/cccsvparser/
#include "documentparser.h"
#include "indexhandler.h"
#include "runquery.h"
#include "searchengine.h"

using namespace std;

int runCatchTests(int argc, char* argv[]) {
    return Catch::Session().run();
}

int main(int argc, char *argv[])
{
    if (argc > 1 && std::string(argv[1]) == std::string("-t")) {
        return runCatchTests(argc, argv);
    } else {
        SearchEngine se;
        se.run();
        return 0;
    }
}
