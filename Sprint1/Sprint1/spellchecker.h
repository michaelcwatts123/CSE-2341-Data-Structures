#include "dictionary.h"
#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H


class spellChecker
{
public:
    spellChecker(const char * buffer, Dictionary d, int wordCount, int lineCount,const char **&argv); //outputs words and suggestions
private:
    void suggestion(michaelString, Dictionary, michaelString *); //method for suggestion correct words from misspelled ones

    int randFill(Dictionary); //random number generator for back up
};

#endif // SPELLCHECKER_H
