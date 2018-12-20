#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <string>
#include <vector>
#include "indexhandler.h"
#include <set>
#include <unordered_set>
#include "porter2_stemmer.h"

/**
 * The DocumentParser reads in data from .csv files and sends them to be added to the index.
 * Sits on top of the CSVParser class.
 *
 * Owner: Evan
 */

class DocumentParser
{
    int questionsIndexed = 0;
    std::unordered_set<std::string> set_stop_words;
    IndexHandler* indexHandler;
    bool checkStopWord(std::string str);
    void parseString(int questionID, int flag, std::string str, int &wordNumber);
    void sendToIndex(std::string term, int questionID, int frequency, int wordNumber);
    std::string findDocument(int id);
public:
    DocumentParser(IndexHandler *ih);
    void parse(std::string fileName);
    void loadStopWords(std::string fileName);
    std::vector<std::string> questionLookup(int lookupID, std::string documentPath);
};

#endif // DOCUMENTPARSER_H
