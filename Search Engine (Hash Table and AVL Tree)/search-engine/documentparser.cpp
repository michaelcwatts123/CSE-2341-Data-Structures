#include "documentparser.h"
#include "csvparser.h"
#include "indexhandler.h"
#include "indexedterm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <strings.h>
/**
 * @brief Constructor for DocumentParser
 * @param Reference to index handler for adding words to an index
 */
DocumentParser::DocumentParser(IndexHandler* ih){
    indexHandler = ih;
}
/**
 * @brief Loads stop words from file and stores them in set
 * @param Name of file
 */
void DocumentParser::loadStopWords(std::string fileName){
    std::ifstream stopWords;
    std::string buffer;
    stopWords.open(fileName);
    if(stopWords.is_open()){
        while(stopWords >> buffer)
            set_stop_words.insert(buffer);
    }
    else
        std::cout << "File cannot be opened" << std::endl;
    stopWords.close();
}
/**
 * @brief Parses .csv file and seperates fields into an array
 * @param Name of file
 */
void DocumentParser::parse(std::string fileName){
    //variables for each field
    double ownerUserId;
    std::string creationDate, title, body, code, tag;
    int id, score;
    int wordNumber;
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new(fileName.c_str(), ",", 1);
    CsvRow *row;
    const CsvRow *header = CsvParser_getHeader(csvparser);
    //checks if header exists, always should with these .csv files
    if (header == NULL) {
        printf("%s\n", CsvParser_getErrorMessage(csvparser));
        return;
    }
    //assigns headers, might be useful?
    if(CsvParser_getNumFields(header) == 8){
    //gets next question and breaks it up
        while ((row = CsvParser_getRow(csvparser))) {
            wordNumber = 0;
            const char **rowFields = CsvParser_getFields(row);
            //assigns each field to proper variable, ignoring dummy field
            id = atoi(rowFields[1]);
            ownerUserId = atof(rowFields[2]);
            creationDate = std::string(rowFields[3]);
            score = atoi(rowFields[4]);
            title = std::string(rowFields[5]);
            body = std::string(rowFields[6]);
            code = std::string(rowFields[7]);
            if(body.length() >= 150){
                //std::cout << "TITLE" << std::endl;
                parseString(id, 0, title, wordNumber);
                //std::cout << "BODY" << std::endl;
                parseString(id, 1, body, wordNumber);
                CsvParser_destroy_row(row);
                questionsIndexed++;
            }
        }
    }
    else if(CsvParser_getNumFields(header) == 3){
        while ((row = CsvParser_getRow(csvparser))) {
            const char **rowFields = CsvParser_getFields(row);
            //assigns each field to proper variable, ignoring dummy field
            id = atoi(rowFields[1]);
            tag = rowFields[2];
            Porter2Stemmer::trim(tag);
            Porter2Stemmer::stem(tag);
            sendToIndex(tag, id, 10, 0);
        }
    }
    indexHandler->setNumQuestions(questionsIndexed);
    CsvParser_destroy(csvparser);
}
/**
 * @brief Processes content of str
 * @param ID of current question
 * @param Indicates header or body
 * @param Data to be processed
 * @param Word counting for double words
 */
void DocumentParser::parseString(int questionID, int flag, std::string str, int& wordNumber){
    std::string buffer;
    std::replace(str.begin(), str.end(), '\n', ' ');
    std::stringstream input(str);
    while(std::getline(input, buffer, ' ')){
        wordNumber++;
        Porter2Stemmer::trim(buffer); //trims before checking for stop word
        if(!checkStopWord(buffer) && buffer.length() > 1){
            Porter2Stemmer::stem(buffer);   //stems and trims word
            if(buffer != "" && buffer.length() < 20){
                //title content
                if(flag == 0){
                    sendToIndex(buffer, questionID, 3, wordNumber);
                }
                //body content
                else if(flag == 1){
                    sendToIndex(buffer, questionID, 1, wordNumber);
                }
            }
        }
    }
}

//Checks if str is a stop word according to the file
/**
 * @brief Checks if str is in the set of stop words
 * @param String to be compared
 * @return True if it is a stop word, false otherwise
 */
bool DocumentParser::checkStopWord(std::string str){
    return set_stop_words.find(str) != set_stop_words.end();
}
/**
 * @brief Adds word to index with other relevant data
 * @param term
 * @param questionID
 * @param frequency
 * @param wordNumber
 */
void DocumentParser::sendToIndex(std::string term, int questionID, int frequency, int wordNumber){
    //adds file to index, provides term, question ID, weighted frequency, and word # in question
    indexHandler->addToIndex(term, questionID, frequency, wordNumber);
}

//question lookup based on ID
/**
  * Takes in file path and an ID to be searched and returns question information.
  * Question information is returned as a vector.
  * User needs to be prompted for path to document
 */
std::vector<std::string> DocumentParser::questionLookup(int lookupID, std::string documentPath){
    int id, i = 0;
    std::vector<std::string> vec;
    std::string fileName = documentPath + findDocument(lookupID);
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new(fileName.c_str(), ",", 1);
    CsvRow *row;
    const CsvRow *header = CsvParser_getHeader(csvparser);
    //checks if header exists, always should with these .csv files
    if (header == NULL) {
        printf("%s\n", CsvParser_getErrorMessage(csvparser));
        return vec;
    }
    //assigns headers, might be useful?
    const char **headerFields = CsvParser_getFields(header);
    for (i = 0 ; i < CsvParser_getNumFields(header) ; i++) {
        //printf("TITLE: %s\n", headerFields[i]);
    }
    //gets next question and breaks it up
    while ((row = CsvParser_getRow(csvparser))) {
        const char **rowFields = CsvParser_getFields(row);
        //assigns each field to proper variable, ignoring dummy field
        id = atoi(rowFields[1]);
        if(id == lookupID){
            for(int i = 1; i <= 7; i++)
                vec.push_back(std::string(rowFields[i]));
            return vec;
        }
    }
}
/**
 * @brief DocumentParser::findDocument
 * @param The question ID to be searched
 * @return String corresponding to proper document
 */
std::string DocumentParser::findDocument(int id){
    if(id >= 80 && id <= 404290)
        return "2008-questions.csv";
    else if(id >= 404430 && id <= 2274530)
        return "2009-questions.csv";
    else if(id >= 1987570 && id <= 4572720)
        return "2010-questions.csv";
    else if(id >= 4572790 && id <= 8691130)
        return "2011-questions.csv";
    else if(id >= 8691180 && id <= 14106820)
        return "2012-questions.csv";
    else if(id >= 14106920 && id <= 20864390)
        return "2013-questions.csv";
    else if(id >= 20864430 && id <= 27727360)
        return "2014-questions.csv";
    else if(id >= 27727410 && id <= 34552540)
        return "2015-questions.csv";
    else
        return "2016-questions.csv";
}
