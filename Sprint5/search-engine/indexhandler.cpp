#include "indexhandler.h"

#include <cstring>

IndexHandler::IndexHandler(std::string indexType) {
    //instantiate object of type specified by argument
    if(indexType == "avl")
        documentIndex = new AVLTree<IndexedTerm>;

    else if(indexType == "hash")
        documentIndex = new HashTable<IndexedTerm>;

    else
        throw std::invalid_argument("That type of index has not been constructed yet.");
}


IndexHandler::~IndexHandler() {
    delete documentIndex;
}


/**
 * Adds an object with the specified term, question ID, and frequency to the index.
 */
void IndexHandler::addToIndex(std::string term, int questionId, int frequency, int location) {

    //create object according to specifications and insert to index
    documentIndex->stringInsert(term, questionId, frequency, location);
}


/**
 * Searches the index for the specified term.
 */
std::pair<IndexedTerm, bool> IndexHandler::searchIndex(std::string toBeFound) {
    //create object according to term and return results of index search
    return documentIndex->stringSearch(toBeFound);
}


/**
 * Sets the number of questions tracker in the index
 */
void IndexHandler::setNumQuestions(int numQuestions) {
    documentIndex->setNumQuestions(numQuestions);
}


/**
 * Updates the top fifty elements of the index to a top fifty usable to the user.
 */
void IndexHandler::updateTopFifty() {
    std::vector<IndexedTerm> tops = documentIndex->getTopFifty();

//    std::ostream_iterator<IndexedTerm> out(std::cout, "\n");
//    std::copy(tops.begin(), tops.end(), out);

    std::transform(tops.begin(), tops.end(), std::back_inserter(topFifty),
                   [](const IndexedTerm & it) -> std::string{ return it.getTerm(); });
}


/**
 * Returns the top fifty terms
 */
std::vector<std::string> IndexHandler::getTopFifty() {
    return topFifty;
}


/**
 * Returns the number of terms indexed by the index
 */
int IndexHandler::getNumTerms() const {
    return documentIndex->getTerms();
}

/**
 * Writes the index to a persistent file location in disk
 */
void IndexHandler::writeToDisk() {

    std::string fileName("../index.txt");
    std::ofstream fileOut;

    fileOut.open(fileName.c_str(), std::ios::out);

    //don't forget to check if open and close afterwards
    if(!fileOut.is_open())
        throw std::runtime_error("Failed to open file for persisting index past runtime.");

    fileOut << documentIndex->getNumQuestions() << std::endl;

    //each visit to a node has it being printed to file
    fileOut << *documentIndex;

    fileOut.close();
}


/**
 * Reads the index from a persistent file location in disk
 */
void IndexHandler::readFromDisk() {

    std::string fileName("../index.txt");
    std::ifstream fileIn;

    fileIn.open(fileName.c_str(), std::ios::in);

    if(!fileIn.is_open())
        throw std::runtime_error("The persistent index file failed to open or isn't here.");

    //empty out the index
    if(!documentIndex->isEmpty())
        documentIndex->makeEmpty();

    char bufferIn[50];
    IndexedTerm temp;
    int questionId;
    int frequency;
    int location;

    fileIn >> bufferIn;
    setNumQuestions(atoi(bufferIn));
    fileIn.get();

    //until end of file
    while(fileIn.getline(bufferIn, 50, '|')) {
        //read in term
        temp = IndexedTerm(bufferIn);

        //until new line, read in ID and frequency
        while(fileIn.peek() != '\n' && fileIn.peek() != -1){
            //insert new term to index
            fileIn.getline(bufferIn, 50, '|');
            questionId = atoi(bufferIn);

            temp.addQuestion(questionId);

            fileIn.getline(bufferIn, 50, ',');
            frequency = atoi(bufferIn);

            temp.addFrequency(questionId, frequency);

            fileIn.getline(bufferIn, 50, ',');
            location = atoi(bufferIn);

            temp.addLocation(questionId, location);

            //until end of line or a pipe, read in elements of location vector
            while(fileIn.peek() != '\n' && fileIn.peek() != -1 && fileIn.peek() != '|') {

                fileIn.getline(bufferIn, 50, ',');
                location = atoi(bufferIn);

                temp.addLocation(questionId, location);
            }
            fileIn.get();

        }

        if(!temp.isEmpty())
            documentIndex->insert(temp);

        fileIn.get();
    }

    fileIn.close();
    updateTopFifty();
}
