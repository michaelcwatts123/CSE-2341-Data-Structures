#include "dictionary.h"
#include "michaelString.h"
#include <fstream>

Dictionary::Dictionary()
{

}

int Dictionary:: getLength(){ //returns length of dictionary
    return lengthOfDictionary;
}

bool Dictionary:: compare(michaelString word){ //compares michael string to dicitionary
    for(int i = 0; i < lengthOfDictionary; i++){ //searches entire dictionary for michaelString equal
        if (filledDictionary[i] == word){
            return true; //if found
        }
    }
    return false; //else
}


void Dictionary :: setLength(int length){ //sets the number of words in dicitonary

    filledDictionary = new michaelString[length]; //dynamically creates array of michaelStrings in the appropriate size
    lengthOfDictionary = length; //saves length of dictionary


}

void Dictionary :: add(const char *buffer){ //adds cStrings to dictionary

    michaelString word(buffer); //converts cString to custom michaelString
    word.upper(); //capitalizes word to avoid comparision errors

    filledDictionary[counter] =  word; //stores word in next open dicitonary slot


    counter++; //marks next open dicitionary slot
}

void Dictionary:: printer(){ //prints entire contents of dictionary
    for(int x = 0; x < lengthOfDictionary; x++){

        cout << filledDictionary[x] << endl;
    }
}

michaelString Dictionary :: getWord(int entry){ //returns indivual word from dictionary
    if(entry < lengthOfDictionary){ //confirms dictionary entry is inside dictionary
    return filledDictionary[entry]; //returns correct entry
    } else {
        return filledDictionary[0]; //else just returns first entry
    }
}






