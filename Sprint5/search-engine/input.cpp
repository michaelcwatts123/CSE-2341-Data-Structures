#include "input.h"
#include <vector>
#include <cstring>
#include <iostream>
#include "porter2_stemmer.h"

using namespace std;
/**
 *@brief Prompts the user for an input Query for searching
 */
input::input()
{
    loadStopWords();
    string initalQuery;
    cout << "Enter a query or * to quit searching" << endl;
    while(initalQuery.empty()){
    getline(cin,initalQuery);
    }
    initalQuery += ' ';
    for(unsigned int i = 0; i < initalQuery.length(); i++){ //loops through setting entire string to lowercase to avoid case issues
        initalQuery[i] = tolower(initalQuery[i]);
    }

    parseWords(initalQuery);

}

/**
 * @brief removes bracket from the second word of a bracketed phrase
 * @param The second word of a bracketed phrase ending with a ]
 * @return the corrected second term without the ]
 */
string input::bracket(string &s){

    string secondWord = s.substr(0,s.find(']'));
    s.erase(0,s.find(']') + 1);
    return secondWord;
}

/**
 * @brief Parses a string into individual words and fills the proper vector with the terms
 * @param the phrase to be parsed into single words
 */
void input::parseWords(string &s){
    string Words = s.substr(0,s.find(' '));
    int notFlag = 0;
    if (Words == "and"){
        andOrFlag = 1;//sets andOr flag to and position (1)
    }
    while(s.length() != 0){
    if(s == ""){
        break;
    }
    Words = s.substr(0,s.find(' '));
    s.erase(0,s.find(' ') + 1);
    if(Words == "not"){
        notFlag =1;
    }
    if(Words == "and" || Words == "not" || Words == "or"){
        continue;
    }
    if(Words[0] == '['){

        Words += " ";
        Words += bracket(s);
        Words.erase(0,1);
        Words = "!" + Words;
    }
    if(notFlag == 1){
        if(Words != "")
        notWords.push_back(Words);
    } else {
        if(Words != "")
        andOrWords.push_back(Words);
    }

    }
    removeStopWords();
    stemWords();


}

/**
 * @brief checks bracketed terms to determine if they contain more than two terms, erases them if they contain more than 2 terms
 * @param a flag determining which vector the term belongs to 0 for andOrWords 1 for notWords
 * @param the place of the term in the chosen vector
 */
void input::bracketCheck(int flag, int place){
    string s;
    string delimiter = " ";
    if(flag == 0){
       s = andOrWords[place];
       s.erase(0,s.find(delimiter) + 1);
       int postion = s.find(delimiter);
       if(postion != -1){
           andOrWords[place].erase(0,1);
           cout << "Bracket Terms can only have two terms. " << andOrWords[place] << " will be ignored." << endl;
           andOrWords.erase(andOrWords.begin() + place);
       }
    }
    if(flag == 1){
        s = notWords[place];
        s.erase(0,s.find(delimiter)+1);
        int postion = s.find(delimiter);
        
        if(postion != -1){
            notWords[place].erase(0,1);
            cout << "Bracket Terms can only have two terms. " << notWords[place] << " will be ignored." << endl;
            notWords.erase(notWords.begin() + place);
        }
    }
}

/**
 * @brief removes stop words from bracketed phrases
 * @param a flag determining which vector the term belongs to 0 for andOrWords 1 for notWords
 * @param the place of the term in the chosen vector
 */
void input::bracketStopWords(int flag, int postion){
    string phrase;
    string s1;
    string s2;
    if(flag == 0){
        phrase = andOrWords[postion];
    }
    if(flag == 1){
        phrase = notWords[postion];
    }
    phrase.erase(0,1);
    s1 = phrase.substr(0,phrase.find(" "));
    phrase.erase(0,phrase.find(" ") + 1);
    s2 = phrase;
    vector<string>::iterator it;
    it = find(stop.begin(),stop.end(),s1);
    if(it != stop.end()){
        s1 = "!";
    }
    it = find(stop.begin(),stop.end(),s2);
    if(it != stop.end()){
        s2 = "!";
    }
    if(s1 == "!" && s2 == "!"){
        if(flag == 0){
            andOrWords.erase(andOrWords.begin() + postion);
        }
        if(flag == 1){
            notWords.erase(notWords.begin() + postion);
        }
    }
    if(s1 == "!" && s2 != "!"){
        if(flag == 0){
            andOrWords[postion] = s2;
        }
        if(flag == 1){
            notWords[postion] = s2;
        }
    }
    if(s1 != "!" && s2 == "!"){
        if(flag == 0){
            andOrWords[postion] = s1;
        }
        if(flag == 1){
            notWords[postion] = s1;
        }
    }

}

/**
 * @brief Loads the stop words file and stores content in vector
 */
void input::loadStopWords(){
    std::ifstream stopWords;
    std::string buffer;
    stopWords.open("../stop_words.txt");
    if(stopWords.is_open()){
        while(stopWords >> buffer)
            stop.push_back(buffer);
    }
    else
        std::cout << "File cannot be opened" << std::endl;
    stopWords.close();
}

/**
 * @brief removes stop words from search vectors
 */
void input::removeStopWords(){
    for(unsigned int i = 0; i < stop.size();i++){
        vector<string>::iterator it;
        it = find(andOrWords.begin(),andOrWords.end(),stop[i]);
        if(it != andOrWords.end()){
            andOrWords.erase(it);
        }
    }
    for(unsigned int i = 0; i < stop.size();i++){
        vector<string>::iterator it;
        it = find(notWords.begin(),notWords.end(),stop[i]);
        if(it != notWords.end()){
            notWords.erase(it);
        }
    }
    for(unsigned int i = 0; i < andOrWords.size(); i++){
        if(andOrWords[i][0] == '!')
            bracketStopWords(0,i);
    }
    for(unsigned int i = 0; i < notWords.size(); i++){
        if(notWords[i][0] == '!')
            bracketStopWords(1,i);
    }
}



/**
 * @brief stems each word to be searched
 */
void input::stemWords(){
    for(unsigned int i = 0; i < andOrWords.size(); i++){
        Porter2Stemmer::stem(andOrWords[i]);
        if(andOrWords[i][0] == '!'){
             bracketCheck(0,i);
        }
    }

    for(unsigned int i = 0; i < notWords.size(); i++){
        Porter2Stemmer::stem(notWords[i]);
        if(notWords[i][0] == '!'){
            bracketCheck(1,i);
        }
    }
}

/**
 * @brief Returns the vector of terms to be searched for
 * @return the vector of andOrWords
 */
vector<string> input::getTermVector(){
    return andOrWords;
}

/**
 * @brief Returns the vector of terms to be notted with search results
 * @return the vector of notWords
 */
vector<string> input::getNotTermVector(){
    return notWords;
}

/**
 * @brief Returns the flag that determines if words to be and/or together
 * @return the andOrFlag used to determine if words are and-ed or or-ed together
 */
int input::getFlag(){
    return andOrFlag;
}

