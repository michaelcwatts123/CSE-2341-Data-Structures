#ifndef INDEXEDTERM_H
#define INDEXEDTERM_H

#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <functional>

/**
 * Container class that holds a term along with each question it is found in and the term's
 * frequency in that question and each location within that question.
 *
 * Owner: Carter
 */
class IndexedTerm
{
private:

    class questionIndex {
    private:
        int questionId;
        mutable int frequency;
        mutable std::vector<int> locations;

    public:
        questionIndex() {
            questionId = 0;
            frequency = 0;
        }
        questionIndex(int id) {
            questionId = id;
            frequency = 0;
        }
        questionIndex(int id, int freq, int loc) {
            questionId = id;
            frequency = freq;
            locations.push_back(loc);
        }
        int getId() const { return questionId; }
        int getFreq() const { return frequency; }
        std::vector<int> getLoc() const { return locations; }
        //comparison operators only compare questionID
        bool operator ==(const questionIndex& rhs) const { return rhs.questionId == questionId ; }
        bool operator <(const questionIndex& rhs) const { return rhs.questionId < questionId ; }
        bool operator >(const questionIndex& rhs) const { return rhs.questionId > questionId ; }
        //append adds data to questionIndex
        void append(int freq, int loc) const {
            frequency += freq;
            locations.push_back(loc);
        }

        friend std::ostream& operator<<(std::ostream& os, questionIndex qi) {
            os << qi.questionId << '|' << qi.frequency << ',';

            for(auto i = qi.locations.begin(); i != qi.locations.end(); i++)
                os << *i << ',';

            return os;
        }

        friend class IndexedTerm;
    };

    std::string term;
    mutable std::unordered_map<int, questionIndex> idWithFrequency;
    mutable int totalFreq;


public:
    IndexedTerm(std::string = "");
    IndexedTerm(std::string, int, int, int);
    std::string getTerm() const;                            //get value of search term
    bool isEmpty() const;
    int getFrequency(int) const;                            //returns frequency of term in given question; 0 if not in questions
    std::vector<int> getLocations(int) const;               //gets vector of locations in particular question
    std::set<int> getQuestionIds() const;
    void addQuestion(int);
    void removeQuestion(int);

    std::vector<std::pair<int, int> > print15(); //prints the first 15 items of idWithFrequency
    void sort(std::vector<questionIndex> &,int); //sorts vectors in ascending order

    IndexedTerm questionAnd(const IndexedTerm &) const;
    IndexedTerm questionOr(const IndexedTerm &) const;
    bool isInQuestion(int) const;
    void addLocation(int, int);
    void removeLocation(int, int);
    void addFrequency(int, int);
    bool isAtLocation(int, int) const;
    void appendData(int, int, int) const;
    int getTotalFreq() const;
    bool operator==(const IndexedTerm&) const;              //opertor == just checks keys; worries about internal data later
    void operator+=(const IndexedTerm&) const;              //operator += appends ID or increases frequency with given ID
    bool operator>(const IndexedTerm&) const;
    bool operator<(const IndexedTerm&) const;
    friend std::ostream& operator <<(std::ostream& os, IndexedTerm it) {
        os << it.term << '|';

        for(auto i = it.idWithFrequency.begin(); i != it.idWithFrequency.end(); i++) {
            os << (*i).second << "|";
        }

        return os;
    }
};

#endif // INDEXEDTERM_H
