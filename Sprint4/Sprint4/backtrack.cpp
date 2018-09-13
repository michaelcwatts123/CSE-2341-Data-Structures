#include "backtrack.h"
#include <fstream>

backTrack::backTrack()
{



}
backTrack::backTrack(LinkedList<LinkedList<City>> &adjList, const char **& argv)
{
    fileParse(argv); //creates flight plans from input2 file
    int flag = 0; //flag to check if a city has been checked our not
    LinkedList<LinkedList<City>> adjCopy = adjList; //copy of adjcent list
    for(int i = 0; i < numOfFlightPlans;i++){ //loop through to create all flights
   while(!path.isEmpty()){ //clears out path Stack
    path.pop();
   }
    City c(flightPlans[i].start); //creates city object at orgin of flight plan

    path.push(c); //adds to stack
    alreadyVisited.clear(); //clears out vector of already visited cities

    alreadyVisited.add(c.getName()); //adds c to vector of already visited cities
    adjList.reset(); //resets adjList current pointer equal to first
    while(adjList.getCurrent().getNext() != nullptr){ //interates through list
        adjList.getCurrent().getData().reset(); //reseting each node's current pointer to first
        adjList.interate(); //interates to next node
    }

while(true){ //infinite loop
if(c.getName() == flightPlans[i].end){ //end condition
    flight a(path); //creates flight from path Stack
    flights.insert(a); //inserts it into list of flights
    path.pop(); //pops destination of stack
    alreadyVisited.pop(); //removes final destination from list of cities visited
    adjList.getCurrent().getData().remove(c); //removed node containing destination from adjList current list
    c = path.peek(); //sets C to last value from stack
}
adjList.reset(); //resets adjList current pointer to first
while(adjList.getCurrent().getNext() != nullptr){ //iterates through entire list
    if(adjList.getCurrent().getData().getFirst().getData().getName() == c.getName()){ //if adjList current list's head pointer equals name of City
        break; //break
    } else {
        adjList.interate(); //else iterate through list
    }
}
do{
    if(adjList.getCurrent().getData().getCurrent().getData().getName() == flightPlans[i].end){ //end condition
        c = adjList.getCurrent().getData().getCurrent().getData(); //assigns c to adjList current list current pointer
        path.push(c); //adds c to path stack

        alreadyVisited.add(c.getName()); //adds name of destination city to alreadyVisted vector
        adjList.getCurrent().getData().interate(); //cycles adjList current's list current pointer to next node
        break; //break out of list
    } else{
    if(!alreadyVisited.Search(adjList.getCurrent().getData().getCurrent().getData().getName())){
    //if current list current city has not been visited
            c = adjList.getCurrent().getData().getCurrent().getData(); //save city to c

            path.push(c); //adds to path Stack
            flag = 1; //set flag = 1
            alreadyVisited.add(c.getName()); //adds name to alreadyVisted vector

            break; //breaks from loop
    } else {
        adjList.getCurrent().getData().interate(); //else iterate to next city in current list
    }
}
}while(adjList.getCurrent().getData().getCurrent().getNext() != nullptr);
if(adjList.getCurrent().getData().getCurrent().getData().getName() == flightPlans[i].end){
    //checks if current list current pointer equal end of path
    c = adjList.getCurrent().getData().getCurrent().getData(); //sets c to value of currenrt list current data
    path.push(c); //adds to path

    alreadyVisited.add(c.getName()); //adds to alreadyVisited list


}
if(flag == 1){ //if flag == 1
    flag = 0; //reset flag and continue to next iteration of loop
    continue;
}
if(adjList.getCurrent().getData().getCurrent().getNext() == nullptr){ //if program reaches end of adjList
    if(!path.isEmpty()){ //if path still contains anything
        if(path.peek() != flightPlans[i].end){ //if last element on path does not equal destination
            path.pop();//pop last element off the stack since it is a dead end
            if(!path.isEmpty()){ //if path is not empty
            c = path.peek(); //set c to top value of stack
            } else {
                break; //else end loop
            }
        } else {
            break; //else end loop
        }
    }
}

}
adjList = adjCopy; //resets adjList
}
    outputer(argv); //outputs list of flights

}
backTrack::~backTrack(){ //destructor
        delete [] flightPlans; //deletes dynamic array
}
backTrack::backTrack(const backTrack &backTrackToCopy){ //copy constructor
    this->flights = backTrackToCopy.flights; //copies flights LinkedList from object to this

    this->flightPlans =backTrackToCopy.flightPlans; //copies flightPlans from object to this
    this->numOfFlightPlans = backTrackToCopy.numOfFlightPlans; //copies numOfFlights to this memember variables
}
backTrack* backTrack::operator =(const backTrack &backTrackToCopy){ //assignment operator
    //copies data from object to member variable
    this->flights = backTrackToCopy.flights;

    this->flightPlans =backTrackToCopy.flightPlans;
    this->numOfFlightPlans = backTrackToCopy.numOfFlightPlans;

    return this; //returns this pointer
}
void backTrack::fileParse(const char **&argv){ //parses file for information
    ifstream parameters(argv[2], ios::in); //creates new ifstream object from input file

    if(!parameters){ //detects if input file is open
        cout << "Critical Error" << endl;
    }
    char c; //holds individual character from input 2 file
    int i = 0;
    parameters.getline(buffer,80); //gets first line from buffer
    numOfFlightPlans = atoi(buffer); //converts buffer to int
    flightPlans = new flightPlan[numOfFlightPlans]; //creates new array of flight plans
    clean(); //cleans buffer
    while(parameters.get(c)){ //loops through entire document character by character
        if(i>=numOfFlightPlans){ //detects if no flightPlans to be made
            break;
        }
        if(c == '|'){ //detects if pipe
        if(c == '|' && orginFlag == 0){ //checks pipe and flag to determine if orgin city name
            buffer[bufferLetterCount] = '\0'; //ensures proper end of string
            orginForPlan = buffer; //sets orginForPlan equal to buffer
            orginFlag = 1; //sets orgin flag to 1
            destinationFlag = 0; //sets destination flag to 0
            clean(); //resets buffer
            continue; //continues to next interation of loop so | character is not saved
        }
        if(c == '|' && destinationFlag == 0){ //checks pipe and flag to determine if destination city name
            buffer[bufferLetterCount] = '\0'; //ensures michaelString is properly capped off
            destinationForPlan = buffer;  //sets destinationForPlan equal to buffer
            clean(); //resets buffer
            continue; //continues to next interation of loop so | character is not saved
        }


       } else {

            if(c == '\n'){ //end of line means automitcally value in buffer is time
                buffer[bufferLetterCount] = '\0'; //ensures buffer is properly capped off
                parameterForSort = buffer; //stores parameterForSort to buffer
                orginFlag = 0; //sets orginFlag to 0
                destinationFlag =1; //sets destination flag to 1
                char time[2];
                time[0] = 'T';
                time[1] = '\0';
                michaelString test1(time);

                if(parameterForSort == test1){ //checks to see if parameterForSort is time
                flightPlans[i].setParameters(orginForPlan,destinationForPlan,1,0); //sets flightPlans member variables
                i++;
                } else { //checks to see if parameterForSort is cost
                    flightPlans[i].setParameters(orginForPlan,destinationForPlan,0,1); //sets flightPlans member variables
                    i++;
                }
                clean(); //ensures all flags properly set
                continue; //continues to next interation of loop so | character is not saved
            } else{
            buffer[bufferLetterCount] = c; //saves c in buffer
            bufferLetterCount++; //increments bufferLetterCount for next letter
            }
        }
     }

    }

void backTrack::clean(){ //resets and empties buffer
    bufferLetterCount = 0;
    for(int i = 0; i < 80;i++){
        buffer[i] = 0;
    }

}
void backTrack::outputer(const char**& argv){
    ofstream outputFile(argv[3], fstream::out); //output object

    if(!outputFile){ //detects if output file is open
        cout << "Critical Error" << endl;
    }
    City c; //city object to hold indivuda values
    int totalCost = 0; //holds totalCost of path
    int totalTime = 0; //holds totalTime of path

   for(int i = 0; i < numOfFlightPlans; i++){ //loops through each flightPlan
        //prints header of flightPlan
       outputFile << "Flight " << i+1 << " " << flightPlans[i].start << " , " << flightPlans[i].end;
       if(flightPlans[i].timeFlag == 1){
           outputFile << " (Time) " << endl;
       } else {
           outputFile << " (Cost) " << endl;
       }

       int count = 0;
   flights.reset(); //resets flights linkedList current to beginging of list
   while(&flights.getCurrent() != &flights.getLast()){ //while current does not equal last of flights
       if(!flights.getCurrent().getData().inOrderFlight.isEmpty()){ //if flights is not empty
   if(flights.getCurrent().getData().inOrderFlight.peek().getName() == flightPlans[i].start){
       //if top of flights current stack equals start of flight plan
   while(!flights.getCurrent().getData().inOrderFlight.isEmpty()){ //loop through entire stack of flights current nodes
   c = flights.getCurrent().getData().inOrderFlight.pop(); //set c to indivudal stack objects
   totalCost+=c.cost; //increments totalCost by c's cost
   totalTime+=c.time; //increments totalTime by c's time
   outputFile << c.getName(); //outputs C name to output file
   if(flights.getCurrent().getData().inOrderFlight.isEmpty()){ //if stack is empty
        outputFile << ". " << "Cost " << totalCost << ".00 Time " << totalTime << endl; //adds information about cost and time
        count++;
        if(count == 3){
            break;
        }

   } else { //else adds arrow between cities
       outputFile << " -> ";
   }
   }
    } else{ //iterates to next flights node
        flights.interate();
   }
       } else { //iterates to next flights node
       flights.interate();
   }
       /*
       if(count == 3){
           continue;
       }
       */
   }

   if(count == 3){
       break;
   }

   if(flights.getLast().getData().inOrderFlight.peek().getName() == flightPlans[i].start){ //checks last element to see if stack is path
   while(!flights.getLast().getData().inOrderFlight.isEmpty()){ //while stack is not equal
   c = flights.getLast().getData().inOrderFlight.pop(); //sets c to individual elements of last of stack
   totalCost+=c.cost; //increments totalCost by c's cost
   totalTime+=c.time; //increments totalTime by c's time
   outputFile << c.getName(); //outputs c's name
   if(flights.getLast().getData().inOrderFlight.isEmpty()){ //if end adds remaining info
        outputFile << ". " << "Cost " << totalCost << ".00 Time " << totalTime << endl;
   } else { //else adds arrow
       outputFile << " -> ";
   }
   }
    }


   }
}
