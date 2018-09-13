#include "flightplan.h"

flightPlan::flightPlan() //default constructor initializes member variables
{
    start = "Dummy";
    end = "Dummy";
    timeFlag = 0;
    costFlag = 1;

}
flightPlan::flightPlan(michaelString sPoint, michaelString ePoint, int time, int cost){ //sets member values to values passed into constructor
    start = sPoint;
    end = ePoint;
    timeFlag = time;
    costFlag = cost;
}
void flightPlan::setParameters(michaelString sPoint, michaelString ePoint, int time, int cost){ //sets member values to values passed into constructor
    start = sPoint;

    start = sPoint;
    end = ePoint;
    timeFlag = time;
    costFlag = cost;
}

flightPlan::~flightPlan(){ //default destructor

}
flightPlan::flightPlan(const flightPlan &flightPlanToCopy){ //copy constructor copies over member variables from one object to another
    this->start = flightPlanToCopy.start;
    this->end = flightPlanToCopy.end;
    this->costFlag = flightPlanToCopy.costFlag;
    this->timeFlag = flightPlanToCopy.timeFlag;
}
flightPlan* flightPlan::operator =(const flightPlan& flightPlanToCopy){ //assignment operator copies memeber varaibles from object and returns this pointer
    this->start = flightPlanToCopy.start;
    this->end = flightPlanToCopy.end;
    this->costFlag = flightPlanToCopy.costFlag;
    this->timeFlag = flightPlanToCopy.timeFlag;
    return this;
}
