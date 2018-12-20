#include "michaelString.h"
#include <iostream>
#include <vector>
using namespace std;
michaelString :: michaelString(){ //default constructor
    length = 0;
    word = new char[0];
};
michaelString :: michaelString(const char * CharArray){ //cString constructor

    length = strlen (CharArray); //finds length of cString
    length+=1; //adds one for null terminator
     word  = new char[length]; //creates char array dynaically for cString
     word[length-1] = '\0'; //adds null terminator
     for(int x = 0; x < length-1; x++){ //stores cString in array
         word[x] = *(CharArray + x);
     }

}
michaelString :: ~michaelString(){
    delete [] word;
}

bool michaelString ::   operator ==( michaelString mString){ //overloaded equality operator
    char * word1Pointer = mString.getWord(); //gets char array for one word
    char * word2Pointer = this->getWord(); //gets char array for other word
    if (length != mString.length){ //first ensures have equal length
        return false; //else return false
    } else {
        for(int x = 0; x < length; x ++){
            if (*(word2Pointer + x) != *(word1Pointer+ x)){ //checks letter by letter for comparision
                return false;
            }
        }
    }
    return true;

}
bool michaelString :: empty(){ //checks to see if michaelString has letters
    char * testString = this->getWord();
    char span[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"; //all valid possible letters
    int check = strspn (testString,span); //checks to see how many valid letters are in cString
    if (check == 0){
        return true; //if none return true
    } else {
        return false; //else return false
    }
}
bool michaelString ::operator >(const michaelString& stringToCompare){ //compares two michaelStrings' lengths
char * word1 = this->getWord();
char * word2 = stringToCompare.word;
int shorter = 0;
if (this->length < stringToCompare.length){
        shorter = this->length;
} else {
    shorter = stringToCompare.length;
}
for (int i = 0; i < shorter; i++){
    int wordvalue1 = word1[i];
    int wordvalue2 = word2[i];
    if(wordvalue1 < wordvalue2){
        return false;
    }
}
return true;
}

char* michaelString ::   getWord(){ //allows access to private data member word
    return word;
}

char michaelString ::operator [](int i){ //overloaded [] operator, returns individual char
    if (i <= length){ // confirms valid length
    return word[i];
    } else {
        return '\0'; //else returns null
    }

}

michaelString :: michaelString(const michaelString &stringToCopy){


    this->length = stringToCopy.length; //reassigns length value
    word = new char[length]; //dynamically creates new char array for new word
    for (int i = 0; i < length; i++){ //cycles through and stores indiviual char
        word[i] = stringToCopy.word[i];
    }



}
michaelString michaelString :: subString(int start, int stop){

    if(start < 0){
        start = length + start + 1;
    }
    if (stop < 0){
        stop = length + stop + 1;
    }

    int length = stop - start;
    char subString[length];
    for(int i = 0; i < length; i++){
        subString[i] = this->word[start + i];
    }
    michaelString newsubString(subString);
    return newsubString;
}


 michaelString& michaelString :: operator =(const michaelString& stringToCopy){ //overloaded assignment operator
    delete [] word; //deletes old word value
    this->length = stringToCopy.length; //reassigns length value
    word = new char[length]; //dynamically creates new char array for new word
    for (int i = 0; i < length; i++){ //cycles through and stores indiviual char
        word[i] = stringToCopy.word[i];
    }
    return *this; //returns pointer to new word
}

void michaelString :: upper(){ //converts michaelString to all caps
    for(int i = 0; i < length; i++){ //cycles through string
        word[i] = toupper(word[i]); //turns character to caps version
    }
}

int michaelString :: getLength(){
    return length-1;
}







