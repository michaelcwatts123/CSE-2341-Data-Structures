#include "runquery.h"
/**
 * Default constructor
 */
runQuery::runQuery()
{

}
/**
 * @brief Searches index for and returns results of Query
 * @param the name of the type of index to form
 */
runQuery::runQuery(string indexType){

     IndexHandler Indexhandler(indexType); //creates index
    DocumentParser docs(&Indexhandler);
    string filepath = "../../../../data/";
    Indexhandler.readFromDisk(); //reads index in from disk

    while(searchFlag == 0){ //infinite loop

        input userInput; //gets user input to be searched for
        Terms = userInput.getTermVector();

        notTerms = userInput.getNotTermVector();
        andOrFlag = userInput.getFlag();
        results.clear();
        notResults.clear();
        pair<IndexedTerm,bool> result;
        pair<IndexedTerm,bool> notResult;
        for (unsigned int i = 0; i < Terms.size(); i++){ //searches every term
        if(!Terms.empty()){
            if(Terms[0] == "*"){
                searchFlag = 1;
                continue;
            }
            if(Terms[i][0] != '!'){ //detects if bracketed term
             result = Indexhandler.searchIndex(Terms[i]);
             if(result.second){ //detects if term is found

                 results.push_back(result.first); //if found adds to results vector
             } else { //else informs user
                 cout << Terms[i] << " has not been located, so it will be ignored"<< endl;
             }
            } else {
                pair<string,string> bracketTerms = delimit(Terms[i]); //splits bracketed terms
                pair<IndexedTerm,bool> result1;
                result1 = Indexhandler.searchIndex(bracketTerms.first); //searches for first term
                 pair<IndexedTerm,bool> result2;
                 result2 = Indexhandler.searchIndex(bracketTerms.second); //searches for second term
                 if (result1.second && result2.second){ //if both found
                       results.push_back(bracketLogic(result1.first,result2.first)); //adds term to results
                 } else { //else informs user bracketed term is not found
                     cout << "Term [" << bracketTerms.first << " " << bracketTerms.second << "] not found" << endl;
                 }
            }
        }
        }
        for(unsigned int i = 0; i < notTerms.size(); i++){
        if(!notTerms.empty()){ //detects if there are terms to not
            if(notTerms[i][0] != '!'){ //detects bracketed terms
             notResult = Indexhandler.searchIndex(notTerms[i]);
             if(notResult.second) //if term is found
             notResults.push_back(notResult.first); //adds to notResults
             else { //else informs user
                              cout << notTerms[i] << " has not been located, so it will be ignored"<< endl;
                          }
            } else {
                pair<string,string> bracketTerms = delimit(notTerms[i]); //splits brakceted term into single words
                pair<IndexedTerm,bool> result1;
                result1 = Indexhandler.searchIndex(bracketTerms.first); //searches for first word
                 pair<IndexedTerm,bool> result2;
                 result2 = Indexhandler.searchIndex(bracketTerms.second); //searches for second term
                 if (result1.second && result2.second){
                       notResults.push_back(bracketLogic(result1.first,result2.first)); //adds results to notResults
                 } else {
                     cout << "Term [" << bracketTerms.first << " " << bracketTerms.second << "] not found" << endl;
                 }
            }
        }
        }


        if(!results.empty()){ //sets base
        base = results[0];

        if(andOrFlag == 1){ //calls either and or or logic based on flag
        andLogic();
        } else {
            orLogic();
        }

        notLogic(); //calls not logic

        Ids.clear();
        Ids = base.print15(); //prints the first 15 results of the sorted vector of results
        for(unsigned int i = 0; i < Ids.size(); i++){
        vector<string> info = docs.questionLookup(Ids[i].first,filepath);
           cout << (i+1) <<"." <<endl;
           cout << "\tTitle: " << info[4] << endl;
           cout << "\tDate: " << dateFix(info[2]) << endl;
           cout << "\tRelevancy: " << Ids[i].second << endl;
        }
        int selection = menu() -1;
        if(selection == -1){
            continue;
        } else {
            vector<string> info = docs.questionLookup(Ids[selection].first,filepath);
            cout << (selection+1) <<"." <<endl;
            cout << "\tTitle: " << info[4] << endl;
            cout << "\tDate: " << dateFix(info[2]) << endl;
            cout << "\tRelevancy: " << Ids[selection].second << endl;
            cout << "Question:" << endl;
            cout << info[5] << endl;
            if(!info[6].empty()){
            cout << "Code:" << endl;
            cout << info[6] << endl;
            }
            string decision = menu2();
            if (decision == "n"){
                searchFlag = 1;
            }

        }

        } else { //else informs user nothing has been found
            if(searchFlag == 0)
                cout << "No results" << endl;
        }

     }

}

/**
 *@brief Prompts the user for their question selection
 * @return the integer menu choice of the user
 */
int runQuery::menu(){
    string choice;
    int number;
    while(true){
        cout << "Enter the question number you would like to see or 0 to search again" << endl;
        cin >> choice;
        number = stoi(choice);
        if(number < 16 && number > -1){
            return number;
        } else {
            cout << "Invalid option. Try again" << endl;
        }

    }
}

/**
 * @brief removes extra characters from date string of question
 * @param the string containing the date with excess characters
 * @return the string with the excess characters removed
 */
string runQuery::dateFix(string date){
    int delimiter1;
    int delimiter2;
    delimiter1 = date.find('T');
    delimiter2 = date.find('Z');
    date[delimiter1] = ' ';
    date[delimiter2] = ' ';
    return date;
}

/**
 * @brief Prompts the user to search again
 * @return the string containing the user's choice
 */
string runQuery::menu2(){
    string choice;
    while(true){
        cout << "Would you like to search again? (Y/N)" << endl;
        cin >> choice;
        for(unsigned int i = 0; i < choice.length(); i++){ //loops through setting entire string to lowercase to avoid case issues
            choice[i] = tolower(choice[i]);
        }
        if(choice == "y" || choice == "n"){
            return choice;
        } else {
            cout << "Invalid choice. Try Again" << endl;
        }
    }
}

/**
 * @brief splits bracketed phrases into indivudal strings
 * @param the string to split into two strings
 * @return a pair of strings containing each term
 */
pair<string,string> runQuery::delimit(string s){
        string s1 = s;
        string s2;
        int delimeter = s1.find(' ');
        s1.erase(0,1);
        s2 = s1.substr(0,delimeter-1);
        s1.erase(0,delimeter);
        pair<string,string> value;
        value.first = s2;
        value.second = s1;
        return value;

}
/**
 * @brief Handles logic for terms which are bracketed together by and-ing the two indivudal terms
 * @param the first IndexedTerm of the bracketed phrase
 * @param the second IndexedTerm of the bracketed phrase
 * @return an Indexed phrase holding all the questionIDs the terms share with inflated frequencies
 */
IndexedTerm runQuery::bracketLogic(IndexedTerm t1, IndexedTerm t2){


    IndexedTerm toBeAdded = t1; //creates term to store new values

    set<int> dummy= t1.getQuestionIds();  //gets questionIDs of first term


   for(auto it = dummy.begin(); it != dummy.end();++it){ //cycles through first terms question IDs
       int hold = *it;
        for(unsigned int j = 0; j < t1.getLocations(hold).size();j++){ //cycles through all location of a term in a specific question ID
            int a = t1.getLocations(hold)[j];
            for(unsigned int k = 0; k < t2.getLocations(hold).size(); k++){ //cycles through all location of a term in a specific question ID
                int b = t2.getLocations(hold)[j];
                if(a+1 == b){ //if the locations are sequential in a question
                    toBeAdded.addFrequency(hold, t1.getFrequency(hold) * t2.getFrequency(hold)); //inflate score
                } else { //else deflate score
                    toBeAdded.addFrequency(hold, (t1.getFrequency(hold) * -1) );
                }
            }
        }
    }
    return toBeAdded; //return modified result
}

/**
 * @brief Handles logic to And terms together by multiplying the score of terms and-ed together
 */
void runQuery::andLogic(){
    questionIDs = base.getQuestionIds(); //gets set of ints of all question IDs from base
    for(unsigned int i = 1; i< results.size();i++){ //cycles through all results
    for(auto it = questionIDs.begin(); it != questionIDs.end(); ++it){ //cycles through all question IDs
        int a = *it;
        base.addFrequency(a,(base.getFrequency(a) * results[i].getFrequency(a)));
        //if terms are both in a question inflate answer highly by multiplying socres
    }
}

/**
* @brief Handles logic to Or terms together by adding the scores of terms or-ed together
*/
}
void runQuery::orLogic(){ //same as and but with + increase instead of *
    questionIDs = base.getQuestionIds();
    for(unsigned int i = 1; i< results.size();i++){
    for(auto it = questionIDs.begin(); it != questionIDs.end(); ++it){
        int a = *it;
        base.addFrequency(a,(base.getFrequency(a) + results[i].getFrequency(a)));
    }
    }
}

/**
 * @brief Handles logic to not terms together by modifying the score of notted terms to be very small
 */
void runQuery::notLogic(){ //same as above but sets score equal to large negative value
    questionIDs = base.getQuestionIds();
    for(unsigned int i = 1; i< notResults.size();i++){
    for(auto it = questionIDs.begin(); it != questionIDs.end(); ++it){
        int a = *it;
        base.addFrequency(a,(base.getFrequency(a) + (notResults[i].getFrequency(a) * -999999999)));
    }
    }

}
