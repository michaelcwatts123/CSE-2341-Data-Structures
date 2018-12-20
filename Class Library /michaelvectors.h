#ifndef MICHAELVECTORS_H
#define MICHAELVECTORS_H
#include <iostream>
using namespace std;


template <typename T>
class michaelVector{
private:
    T* holding = new T[0]; //array to hold T values
    int length = 0; //int to track array length
public:
    michaelVector(){} //default constructor
    michaelVector(const michaelVector &michaelVectorToCopy){//copy constructor
        this->length = michaelVectorToCopy.length; //sets lengths of michaelVectors equal
        delete [] holding; //deletes old michaelVector
        holding = new T[length]; //reassigns it with new length
        for (int i = 0; i < length; i++){
            holding[i] = michaelVectorToCopy.holding[i]; //fills newly created michaelVector with copied over values
        }

    }

    ~michaelVector(){ //destructor

        delete [] holding;
    }
    michaelVector& operator =(const michaelVector& ); //assignment operator

    int getLength() const; //returns length of holding array

    T pop(); //returns final element from vector and removes element from array
    T& operator [] (int) const; //overloaded [] operator

    bool Search(T const&); //searches array to see if value is inside of it

    void add(T const& item); //adds value to end of array
    void print(); //prints out contents of array
    void sort(int); //preforms binary sort of array
    void clear();

};

template <typename S>
 ostream& operator <<(ostream& os, const michaelVector<S>& michaelV){ //overloaded << operator to print out array
    for(int i = 0; i < michaelV.getLength(); i++){
        os << michaelV[i] << " ";
    }
    return os;
}

 template <typename T>
 michaelVector<T>& michaelVector<T> :: operator =(const michaelVector<T>& michaelVectorToCopy){ //assignment operator
    if (this == &michaelVectorToCopy){ //checks to see if michaelVector has been assigned to itself
        return *this;
    } else {
     delete [] holding; //deletes old values in michaelVector
    this->length = michaelVectorToCopy.length; //changes michaelVector's length
    holding = new T[length];
    for (int i = 0; i < length; i++){
        holding[i] = michaelVectorToCopy.holding[i]; //fills michaelVector with new values
    }
    return *this; //returns pointer to new michaelVector
    }
 }

 template <typename T>
 int michaelVector<T> ::getLength() const{ //returns length of michaelVector
     return length;
 }
template <typename T>
 void michaelVector<T>::clear(){
    michaelVector<T> empty;
    *this = empty;
 }

 template <typename T>
 T michaelVector<T> :: pop(){ //returns end value of michaelVector and removes it
     T* resizedArray = new T[length-1]; //creates new properly sized array for michaelVector
     for(int i = 0; i < length-1; i++){ //copies over all but last value
         resizedArray[i] = holding[i];
     }
     T value = holding[length-1]; //saves last value
     delete [] holding; //deletes old array
     length--;
     //holding = new T[length]; //creates new array
     holding = resizedArray; //assigns pointer to point to new array
     return value; //returns final value of old array
 }

template <typename T>
T &michaelVector<T>::operator [](int value) const{ //overloaded [] operator
    if(value > length){ //checks to see if value is within bounds of the array
        value = length;
    }
    if(value < 0)//checks to see if value is within bounds of the array
        value = 0;

    return holding[value]; //retunrs value
}

template <typename T>
bool michaelVector<T>:: Search(T const& item){ //searches through content of array
    for(int i = 0; i < length; i++){
        if(holding[i] == item){ //compares item to each item in array
            return true; //if found returns true
        }
    }
        return false;

}

template <typename T>
void michaelVector<T>:: print(){ //prints contents of array
    for(int i = 0; i < length; i++){
        cout << holding[i] << endl; //cycles through array printing out content
    }


}

template <typename T>
void michaelVector<T>:: add(T const& item){ //adds item to array
    T* resizedArray = new T[(length+1)]; //creates a new array of length + 1
    for(int i = 0; i < length; i++){

        resizedArray[i] = holding[i]; //copies values from old array into new array
    }

    resizedArray[length] = item; //assigns item to final value of array

    delete [] holding; //deletes old array
    length++; //increments length

    holding = resizedArray; //sets holding pointer to point to new array



}

template <typename T>
void michaelVector<T>:: sort(int counter){ //binary sort of array
    if(counter != length){ //guard statment to detect end of sort
    for(int i = 0 + counter; i < length; i++){ //cycles through array each time incrementing the starting point
        if(holding[counter] > holding[i]){ //detects if value at counter is greater than any other value in array
            swap(holding[counter], holding[i]); //if so swaps it to put array in ascending order
        }
    }
    sort(counter+1); //recursive call to repeat this function until end of array
    }


}


#endif // MICHAELVECTORS_H
