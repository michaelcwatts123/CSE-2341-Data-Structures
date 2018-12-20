#include "dictionary.h"
#ifndef FILEREADER_H
#define FILEREADER_H


class FileReader
{
public:
    FileReader(const char **&); //reads in both files, seperates words into michael strings with the buffer

    Dictionary d; //dictionary used throughout object's lifetime
private:
    char buffer[30]; //word storage buffer
    char c; //character to hold read in from file

    int letterCounter=0; //keeps count of individual letters
    int lineCounter = 0; //keeps count of lines from file
    int wordCounter = 1; //keeps count of words from file
};

#endif // FILEREADER_H
