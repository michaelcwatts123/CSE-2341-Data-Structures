#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <type_traits>

#include "indexinterface.hpp"
#include "indexedterm.h"

/**
 * Implements an unordered indexing structue as a hash table.
 *
 * Owner: Carter
 */

template <class T>
class HashTable : public IndexInterface<T>
{
private:
    std::vector<std::set<T>> table;   //vector of sets of data
    int numElements;                  //number of elements

    void resize();
    bool checkResize() const;
    int hashObject(const std::string &, int) const;
    int hashObject(const IndexedTerm &, int) const;
    void insertValue(const IndexedTerm &, std::set<IndexedTerm>::iterator);
    void insertValue(const std::string &, std::set<IndexedTerm>::iterator &) {}

public:
    HashTable(int = 1000000);
    HashTable(const HashTable<T>&);
    HashTable<T>& operator =(const HashTable<T>&);
    bool contains(const T &) const;
    std::pair<T, bool> search(const T &);
    void insert(const T &);
    bool isEmpty() const;
    void makeEmpty();
    std::pair<T, bool> stringSearch(const std::string &);
    void stringInsert(const std::string &, int, int, int);
    std::ostream& print(std::ostream &os) const;
    int getNumElements() const;
    std::pair<T,bool> operator[](const T &);
    std::vector<T> getTopFifty();
    int getTerms() const;
    template <class U>
    friend std::ostream& operator <<(std::ostream&, const HashTable<U> &);
};


//============
//CONSTRUCTORS
//============

/**
 * Default constructor initializes array
 */
template <class T>
HashTable<T>::HashTable(int size) {
    //set vector to an obscenely large size so we never have to resize
    table = std::vector<std::set<T>>(size);

    //set element count to 0
    numElements = 0;
}


/**
 * Copy constructor copies over elements of vector
 */
template <class T>
HashTable<T>::HashTable(const HashTable<T> & rhs) {
    //set vector to size of other table's vector to avoid resize
    //copy over the vector
}


/**
 * Assignment operator copies over data if given argument is not identical
 */
template <class T>
HashTable<T>& HashTable<T>::operator =(const HashTable<T> & rhs) {
    //if not same address, use copy c'tor logic
}


//================
//INDEX INTERFACES
//================


/**
 * Determines whether or not the table contains the given argument
 */
template <class T>
bool HashTable<T>::contains(const T & toBeFound) const {
    //hash the new object, search for object in relevant set
    int hashValue = hashObject(toBeFound, table.size());

    auto result = std::find(table[hashValue].begin(), table[hashValue].end(), toBeFound);

    return result != table[hashValue].end();
}


/**
 * Returns pair with the sought object and a boolean flag indicating
 * whether or not it was found
 */
template <class T>
std::pair<T, bool> HashTable<T>::search(const T & sought) {
    //hash the argument
    int hashValue = hashObject(sought, table.size());

    //find argument at set indicated by hash
    auto result = std::find(table[hashValue].begin(), table[hashValue].end(), sought);

    //if object was found, return found object and true
    if(result != table[hashValue].end())
        return std::pair<T, bool>(*result, true);
    //else return argument, false
    else
        return std::pair<T, bool>(sought, false);
}


/**
 * Searches the index for an index whose key matches the string passed as argument.
 */
template <class T>
std::pair<T, bool> HashTable<T>::stringSearch(const std::string & word) {

    int hashValue = hashObject(word, table.size());

    auto result = std::find_if(table[hashValue].begin(), table[hashValue].end(),
                               [word](const IndexedTerm & term) -> bool{ return term.getTerm() == word; });

    if(result != table[hashValue].end())
        return std::pair<T, bool>(*result, true);
    else
        return std::pair<T, bool>(IndexedTerm(word), false);
}


/**
 * Inserts new object to position given by hashing function
 */
template <class T>
void HashTable<T>::insert(const T & inserted) {
    //hash the object and insert to tree at correct position in table
    int hashValue = hashObject(inserted, table.size());
    auto result = table[hashValue].insert(inserted);

    //if already there, append data; else
    if(!result.second) {

        insertValue(inserted, result.first);

        //check to resize array
        if(checkResize())
            resize();
    } else {
        //increment count of elements
        numElements++;
    }

}


/**
 * Searches for a term matching the given string in the index. If found, appends the data to that term.
 * If not, inserts it to the index.
 */
template <class T>
void HashTable<T>::stringInsert(const std::string & word, int id, int freq, int loc) {

    int hashValue = hashObject(word, table.size());
    auto result = std::find_if(table[hashValue].begin(), table[hashValue].end(),
                               [word](const IndexedTerm & it) -> bool{ return it.getTerm() == word; });

    if(result != table[hashValue].end()) {
        (*result).appendData(id, freq, loc);

        if(checkResize())
            resize();
    } else {
        table[hashValue].insert(IndexedTerm(word, id, freq, loc));
        numElements++;
    }

}


/**
 * Supports overloaded calls to insert individual types of data
 */
template <class T>
void HashTable<T>::insertValue(const IndexedTerm & word, std::set<IndexedTerm>::iterator it) {
    *it += word;
}


/**
 * Determines whether or not there are any elements in the table
 */
template <class T>
bool HashTable<T>::isEmpty() const {
    //check if number of elements is equal to zero
    return numElements == 0;
}


/**
 * Clears table of all old elements
 */
template <class T>
void HashTable<T>::makeEmpty() {
    //create a new vector of old size, and get rid of the old one
    std::vector<std::set<T>> newTable(table.size());
    table = newTable;

    //set count to zero
    numElements = 0;
}


/**
 * Prints all elements in table in order of hash value
 */
template <class T>
std::ostream& HashTable<T>::print(std::ostream &os) const {
    //iterate over vector, std::copy-ing every non-empty element
    for(auto i = table.begin(); i != table.end(); i++) {
        for(auto j = (*i).begin(); j != (*i).end(); j++) {
            os << *j << std::endl;
        }
    }

    return os;
}


/**
 * Returns a vector of the top fifty most common sords.
 */
template <class T>
std::vector<T> HashTable<T>::getTopFifty() {

    std::vector<T> tops;

    for(auto i = table.begin(); i != table.end(); i++) {
        for(auto j = (*i).begin(); j != (*i).end(); j++) {
            if((*j).getTotalFreq() >= 1000) {
                tops.push_back(*j);
            }
        }
    }

    std::sort(tops.begin(), tops.end(),
              [](const IndexedTerm& lhs, const IndexedTerm& rhs) ->
              bool{ return lhs.getTotalFreq() > rhs.getTotalFreq(); });

    tops.resize(50);
    return tops;
}


/**
 * Returns the number of elements indexed by the table
 */
template <class T>
int HashTable<T>::getTerms() const {
    return numElements;
}


//============================
//HASHING OBJECTS AND RESIZING
//============================


/**
 * Takes an object and size value (defaulting to size of vector) as input and returns hash value
 */
template <class T>
int HashTable<T>::hashObject(const IndexedTerm & hashInput, int tableSize) const {

    //call adapted hash function
    std::hash<std::string> hashFn;
    return hashFn(hashInput.getTerm()) % tableSize;
}

/**
 * Hashes a string and mods the given value based on the size of the table
 */
template <class T>
int HashTable<T>::hashObject(const std::string & hashInput, int tableSize) const {

    std::hash<std::string> hashFn;
    return hashFn(hashInput) % tableSize;
}


/**
 * Returns the number of elements in the table
 */
template <class T>
int HashTable<T>::getNumElements() const {
    return numElements;
}


/**
 * Resizes the table to be twice the size of the old table with new hash values
 */
template <class T>
void HashTable<T>::resize() {

    //create new vector of double the size of old vector
    int newSize = 2*table.size();
    std::vector<std::set<T>> newTable(newSize);
    int hashValue;

    //for each element of vector
    for(auto i = table.begin(); i != table.end(); i++) {
        //if element not empty, iterate over set, sending every element to hash value for new vector
        if(!(*i).empty()) {
            for(auto j = (*i).begin(); j != (*i).end(); j++) {
                hashValue = hashObject(*j, newTable.size());
                newTable[hashValue].insert(*j);
            }
        }
    }

    //set member data to new vector
    table = newTable;
}


/**
 * Checks to see if table needs to be resized and returns true if 3*size of vector
 * is exceeded by number of elements
 */
template <class T>
bool HashTable<T>::checkResize() const {
    return 3*table.size() < numElements;
}


//=========
//OPERATORS
//=========

/**
 * Stream insertion operator prints every element in order, according to hash value
 */
template <class T>
std::ostream& operator <<(std::ostream& os, const HashTable<T>& ht) {
    //call print function
    return ht.print(os);
}


/**
 * Subscript operator accepts argument of type template parameter and
 * returns object stored at that key in the table
 */
template <class T>
std::pair<T, bool> HashTable<T>::operator [](const T & sought) {
    //call search function with argument
    return search(sought);
}

#endif // HASHTABLE_H
