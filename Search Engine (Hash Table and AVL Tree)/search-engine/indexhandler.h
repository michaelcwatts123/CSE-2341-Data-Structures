#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>

#include "indexinterface.hpp"
#include "indexedterm.h"
#include "avltree.hpp"
#include "hashtable.hpp"

/**
 * Provides a wrapper for the indexing data structures and includes functionality specific to this use case
 *
 * Owner: Carter
 */
class IndexHandler
{
private:
    IndexInterface<IndexedTerm> * documentIndex;            //pointer to Index base class
    std::vector<std::string> topFifty;
    
public:
    IndexHandler(std::string = "hash");
    ~IndexHandler();
    void addToIndex(std::string, int, int, int);            //adds object to index
    std::pair<IndexedTerm, bool> searchIndex(std::string);  //searches index for object by key
    void setNumQuestions(int);
    void writeToDisk();                                     //writes index to disk
    void readFromDisk();                                    //reads index from disk
    void updateTopFifty();
    int getNumTerms() const;
    std::vector<std::string> getTopFifty();
    //doesnt work
    int getQuestionsIndexed() { return documentIndex->getNumQuestions(); }
};

#endif // INDEXHANDLER_H
