#include "runquery.h"

runQuery::runQuery()
{

}
runQuery::runQuery(string indexType){

     IndexHandler Indexhandler(indexType);


    //Indexhandler.readFromDisk(); DNE currently
     while(true){
        input userInput;
        Terms = userInput.getTermVector();
        notTerms = userInput.getNotTermVector();
        andOrFlag = userInput.getFlag();
        for (int i = 0; i < Terms.size(); i++){
        pair<IndexedTerm,bool> result = Indexhandler.searchIndex(Terms[i]);
        if(result.second)
        results.push_back(result.first);
        else {
            cout << Terms[i] << " has not been located, so it will be ignored"<< endl;
        }
        }
        if(andOrFlag == 1){
        andLogic();
        } else {
            orLogic();
        }
        notLogic();

     }

}
void runQuery::andLogic(){
    IndexedTerm base = results[0]; //sets base to be first searchedTerm

    for(int i = 1; i< results.size();i++){ //cyclesthrough remaining temrs
        for(int j = 0;j < base.getQuestionVector().size();j++){ //cycles through Base ID's
            pair <pair<int,int>,bool> response = results[i].search(7); //checks to see if Base has any ID in common with current term
            if(response.second){
                base.getQuestionVector()[j].second *= response.first.second; //if so increaes frequency score
            }
        }
    }

}
void runQuery::orLogic(){ //same as and but with + increase instead of *
    IndexedTerm base = results[0];
    for(int i = 1; i< results.size();i++){
        for(int j = 0;j < base.getQuestionVector().size();j++){
            pair <pair<int,int>,bool> response = results[i].search(base.getQuestionVector()[j]);
            if(response.second){
                base.getQuestionVector()[j].second += response.first.second;
            }
        }
    }
}
void runQuery::notLogic(){ //same as above but sets score equal to zero
    IndexedTerm base = results[0];

    for(int i = 1; i< results.size();i++){
        for(int j = 0;j < base.getQuestionVector().size();j++){
            pair <pair<int,int>,bool> response = results[i].search(base.getQuestionVector()[j]);
            if(response.second){
                base.getQuestionVector()[j].second *= 0;
            }
        }
    }

}
