#include "indexedterm.h"

#include <utility>
#include <map>
#include <iostream>

//============
//CONSTRUCTORS
//============

IndexedTerm::IndexedTerm(std::string termIndex) : term(termIndex) {}


IndexedTerm::IndexedTerm(std::string word, int questionID, int frequency, int loc) {

    //set term
    term = word;

    //create new question with id, frequency, and location
    questionIndex question(questionID);
    question.append(frequency, loc);
    totalFreq = frequency;

    idWithFrequency.insert({questionID, question});
}


//===================
//GETTERS AND SETTERS
//===================

/**
 * Gets value of search term
 */
std::string IndexedTerm::getTerm() const {
    return term;
}


/**
 * Returns a set of all of the question IDs that this term is found in
 */
std::set<int> IndexedTerm::getQuestionIds() const {

    //construct a set
    std::set<int> idSet;
    std::insert_iterator<std::set<int>> inserter(idSet, idSet.begin());

    std::transform(idWithFrequency.begin(), idWithFrequency.end(),
                   inserter, []( std::pair<int, questionIndex> q ) -> int {
                    return q.second.getId(); } );

    return idSet;
}


/**
 * Retrieves the frequency of the question ID passed as argument; returns 0 if not present.
 */
int IndexedTerm::getFrequency(int questionID) const {

    //find the question in question set
    auto result = idWithFrequency.find(questionID);

    //if question is there, return frequency, else return 0
    if(result != idWithFrequency.end())
        return (*result).second.getFreq();
    else
        return 0;
}


/**
 * Returns the vector of locations attached to the given question ID.
 */
std::vector<int> IndexedTerm::getLocations(int questionId) const {

    //find the question in question set
    auto result = idWithFrequency.find(questionId);

    //if not present in set, return empty vector
    if(result == idWithFrequency.end())
        return std::vector<int>();

    //if present, return location vector
    else
        return (*result).second.getLoc();
}


/**
 * @brief Prints the first 15 values of the sorted Vector of results
 * @return a vector of pairs containing questionIDs and and frequencies of a term
 */

std::vector<std::pair<int,int>> IndexedTerm::print15(){

    std::vector<questionIndex> output;
    for(auto kv : idWithFrequency){
        output.push_back(kv.second);
    }

    std::vector<std::pair<int,int>> Ids;

    sort(output,0);
    int count = 0;
    for(unsigned int i = 0; i < output.size(); i++){
        if(count == 15){
            break;
        }
        count++;
        std::pair<int,int> info;
        info.first = output[i].getId();
        info.second = output[i].getFreq();
        Ids.push_back(info);
    }
    return Ids;
}


/**
 * Sorts a vector in descending order
 * @param the vector to sort
 * @param the location to begin sorting
 */
void IndexedTerm::sort(std::vector<questionIndex> &output, int position){
    if(position != output.size()){ //guard statment to detect end of sort
    for(int i = 0 + position; i < output.size(); i++){ //cycles through array each time incrementing the starting point

        if(output[position].getFreq() < output[i].getFreq()){ //detects if value at counter is greater than any other value in array
            std::swap(output[position], output[i]); //if so swaps it to put array in ascending order
        }
    }
    sort(output,position+1); //recursive call to repeat this function until end of array
    }
}


/**
 * Adds location to location vector of specified question
 */
void IndexedTerm::addLocation(int questionId, int location) {

    //find the question
    auto result = idWithFrequency.find(questionId);

    //if question doesn't exist, throw an exception
    if(result == idWithFrequency.end())
        throw std::runtime_error("This term is not contained in the given question.");

    //else, push new location
    else
        (*result).second.locations.push_back(location);

}


/**
 * Removes location from location vector of specified question
 */
void IndexedTerm::removeLocation(int questionId, int location) {

    //find the question
    auto result = idWithFrequency.find(questionId);

    //if question doesn't exist, throw an exception
    if(result == idWithFrequency.end())
        throw std::runtime_error("The specified question is not one in which this term appears.");
    //else, remove the location from question
    else
        (*result).second.locations.erase(std::remove((*result).second.locations.begin(),
                                                    (*result).second.locations.end(), location),
                                        (*result).second.locations.end());
}


/**
 * Adds frequency to frequency of specified question
 */
void IndexedTerm::addFrequency(int questionId, int frequency) {

    //find the question
    auto result = idWithFrequency.find(questionId);

    //if question doesn't exist, throw exception
    if(result == idWithFrequency.end())
        throw std::runtime_error("The specified question is not one in which this term appears.");

    //else, add frequency to question
    else
        (*result).second.frequency += frequency;

    totalFreq += frequency;
}


/**
 * Adds questionId to the set of questions this term is found in.
 */
void IndexedTerm::addQuestion(int questionId) {

    //insert a new question to the set

    idWithFrequency.insert({questionId, questionIndex(questionId)});


}


/**
 * Removes the specified question from the set if there or throws error if not
 */
void IndexedTerm::removeQuestion(int questionId) {

    //find the question
    auto result = idWithFrequency.find(questionId);

    //remove if found, throw error if not
    if(result != idWithFrequency.end())
        idWithFrequency.erase(result);
    else
        throw std::runtime_error("The specified question is not one in which this term appears.");
}


/**
 * Returns true if term is in question, false if not
 */
bool IndexedTerm::isInQuestion(int questionId) const {

    //find question
    auto result = idWithFrequency.find(questionId);

    //return false if end iterator, true if not
    if(result == idWithFrequency.end())
        return false;
    else
        return true;

}


/**
 * Determines whether or not the term appears in the given
 * question at the given location.
 */
bool IndexedTerm::isAtLocation(int questionId, int location) const {

    //find question in set
    auto result = idWithFrequency.find(questionId);

    //if question in set and location vector contains location, return true
    if(result != idWithFrequency.end()) {

        if(std::find((*result).second.locations.begin(), (*result).second.locations.end(), location) !=
                (*result).second.locations.end())
            return true;
        else
            return false;

        //else return false
    } else {
        throw std::runtime_error("The specified question is not one in which this term appears.");
    }
}



int IndexedTerm::getTotalFreq() const {
    return totalFreq;
}



/**
 * Determines whether or not the set of question IDs is empty
 */
bool IndexedTerm::isEmpty() const {
    return idWithFrequency.empty();
}


//=========
//OPERATORS
//=========

/**
 * Equality operator checks keys (terms) for equality
 */
bool IndexedTerm::operator ==(const IndexedTerm& rhs) const {
    return term == rhs.term;
}


/**
 * Addition Assignment Operator adds question ID to list if it isn't there,
 * if it is present, adds frequency
 */
void IndexedTerm::operator +=(const IndexedTerm& rhs) const {
    /*
     * First, check to make sure keys are the same.
     * If not, throw big, scary error because
     * something is seriously wrong.
     */
    if(term != rhs.term)
        throw std::invalid_argument("Keys mismatched when trying to append Question ID data.");

    questionIndex ques = (*rhs.idWithFrequency.begin()).second;
    auto result = idWithFrequency.insert({ques.getId(), ques});

    totalFreq += ques.getFreq();

    if(!result.second) {
        (*result.first).second.append(ques.getFreq(), ques.getLoc()[0]);
    }
}


/**
 * Appends all data associated with a particular question to the term.
 */
void IndexedTerm::appendData(int questionId, int frequency, int location) const {

    auto result = idWithFrequency.insert({questionId,
                                          questionIndex(
                                          questionId,
                                          frequency,
                                          location)});

    totalFreq += frequency;
    if(!result.second) {
        (*result.first).second.append(frequency, location);
    }
}


/**
 * Compares the terms using lexicographical comparison of the
 * ASCII values of each character in the string.
 */
bool IndexedTerm::operator <(const IndexedTerm& rhs) const {
    return term < rhs.term;
}


/**
 * Compares the terms using lexicographical comparison of the
 * ASCII values of each character in the string.
 */
bool IndexedTerm::operator >(const IndexedTerm& rhs) const {
    return term > rhs.term;
}

