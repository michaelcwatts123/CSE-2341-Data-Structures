#include "entry.h"
#include <../../lib/michaelvectors.h>
entry:: entry(){ //default constructor

}

entry::entry(int &pageNumber, michaelString &wordToAdd)
{

    addToNum(pageNumber); //adds pageNumber to pageNumbers michaelVector
    word = wordToAdd; //saves word to be indexed

}
entry :: entry(const entry & enteryToBeCopied){ //copy constructor
    this->word = enteryToBeCopied.word; //copies word
    this->pageNumbers = enteryToBeCopied.pageNumbers; //copies pageNumbers michaelvector


}

 entry& entry::operator =(const entry& enteryToBeCopied ){ //copy constructor
     if(*this == enteryToBeCopied){ //checks to see if entry is assigned to itself
         return *this;
     } else {
         this->word = enteryToBeCopied.word; //copies word
         this->pageNumbers = enteryToBeCopied.pageNumbers; //copies pageNumbers michaelvector
     }
     return *this; //returns pointer to entry

 }

  michaelVector<int> entry::getPageNumbers(){
      return pageNumbers;
  }

michaelString entry:: getWord() const{ //returns the word of an entry
    return word;
}

bool entry::operator ==(const entry entry2){ //overloaded equality operator
    michaelString word1 = this->getWord(); //gets word of 1 entry
    michaelString word2 = entry2.getWord(); //gets word of other entry
    if(word1.getLength() == word2.getLength()){ //checks to see if they are the same length
        for (int i = 0; i < word1.getLength(); i++){
            if(toupper(word1[i]) == toupper(word2[i])){ //compares letter by letter ignoring case

            } else {
                return false; //if any do not match returns false
            }
        }
        return true; //if length and letters match return true
    }
    return false; //if length does not match return false

}

bool entry ::operator >(const entry& entry2){ //overloaded > operator
    if (this->getWord() > entry2.getWord()){ //calls michaelString > comparision operator
        return true;
    } else {
        return false;
    }
}

char entry :: firstLetter(){ //returns first letter of word
    char c = word[0];
    return c;
}

void entry ::addToNum(int x){

    if(!pageNumbers.Search(x))//confirms page number not already in array
        pageNumbers.add(x); //adds page to pageNumbers
    pageNumbers.sort(0); //sorts michaelVector
}


