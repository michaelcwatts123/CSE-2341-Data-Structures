#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>

/**
 * Parent class for each indexing data structure. Declares functions considered necessary
 * functionality for an indexing data structure.
 *
 * Owner: Carter
 */
template <class T>
class IndexInterface
{
    int numQuestions;

public:
    IndexInterface() {}
    IndexInterface(const IndexInterface<T>&) {}
    IndexInterface<T>& operator =(const IndexInterface<T>&) {}
    int getNumQuestions() const { return numQuestions; }
    void setNumQuestions(int questionsIndexed) { numQuestions = questionsIndexed; }
    virtual ~IndexInterface();
    virtual bool contains(const T&) const = 0;
    virtual std::pair<T, bool> search(const T&) = 0;
    virtual void insert(const T&) = 0;
    virtual bool isEmpty() const = 0;
    virtual void makeEmpty() = 0;
    virtual std::pair<T, bool> stringSearch(const std::string&) = 0;
    virtual void stringInsert(const std::string&, int, int, int) = 0;
    virtual std::ostream& print(std::ostream& os) const { return os; }
    virtual std::vector<T> getTopFifty() = 0;
    virtual int getTerms() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const IndexInterface<T>& ii) {
        return ii.print(os);
    }
};

template<class T>
IndexInterface<T>::~IndexInterface() {}

#endif // INDEXINTERFACE_H
