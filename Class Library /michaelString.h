#ifndef MICHAELSTRING_H
#define MICHAELSTRING_H

#include <iostream>
#include <cstring>
using namespace std;
class michaelString{
public:
   michaelString(const char*); //constructor
   michaelString(); //default constructor
   michaelString(const michaelString &); //copy constructor
   ~michaelString(); //destructor


   bool operator >(const michaelString&);
   bool operator ==(const michaelString); //comparison operator
   bool operator !=(const michaelString);
   bool empty( ); //detects empty cStrings
   bool ignoreCaseCompare(const michaelString); //ignore case compare

   char* getWord() const; //returns word array
   char operator [](int); //overloaded brackets operator to get individual characters

   friend ostream& operator <<(ostream& os, const michaelString& mstring); //overloaded << operator

   michaelString& operator =(const michaelString& stringToCopy); //overloaded assignment operator
   michaelString subString(int, int); //gets substring from michaelString

   void upper(); //converts word to upper case

   int getLength() ; //gets length of word


private:
    int length; //length of the word

    char * word; //char array holding cString


friend ostream& operator <<(ostream& os, const michaelString& mstring){ //overloaded << operator for display

        for(int i = 0; i < mstring.length; i++){
            if(mstring.word[i] == '\0'){
                break;
            }
            os << mstring.word[i];
        }


       // os << mstring.word;

        return os;
    }

};

#endif // MICHAELSTRING_H
