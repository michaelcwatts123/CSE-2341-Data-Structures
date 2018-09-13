
#include <iostream>
#include <../../lib/linkedlist.h>
#include <../../lib/listnode.h>
#include <../../lib/stack.h>
#include <fileparse.h>
#define CATCH_CONFIG_RUNNER
#include <../../lib/catch.hpp>

using namespace std;

int main(int argc, const char * argv[])
{

    michaelString parameter3;
    michaelString testFlag;

    if (argc == 2){ //checks if only one parameter
     parameter3 = argv[1]; //check for -t
     testFlag = "-t";
    } else {
        parameter3 = "NO";
        testFlag = "TEST";
    }
    if(parameter3 == testFlag){ //checks parameter to see if -t

            int result = Catch::Session().run(); //runs test if yes

            return (result <0xff ? result : 0xff);
        } else {
        fileparse files(argv); //if test not found, begin indexing


    }



}

