#include "customsort.h"

customSort::customSort(michaelVector<michaelString> &toBeSorted)
{
    sort(toBeSorted,0);
}
void customSort::sort(michaelVector<michaelString> &toBeSorted, int counter){ //selection sort

    if(counter != toBeSorted.getLength()){ //guard statment to detect end of sort
    for(int i = 0 + counter; i < toBeSorted.getLength(); i++){ //cycles through array each time incrementing the starting point
        if( toBeSorted[counter].getLength() >  toBeSorted[i].getLength()){ //detects if value at counter is greater than any other value in array
            swap( toBeSorted[counter],  toBeSorted[i]); //if so swaps it to put array in ascending order
        }
        if (toBeSorted[counter].getLength() ==  toBeSorted[i].getLength()){ //check if words have the same length
            if(toBeSorted[counter] >  toBeSorted[i]){ //compares words of the same size

                swap( toBeSorted[counter],  toBeSorted[i]); //swaps words if needed
            }
        }
    }
    sort(toBeSorted, counter+1); //recursive call to repeat this function until end of array
    }
}

