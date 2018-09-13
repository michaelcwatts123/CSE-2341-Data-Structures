#ifndef RUNQUERY_H
#define RUNQUERY_H
#include "indexhandler.h"
#include "documentparser.h"
#include "indexedterm.h"
#include "input.h"
#include <vector>
#include <iostream>

/**
 * Implements logic for querying the index.
 *
 * Owner: Michael
 */
using namespace std;
class runQuery
{
private:
    int andOrFlag; //flag for if terms are and-ed or or-ed together
    int searchFlag = 0;
    int menu();

    vector<string> Terms; //terms to be searched for
    vector<string> notTerms; //terms not to be searched for

    vector<IndexedTerm> results; //resuls of search
    vector<IndexedTerm> notResults; //results of not search

    vector<pair<int,int>> Ids;

    IndexedTerm base;

    set<int> questionIDs; //question IDs for base term

    string dateFix(string);
    string menu2();

public:
    runQuery(); //default constructor
    runQuery(string);

    pair<string, string> delimit(string s); //logic to split brakceted terms

    IndexedTerm bracketLogic(IndexedTerm, IndexedTerm); //logic to handle bracketed terms

    void andLogic(); //logic to and terms together
    void orLogic(); //logic to or terms together
    void notLogic(); //logic to exclude terms from search
};

#endif // RUNQUERY_H
