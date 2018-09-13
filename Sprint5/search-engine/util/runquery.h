#ifndef RUNQUERY_H
#define RUNQUERY_H
#include "indexhandler.h"
#include "documentparser.h"
#include "indexedterm.h"
#include "input.h"
#include <vector>
#include <iostream>


using namespace std;
class runQuery
{
private:
    int andOrFlag;
    vector<string> Terms;
    vector<string> notTerms;
    vector<IndexedTerm> results;

public:
    runQuery();
    runQuery(string);
    void bracketLogic();
    void andLogic();
    void orLogic();
    void notLogic();
};

#endif // RUNQUERY_H
