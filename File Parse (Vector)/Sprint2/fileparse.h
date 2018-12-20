#ifndef FILEPARSE_H
#define FILEPARSE_H
#include <../../lib/michaelvectors.h>
#include <../../lib/michaelString.h>
#include <entry.h>

class fileParse
{
public:
    fileParse(const char **&); //constructor passed argv array

    void addToEnteries();  //adds phrase to enteries michaelVector
    void phraseLogic(); //logic for handling phrases in []

    char buffer[80]; //character buffer used to form words

    michaelVector<entry> enteries; //michaelVector of index enteries
private:
    int wordFlag = 0;  //flags set of by detection of [ or ]
    int pageFlag = 0; //flag set off by detection of < or >
    int phraseFlag = 1;
    int pageNum; //page number for entery
    int bufferCounter = 0;

    char c; //character read in from file

    michaelString word; //word for entry
};

#endif // FILEPARSE_H
