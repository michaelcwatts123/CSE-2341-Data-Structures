#include <../../lib/michaelString.h>
#include <../../lib/michaelvectors.h>
#ifndef CUSTOMSORT_H
#define CUSTOMSORT_H


class customSort
{
public:
    customSort(michaelVector<michaelString> &toBeSorted); //sorting object
    void sort(michaelVector<michaelString> &, int); //method that sorts the filled michaelVector with a selection sort

};

#endif // CUSTOMSORT_H
