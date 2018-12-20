#include "flight.h"

flight::flight() //default constructor sets member varaibles to inital values
{
     totalCost = 0;
     totalTime = 0;
}
flight::~flight(){ //default destructor

}
flight::flight(const flight &flightToCopy){ //copy constructor copies over member variables from object to this
    this->inOrderFlight = flightToCopy.inOrderFlight;
    this->totalCost = flightToCopy.totalCost;
    this->totalTime = flightToCopy.totalTime;
}
flight* flight::operator =(const flight &flightToCopy){ //assignment copies over member variables from object to this and returns this
    this->inOrderFlight = flightToCopy.inOrderFlight;
    this->totalCost = flightToCopy.totalCost;
    this->totalTime = flightToCopy.totalTime;
    return this;
}
flight::flight(Stack<City> cities){ //overloaded constructor
    while(!cities.isEmpty()){ //while stack is not empty
    City a; //temp city object to store values
    a = cities.pop(); //pop city stack to a
    totalCost += a.cost; //increment totalCost by city Cost
    totalTime += a.time; //increment totalTime by city Time
    inOrderFlight.push(a); //pushes a to member variables stack
    }

}
int flight::getTime(){ //caculates totalTime as double check of time
Stack<City> copy; //temporary stack to hold temporary cities
City c; //temporary city to hold individual values
totalTime = 0; //resets total time
while(!inOrderFlight.isEmpty()){ //cycles through entire stack
    c = inOrderFlight.pop(); //c stores inOrderFlight's individual items
    totalTime += c.time; //adds c's time to total time
    copy.push(c); //adds c to copy Stack
}
inOrderFlight = copy; //copies over stack to member variable
return totalTime; //returns totalTime
}
int flight::getCost(){ //caculates totalTime as double check of cost
Stack<City> copy; //temporary stack to hold temporary cities
City c; //temporary city to hold individual values
totalCost = 0;  //resets total time
while(!inOrderFlight.isEmpty()){ //cycles through entire stack
    c = inOrderFlight.pop(); //c stores inOrderFlight's individual items
    totalCost += c.cost; //adds c's cost to total cost
    copy.push(c); //adds c to copy stack
}
inOrderFlight = copy; //copies over stack to member variable
return totalCost; //returns totalCost
}
flight * flight::reverseOrder(){ //reverses order of stack
    Stack<City> copy; //temp stack to hold values
    City c; //temp city object to hold individual values

    while(!inOrderFlight.isEmpty()){ //cycles through entire stack
        c = inOrderFlight.pop(); //c stores single values from inOrderFlight stack

        copy.push(c); //pushes c to copy
    }
    inOrderFlight = copy; //copies copy to inOrderFlight
    return this; //returns this pointer
}
bool flight::operator ==(flight flightToCopare){ //comparison operator
    if(this->inOrderFlight == flightToCopare.inOrderFlight){ //calls stack comparison
        return true; //returns true if true
    } else {
        return false; //else false
    }
}
bool flight::operator !=(flight flightToCopare){ //comaprison operatpr
   return !(*this == flightToCopare); //negates == result
}
