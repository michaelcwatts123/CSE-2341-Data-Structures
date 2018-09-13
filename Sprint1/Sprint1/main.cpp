#include <iostream>
#include "filereader.h"
#include "test.h"
#include "catch.hpp"
#define TEST false
using namespace std;

int main(int argc, const char * argv[])
{

    if(TEST){
            int result = Catch::Session().run();


            return (result <0xff ? result : 0xff);
        } else {
    FileReader files(argv); //creates fileReader object to read in files
}

    return 0;
}
