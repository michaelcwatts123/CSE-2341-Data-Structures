#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;


/**
 * Container class for the contents of a query. Supports boolean logic for rejecting and including
 * certain search results based on user specification.
 *
 * Owner: Michael
 */
class input
{
private:


    vector<string> andOrWords; //holds all words to search
    vector<string> stop;
    vector<string> notWords; //holds all words not to be searched for

    string bracket(string &);

    void parseWords(string &); //parses the querey to single words
    void bracketCheck(int, int);
    void bracketStopWords(int,int);
    void loadStopWords();
    void removeStopWords();

    void stemWords();

public:
    input();

    int andOrFlag = 0; //determines if terms are and/or togehter, 0 for or 1 for and
    int getFlag();

    vector<string> getTermVector();
    vector<string> getNotTermVector();

};

#endif // INPUT_H
