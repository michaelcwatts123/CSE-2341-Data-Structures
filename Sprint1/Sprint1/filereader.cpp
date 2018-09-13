#include "filereader.h"
#include "dictionary.h"
#include "spellchecker.h"
#include <fstream>

using namespace std;

FileReader::FileReader(const char **&argv)
{

ifstream dictionaryFile(argv[1], ios::in); //reads in dictionary
ifstream fileToParse(argv[2], ios::in); //reads in manuscript
ofstream outputFile(argv[3], ios::out);
char m = ' ';
while(outputFile.eof()){ //clears out previous contents of output file
    outputFile << c;
}
outputFile.close();
if(!dictionaryFile || !fileToParse){ //confirms that files have been opened
        cout<< "Critical Error!"<< endl;
        exit(0);
    }


while (dictionaryFile.get(c)){ //reads in dictionary character by character

    if (lineCounter == 1 && letterCounter == 0){ //determines if first line of dictionary

    int dictionaryLength = atoi(buffer); //converts buffer holding characters into int

    d.setLength(dictionaryLength); //sets the length of the dictionary according to the first line
   }

    if (c != '\n') { //detects individual words

         buffer[letterCounter] = c; //stores letters into buffer to turn into michaelString
        letterCounter++; //ensures that the character does not write over preexisting character

    } else {

        buffer[letterCounter] = '\0'; //detects end of word
        letterCounter = 0; //resets letter counter

        if (lineCounter > 0 ){ //confirms word is not just blank space

            d.add(buffer); //adds word to dictionary
            for (int i = 0; i < 30; i++){ //clears out buffer to ensure no extra characters are added to words
                buffer[i] = ' ';
            }
        }
        lineCounter++; //moves line counter forward


    }



}
lineCounter = 0; //resets line counter for manuscript
letterCounter = 0; //resets letter counter for manuscript
while(!fileToParse.eof()){ //opens manuscript txt file, loops until end of file marker is hit
fileToParse.get(c); //stores individual characts in char c


    if (c == '\0' || c == '\n'|| c=='\t' || c == ' ' || c == '.' || c == ','|| c == '!'|| c == '?'|| c == ';'|| c == ':'|| c == '\"'|| c == '('|| c == ')'|| c == '['|| c == ']'|| c == '{'|| c == '}'){ //various signs that a new word or line is started
        if (buffer[0] != ' ' || buffer[0] != '\n' || buffer[0] != ' '){ //indicates new word
            buffer[letterCounter] = '\0'; //adds a null terminator to end of buffer
            spellChecker check(buffer, d, wordCounter, lineCounter, argv); //sends indivual word in buffer to spell check witht the words information


            letterCounter = 0; //resets the letter counter
            wordCounter++; //increments the word count
        }

    } else {
        if(c == ' '){ // check to ensure c is not an empty character

        } else {
        if(isalpha(c)){ //double check c is character data
            if(isspace(c)){ //third confirmation c is character data

            } else {
            buffer[letterCounter]= c; //adds letter to buffer
            letterCounter++; //increases letter count
            }
        }
        }


    }
    if (c == '\n'){ //detects new lines
        lineCounter++; //increases line count
        wordCounter = 1; //resets word count for line
    }

}
dictionaryFile.close(); //closes dictionary file
fileToParse.close(); //closes manuscript




}

