#include "fileparse.h"
#include <../../lib/michaelvectors.h>
#include <../../lib/michaelString.h>
#include <fileoutput.h>
#include <fstream>
fileParse::fileParse(const char **& argv)
{

    ifstream inputFile(argv[1], ios::in); //creates new ifstream object from input file

    if(!inputFile){ //detects if input file is open
        cout << "Critical Error" << endl;
    }

    while(inputFile.get(c)){ //reads in input file letter by letter

        if(c == '.' || c == ',' || c == '?' || c == '!'){
            continue;
        }
        if(c == '<' || c == '>' || c == '[' || c == ']'){ //detects start of phrase

            phraseFlag =1 ;
        }
        if (phraseFlag == 1){

             phraseLogic(); //calls logic to handle parsing phrases
        }

         else {

            if ( (c == '\n' && bufferCounter > 0) ||  (c == ' ' && bufferCounter > 0)){ //detects end of word
                    bufferCounter++;
                    buffer[bufferCounter] = '\0'; //adds null terminator to end of word
                    word = buffer; //assigns buffer to word

                   for(int i = 0; i < 80; i++){ //empty the buffer
                       buffer[i] = ' ';
                   }
                   bufferCounter = 0; //reset the buffer counter
                   addToEnteries(); //adds word to enteries michaelVector
            } else {

                buffer[bufferCounter] = c; //adds letter to buffer
                bufferCounter++; //increments buffer counter


            }

        }


    }
    enteries.sort(0); //calls the sort function begining at item 0 of enteries michaelVector
    //cout << enteries << endl;
    fileOutput output(argv,enteries); //object to output the enteries michaelVector


}
void fileParse::addToEnteries(){

    if(pageNum > 0){ //ensures a valid pagenumber

       entry toBeIndexed(pageNum, word); //creates new entry from word and pageNum

    if(!enteries.Search(toBeIndexed)){ //searches array to see if word is already cataloged
    enteries.add(toBeIndexed); //adds new entry to michaelVector of enteries
    } else {

        for(int i = 0; i < enteries.getLength(); i++){ //loops through all enteries

            if( word.ignoreCaseCompare( enteries[i].getWord())){ //compares new entry to all exisiting enteries

                enteries[i].addToNum(pageNum); //if already cataloged adds new page number to pageNumber michael vector of entry

            }
        }
    }
    }
}
void fileParse::phraseLogic(){

    if(pageFlag == 1){
        buffer[bufferCounter] = c; //fill buffer array with letters from file
        bufferCounter++; //increment the buffer counter to keep letter count
    }
    if(pageFlag == 2){
        buffer[bufferCounter+1] = '\0'; //add a null terminator to end of buffer
        pageNum = atoi(buffer); //conver buffer to int


        pageFlag = 0; //reset the page flag
        for(int i = 0; i < 80; i++){ //empty the buffer
            buffer[i] = ' ';
        }
        bufferCounter = 0; //reset the buffer counter
        phraseFlag = 0; //resets phrase flag
    }
    if(wordFlag == 1){

        if (c == ']'){} //if ] bracket from end of word throw it away
        else{
        buffer[bufferCounter] = c; //otherwise add it to the buffer
        bufferCounter++; //increment buffer counter
        }

    }
    if(wordFlag ==2){
        buffer[bufferCounter] = '\0'; //add null termintor to end of buffer
        word = buffer; //michaelString assignemnt operator
        wordFlag = 0; //reset word flag
        for(int i = 0; i < 80; i++){ //loop to empty buffer
            buffer[i] = ' ';
        }
        bufferCounter = 0; //reset buffer counter
        addToEnteries(); //adds word and pageNumber to enteries vector
         phraseFlag = 0; //resets phrase flag
    }

    if (c == '<'){ //if < is detected marking the begining of a page number
        pageFlag = 1; //sets the page number flag to 1

    }
    if (c == '>'){ //if > detected marking the end of a page number
        pageFlag = 2; //sets page number flag to 0

    }
    if (c == '[') //if a [ is detected marking the begining of a word
        wordFlag = 1; //sets word flag to 1
    if (c == ']'){ //if a ] is detected marking the end of a word
        wordFlag = 2; //sets word flag to 2

    }
}

