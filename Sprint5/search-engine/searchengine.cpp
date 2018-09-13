#include "searchengine.h"
#include <string>
#include <iostream>
#include <fstream>
#include <fstream>
using namespace std;
SearchEngine::SearchEngine()
{
}

void SearchEngine::run(){
    cout << "Welcome to Goggle" << endl;
    cout << "Press 1 for maintenance mode or 2 for interactive mode:" << endl;
    int input;
    cin >> input;
    if(input == 1)
        maintenanceMode();
    else if(input == 2)
        interactiveMode();
    else {
        cout << "Invalid option" << endl;
        run();
    }
}

void SearchEngine::interactiveMode(){
    cout << "What kind of index do you want? (avl/hash)" << endl;
    string input;
    cin >> input;
    if(input != "hash" && input != "avl"){
        cout << "Invalid data type" << endl;
        interactiveMode();
    }
    IndexHandler ih(input);
    ih.readFromDisk();
    ih.updateTopFifty();
    system("clear");
    while(true){
        cout << "Please select an option:\n1. Search\n2. List 50 most indexed terms\n3. List number of questions indexed\n4. List number of words indexed\n*. exit" << endl;
        char choice;
        cin >> choice;
        if(choice == '1'){
            runQuery rq(input);
        }

        else if(choice == '2'){
            vector<string> vec = ih.getTopFifty();
            for(int i = 0; i < vec.size(); i++)
                cout << vec[i] << endl;
        }
        else if(choice == '3')
            cout << "There are " << ih.getQuestionsIndexed() << " questions indexed." << endl;
        else if(choice == '4')
            cout << "There are some words indexed" << endl;
        else if(choice == '*') {
            break;
        }
        else
            cout << "Invalid choice" << endl;
    }

}

void SearchEngine::maintenanceMode(){
    IndexHandler ih("hash");
    DocumentParser d(&ih);
    d.loadStopWords("../stop_words.txt");
    string input = "";
    int choice = 0;
    cout << "Press 1 to load new files or press 2 to clear index: " << endl;
    cin >> choice;
    if(choice == 1){
        while(true){
            cout << "Type file name and path to parse, or type \"*\" to exit: " << endl;
            cin >> input;
            if(input == "*"){
                ih.updateTopFifty();
                ih.writeToDisk();
                break;
            }
            d.parse(input);
        }
    }
    else if(choice == 2){
        ofstream clear;
        clear.open("../index.txt");
        clear.close();
    }
    else{
        cout << "Invalid choice." << endl;
        maintenanceMode();
    }
}
