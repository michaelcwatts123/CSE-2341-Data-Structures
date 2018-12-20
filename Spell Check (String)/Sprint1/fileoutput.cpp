#include "fileoutput.h"

fileOutput::fileOutput(michaelString word,int wordCount,int lineCount, michaelString * suggestions,  const char **&argv)
{
ofstream  outPut(argv[3], fstream::app); //opens output file
if(!outPut){ //confirms file is open
    cout << "Error!" << endl;
} else {
outPut <<  '\n' << word << " [" << wordCount << " , " << (lineCount+1) << " ]" << endl; //prints misspelled word with infomation

outPut << "Did you mean: " << *suggestions << " or "<< *(suggestions + 1) << " or " << *(suggestions + 2) << " ?" << endl; //prints suggested words
}

}
