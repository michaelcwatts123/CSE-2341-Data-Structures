#ifndef CITY_H
#define CITY_H
#include <../../lib/michaelString.h>

class City
{
public:
    City * origin; //pointer to city's orgin or null if orgin city
    michaelString name; //name of city
    int time = 0; //time to fly to city
    int cost = 0; //cost to fly to city

    City(); //default constructor
    City(michaelString); //orgin city constructor
    ~City(); //destructor
    City(const City &); //copy constructor
    City(City &, michaelString &, int &, int&); //destination city constructor

    City* operator =(const City&); //copy constructor
    bool operator ==(const City&); //comparison operator
    bool operator !=(const City&); //comparison operator
    City* getOrgin(); //returns orgin of city
    michaelString getOrginName(); //returns orgin of city as string
    michaelString getName(); //returns name of city




    };



#endif // CITY_H
