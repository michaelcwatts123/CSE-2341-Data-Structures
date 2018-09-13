#include "city.h"

City::City(){
     origin = nullptr; //pointer to city's orgin or null if orgin city
    name = " "; //name of city
     time = 0; //time to fly to city
     cost = 0; //cost to fly to city
}

City::City(michaelString placeName) //orgin constructor
{
    name = placeName; //sets name
    origin = nullptr; //puts orgin pointer at null
}
City::City(City  &orginCity, michaelString &placeName, int &costToTravel, int &timeToTravel){ //destination constrictor
    origin = &orginCity; //sets orgin pointer to orgin city
    name = placeName; //sets city name
    cost = costToTravel; //sets cost to fly to
    time = timeToTravel; //sets time to fly to
}

City::~City(){ //destructor

}
 City::City(const City &cityToCopy){
     if(cityToCopy.origin == nullptr){ //checks if cityToCopy is destination
         this->name = cityToCopy.name; //copies name
         this->origin = nullptr; //sets orgin pointer to null to distinguish orgin city
     } else{ //else copies attriubutes
     this->cost = cityToCopy.cost;
     this->name = cityToCopy.name;
     this->origin = cityToCopy.origin;
     this->time = cityToCopy.time;
     }

 }

City* City::operator =(const City &cityToCopy){ //copy constructor
    if(cityToCopy.origin == nullptr){ //checks if cityToCopy is destination
        this->name = cityToCopy.name; //copies name
        this->origin = nullptr; //sets orgin pointer to null to distinguish orgin city
    } else{ //else copies attriubutes
    this->cost = cityToCopy.cost;
    this->name = cityToCopy.name;
    this->origin = cityToCopy.origin;
    this->time = cityToCopy.time;
    }
    return this; //returns pointer to new object

}
michaelString City::getOrginName(){ //returns name of orgin
    return origin->name;
}
michaelString City::getName(){ //returns name of city
    return name;
}

bool City::operator ==(const City& cityToCompare){ //comparison operator
    if((this->origin == nullptr && cityToCompare.origin != nullptr) || (this->origin != nullptr && cityToCompare.origin == nullptr) ){ //checks if comparing a destination city to orgin city
        return false;
    }
    if(this->origin == nullptr && cityToCompare.origin == nullptr){ //compares two orgin cities
        if(this->name == cityToCompare.name){ //if name is same
            return true; //returns true
        } else {
            return false;
        }
    }
    else {
        if(this->origin == cityToCompare.origin && this->name == cityToCompare.name && this->cost == cityToCompare.cost && this->time == cityToCompare.time) //compares all atributes of destination cities
            return true; //retrns true if sa,e
        else{ //else false
            return false;
        }
    }
}
bool City::operator !=(const City& cityToCompare){ //comparison operator
    return !(*this == cityToCompare); //negates == result
}

City * City::getOrgin(){ //returns orgin
    return origin;
}



