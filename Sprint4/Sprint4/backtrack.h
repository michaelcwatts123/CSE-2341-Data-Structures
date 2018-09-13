#include <../../lib/linkedlist.h>
#include <../../lib/michaelvectors.h>
#include "city.h"
#include "flight.h"
#include "flightplan.h"
#include "backtrace.h"

#ifndef BACKTRACK_H
#define BACKTRACK_H


class backTrack
{
private:
    LinkedList<flight> flights; //list of flights
    flightPlan * flightPlans = nullptr; //array of requested flight plans
    Stack<City> path; //stack holding singular path of flight
    michaelVector<michaelString> alreadyVisited; //vector holding name of already visited cities
    char buffer[80] = {' '}; //buffer holding input
    int numOfFlightPlans = 0; //number of flight plans reuqested by file
    int orginFlag = 0; //parsing flag for detecting orgin
    int destinationFlag = 1; //parsing flag for detecting destination
    int bufferLetterCount = 0; //letter counter for buffer
    michaelString orginForPlan; //string holding name of orgin
    michaelString destinationForPlan; //string holding name of destination
    michaelString parameterForSort; //string holding name of sorting parameter
    void outputer(const char **&argv);

public:
    backTrack(); //default constructor
    backTrack(LinkedList<LinkedList<City> > &, const char **&); //constructor
    backTrack(const backTrack&); //copy constructor
    backTrack* operator =(const backTrack&); //assignment operator
    ~backTrack(); //destructor
    void fileParse(const char **&); //method to parse second input file
    void clean(); //method to empty buffer
};

#endif // BACKTRACK_H
