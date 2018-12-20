#include <../../lib/michaelString.h>
#include<../../lib/michaelvectors.h>
#ifndef FILEPARSE_H
#define FILEPARSE_H


class FileParse
{
public:
   FileParse(const char **&argv); //constructor
private:
   michaelVector<michaelString> listToBeSorted; //michaelVector which holds the list of words

   int numWords = 0; //holds the total number of words
   int numWordsToSort = 0; //holds the number of words to be sort
   int firstWordflag = 0; //flag to determine if the biffer holds the first word in the buffer
   int secondWordFlag = 0; //flag to determine if the biffer holds the second word in the buffer

   char buffer[35]; //buffer to hold each word
};

#endif // FILEPARSE_H
