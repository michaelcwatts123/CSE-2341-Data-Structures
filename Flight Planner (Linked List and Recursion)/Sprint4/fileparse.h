#ifndef FILEPARSE_H
#define FILEPARSE_H
#include <fstream>
#include <../../lib/michaelString.h>
#include <../../lib/michaelvectors.h>
#include "city.h"
#include <../../lib/stack.h>
#include <backtrack.h>

class fileparse
{
private:
    int numberOfLines; //holds the number of lines in the input file
    int cityFlag = 0; //flag for if text is an orgin city
    int destinationFlag = 1; //flag for if text is a destination city
    int costFlag = 1; //flag for if text is a cost
    int timeFlag = 1; //flag for if text is a time
    int bufferLetterCount = 0;//keeps track of buffer letter location

    michaelString orginName; //holds the name of orgin city
    michaelString destinationName; //holds the name of the destination city
    int cost = 0; //holds cost
    int time = 0; //holds time

    LinkedList<LinkedList<City>>  adjCity;
    City Orgin; //holds the orgin city object

    michaelVector<michaelString> OrginCityNames;


    int numberOfOrigins = 0; //tracks the number of orgin cities

public:
    fileparse(); //default constructor
    fileparse(const char **&); //constructor
    void cleanBuffer(char *); //cleans buffer
    void clean(); //resets all flags to inital postion
    void constructAdjList();
    char c; //holds the character c from input file
    char buffer[35] = {' '}; //holds text of input

};

#endif // FILEPARSE_H
