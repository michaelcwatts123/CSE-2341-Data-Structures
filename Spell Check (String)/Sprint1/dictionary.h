#include "michaelString.h"
#include <fstream>
#ifndef DICTIONARY_H
#define DICTIONARY_H


class Dictionary
{
public:
    Dictionary(); //constructor

    int getLength(); //returns length of dictionary

    bool compare(michaelString); //compares michaelString to all entries

    void setLength(int);//sets dictionary length
    void add(const char * buffer); //adds word to dictionary
    void printer(); //prints contents of dictionary

    michaelString getWord(int);  //gets individual entry
private:
    int counter = 0;
    int lengthOfDictionary = 0;

    michaelString * filledDictionary;


};

#endif // DICTIONARY_H
