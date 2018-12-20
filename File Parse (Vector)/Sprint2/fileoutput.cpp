#include "fileoutput.h"
#include <../../lib/michaelvectors.h>

#include <fstream>
fileOutput::fileOutput(const char **& argv, michaelVector<entry>& enteries)
{
    clearFile(argv); //clears out previous file contents
    ofstream outputFile(argv[2], fstream::app); //creates new fstream object from output file
    if(!outputFile){ //detects if out file is open
        cout << "Critical Error" << endl;
    }

    char c = enteries[0].firstLetter(); //gets first letter of first entery in array
    char d = toupper(c); //capitalizes it
    outputFile << '[' << d << ']' << endl;

    for (int i = 0; i < enteries.getLength(); i ++){
        if (c != enteries[i].firstLetter()){ //checks to see if output file needs new letter headed

             c = enteries[i].firstLetter();
             d = toupper(c);
            outputFile << '[' << d << ']' << endl;
        }

        outputFile << enteries[i].getWord() << " : " << enteries[i].getPageNumbers() << endl; //prints contents of entry michaelVector
    }

}
void fileOutput::clearFile(const char **& argv){
    ofstream outputFile(argv[2], ios::out);
    if(!outputFile){ //detects if output file is open
        cout << "Critical Error" << endl;
    }
    while(outputFile.eof()){ //clears out previous contents of output file
        outputFile << ' ';
    }
    outputFile.close(); //closes file
}
