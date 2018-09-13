#include <../../lib/michaelString.h>
#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H


class flightPlan
{
public:
    michaelString start = "Dummy"; //string holding starting orgin
    michaelString end = "Dummy"; //string holding final destination
    int timeFlag = 0; //flag set if path is to be organized by time
    int costFlag = 0; //flag set if path is to be organized by cost

    flightPlan(); //default constructor
    flightPlan(michaelString,michaelString,int,int); //constructor
    void setParameters(michaelString,michaelString,int,int); //method to set all memeber variables
    flightPlan(const flightPlan&); //copy constructor
    flightPlan* operator =(const flightPlan&); //assignment operator
    ~flightPlan(); //destructor
};

#endif // FLIGHTPLAN_H
