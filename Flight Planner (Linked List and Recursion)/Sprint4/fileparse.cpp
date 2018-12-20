#include "fileparse.h"
#include "city.h"
#include <../../lib/stack.h>
#include <fstream>
#include <iostream>
#include <../../lib/michaelString.h>
#include <../../lib/michaelvectors.h>
using namespace std;
fileparse::fileparse(){
    cost = 0;
    time = 0;
}

fileparse::fileparse(const char **&argv)
{
    ifstream inputFile(argv[1], ios::in); //creates new ifstream object from input file

    if(!inputFile){ //detects if input file is open
        cout << "Critical Error" << endl;
    }
    ofstream outputFile(argv[3], fstream::out); //creates new ifstream object from input file


    while(outputFile.eof()){ //cleans out output file of text

        outputFile << ' ';
    }

    inputFile.getline(buffer,35); //gets first line of input
    numberOfLines = atoi(buffer); //converts to int and stores it

    while(inputFile.get(c)){ //loops through entire document

        if(c == '|'){ //detects if pipe
        if(c == '|' && cityFlag == 0){ //checks pipe and flag to determine if orgin city name
            buffer[bufferLetterCount] = '\0'; //ensures proper end of string
            orginName = buffer; //saves buffer in orginName
            destinationFlag = 0;//sets the next flag
            cityFlag = 1; //disables previous flag
            cleanBuffer(buffer); //cleans buffer

            City c(orginName); //creates new orgin city object with orginName
            Orgin = c; //assigns its value to attribute Orgin

            continue; //continues to next interation of loop so | character is not saved
        }
        if(c == '|' && destinationFlag == 0){ //checks pipe and flag to determine if destination city name
            buffer[bufferLetterCount] = '\0'; //ensures michaelString is properly capped off
            destinationName = buffer; //saves buffer as destinationName
            costFlag = 0; //enables next flag
            destinationFlag = 1; //disables current flag
            cleanBuffer(buffer); //cleans buffer

            continue; //continues to next interation of loop so | character is not saved
        }
        if(c == '|' && costFlag == 0){ //checks pipe and flag to determine if cost

            cost = atoi(buffer); //converts buffer to string and saves value
            timeFlag = 0; //disables current flag
            costFlag = 1;  //enables next flag
            cleanBuffer(buffer); //cleans uffer
            continue; //continues to next interation of loop so | character is not saved
        }

       } else {
            if(c == '\n'){ //end of line means automitcally value in buffer is time
                time = atoi(buffer); //converts buffer to int
                cityFlag = 0; //disables current flag
                timeFlag = 1; //enables next flag
                cleanBuffer(buffer); //cleans buffer
                constructAdjList();


                clean(); //ensures all flags properly set
                continue; //continues to next interation of loop so | character is not saved
            } else{
            buffer[bufferLetterCount] = c; //saves c in buffer
            bufferLetterCount++; //increments bufferLetterCount for next letter
            }
        }
     }
    backTrack trace(adjCity,argv);

}
void fileparse::cleanBuffer(char * bufferToClean){ //clears out contents of the buffer and resets count
    for(int i = 0;i<35;i++){
        bufferToClean[i] = ' ';
    }
    bufferLetterCount = 0;
}
void fileparse::clean(){ //resets all flags to default postion

     cityFlag = 0;
     destinationFlag = 1;
     costFlag = 1;
     timeFlag = 1;
     bufferLetterCount = 0;
     cleanBuffer(buffer);
     orginName = "";
     destinationName = "";
     cost = 0;
     time = 0;
}
void fileparse::constructAdjList(){ //constructs Adjacent List
    City destinationOfOrgin(Orgin,destinationName,cost,time); //creates destination City
    City destinationAsOrgin(destinationName); //uses destination as orgin since flights are two way
    City orginAsDestination(destinationAsOrgin,orginName,cost,time); //uses orgin as destination since flights are two way


    if(!OrginCityNames.Search(orginName) && !orginName.empty()){ //if this city has not already been used as an orgin

        OrginCityNames.add(orginName); //adds orginName to Vector of orgin names
        LinkedList<City> a; //creates new linkedList
        a.insert(Orgin); //sets orgin as head
        adjCity.insert(a); //adds to adjacent list
    }
    if(!OrginCityNames.Search(destinationName) && !destinationName.empty()){ //if this city has not already been used as an orgin

        OrginCityNames.add(destinationName); //adds destinationName to Vector of orgin names
        LinkedList<City> a;  //creates new linkedList
        a.insert(destinationAsOrgin); //sets destination as head
        adjCity.insert(a); //adds to adjacent list
    }
    adjCity.reset(); //sets current pointer of adjCity to first pointer
    while(!(adjCity.getCurrent().getData().getFirst().getData().getName() == adjCity.getLast().getData().getFirst().getData().getName())){
        //cycles through entire adjList till right before last pointer
        if(adjCity.getCurrent().getData().getFirst().getData().getName() == destinationOfOrgin.getOrgin()->getName()){
            //if destinationOfOrgin's orgin object equals head of list
            adjCity.getCurrent().getData().insert(destinationOfOrgin); //add destinationOfOrgin to list

        }
            if(adjCity.getCurrent().getData().getFirst().getData().getName() == orginAsDestination.getOrgin()->getName()){
                //if orginAsDestination's orgin object equals head of list
                adjCity.getCurrent().getData().insert(orginAsDestination); //add orginAsDestination to list

            }
                adjCity.interate(); //cyles current pointer to next head of list




}

        if(adjCity.getLast().getData().getFirst().getData().getName() == destinationOfOrgin.getOrgin()->getName()){
            //if destinationOfOrgin's orgin object equals head of list at last position of list
            adjCity.getLast().getData().insert(destinationOfOrgin); //inserts this city object into list
        }

            if(adjCity.getLast().getData().getFirst().getData().getName() == orginAsDestination.getOrgin()->getName()){
                //if orginAsDestination's orgin object equals head of list at last position of list
                adjCity.getLast().getData().insert(orginAsDestination); //inserts this city object into list

            }

}
