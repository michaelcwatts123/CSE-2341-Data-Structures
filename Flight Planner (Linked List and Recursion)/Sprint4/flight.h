#include <../../lib/stack.h>
#include "city.h"
#ifndef FLIGHT_H
#define FLIGHT_H


class flight
{
private:
    int totalCost; //holds total cost of flight
    int totalTime; //holds total time of flight

public:

    flight(); //default construcotr
    flight(Stack<City>); //constructor
    flight(const flight&); //copy constructor
    flight* operator =(const flight&); //assignment operator
    ~flight(); //destructor
    int getCost(); //returns totalCost of flight
    int getTime(); //returns totalTime of flight
    flight * reverseOrder(); //reverses order of flight stack

    bool operator ==(flight); //comparison operator
    bool operator !=(flight ); //comparison operator

     Stack<City> inOrderFlight; //stack holding the flight in proper order

};

#endif // FLIGHT_H
