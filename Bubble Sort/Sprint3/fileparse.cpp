#include "fileparse.h"
#include "customsort.h"
#include <fstream>

FileParse::FileParse(const char **&argv)
{
    ifstream fileToSort(argv[1], ios::in); //file to read in
    ofstream outputFile(argv[2], ios::out); //file for output
    if(!fileToSort){ //checks if file is open
        cout << "Critical Error" << endl;
    }
    while(!fileToSort.eof()){ //loops through file till end

        if(firstWordflag == 0){ //detemines if first word of document
        fileToSort.getline(buffer,35); //stores first word in buffer

        numWords = atoi(buffer); //converts word to number of words in document
        firstWordflag = 1; //sets first word flag to 1

        }
        if(secondWordFlag == 0){ //determines if second word of document
        fileToSort.getline(buffer,35); //stores second word in buffer

        numWordsToSort = atoi(buffer); //converts word to number of words to be sorted
        secondWordFlag = 1; //sets second word flag

        }

        fileToSort.getline(buffer, 35); //gets next word and stores it in buffer
        michaelString word(buffer); //converts buffer into michaelString
        if(!word.empty()){ //check to ensure word is not blank


            listToBeSorted.add(word); //adds michaelString to michaelVector
        }
    }

    customSort x(listToBeSorted); //calls sort on list



    for(int i = 0; i < numWordsToSort; i++){ //outputs michaelVector to file
        outputFile << listToBeSorted[i] << endl;
    }

}
