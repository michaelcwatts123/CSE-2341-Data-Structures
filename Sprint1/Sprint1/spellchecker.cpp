#include "spellchecker.h"
#include "dictionary.h"
#include "michaelString.h"
#include "fileoutput.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

spellChecker::spellChecker(const char * buffer, Dictionary d, int wordCount, int lineCount,const char **&argv)
{
    michaelString word(buffer); //creates michaelString from cString buffer
    michaelString wordToCompare(buffer); //creates copy of word
    wordToCompare.upper(); //convers word copy to all upper case for comparision
     michaelString wordsWordsWords [3] = {"a","b", "c"};  //stores word suggestions

        if (d.compare(wordToCompare)){ //if valid spelling, calls compare function

        } else {
            if(word.empty()){ //ensures word has at least one valid character
            } else {

                suggestion(wordToCompare,d,wordsWordsWords); //calls suggestion method
                fileOutput out(word,wordCount,lineCount,wordsWordsWords, argv); //sends word to output


            }

        }


}
void spellChecker :: suggestion(michaelString word, Dictionary d,  michaelString *suggestions){ //reccomends words
    int counter = 0;
    for (int i = 0; i < d.getLength(); i++){
        if((word[0] == d.getWord(i)[0]) && (word[1] == d.getWord(i)[1]) && (word[2] == d.getWord(i)[2])){ //reccomends words if they have the same first 3 characters
            if (counter < 3){ //if there are less than 3 suggestions already
                suggestions[counter] = d.getWord(i); //stores word
                counter++; //increases suggestion counter
            }
        } else {
            if((word[0] == d.getWord(i)[0]) && (word[1] == d.getWord(i)[1])){ //reccomends words if they have the same first 2 characters
                if (counter < 3){
                if (counter < 3){
                    suggestions[counter] = d.getWord(i); //reccomends words if they have the same first character
                    if (counter < 3){
                    counter++;
                }
        } else {
                if((word[0] == d.getWord(i)[0])){
                    if (counter < 3){
                        suggestions[counter] = d.getWord(i);
                        counter++;
                    }
            }
    }

}
    }
        }
srand( time( NULL ) );
    if (counter == 0){ //if no suggestions found
        //finds 3 random words to suggest
        suggestions[0] = d.getWord(randFill(d));
        suggestions[1] = d.getWord(randFill(d));
        suggestions[2] = d.getWord(randFill(d));
    }

    if (counter == 1){ //if 1 suggestion found
        //finds two random words to suggest
        suggestions[1] = d.getWord(randFill(d));
        suggestions[2] = d.getWord(randFill(d));
    }
    if (counter == 2){ //if two suggestions found
        //finds one random word to suggest
        suggestions[2] = d.getWord(randFill(d));
    }


}
}

int spellChecker :: randFill(Dictionary d){ //generates a random number
    int num;

    for (int i = 0; i < 3; i++) {
         num = (rand() % d.getLength()) + 0;

      }

        return num;
    }


