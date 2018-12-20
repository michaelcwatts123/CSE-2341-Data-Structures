#ifndef ENTRY_H
#define ENTRY_H
#include <../../lib/michaelString.h>
#include <../../lib/michaelvectors.h>

class entry
{
public:
    entry(int &, michaelString &); //constructor
    entry(); //default constructor
    entry(const entry&); //copy constructor
    entry& operator =(const entry& ); //assignment operator

    michaelVector<int> getPageNumbers();

    michaelString getWord() const; //returns entry word

    friend ostream& operator <<(ostream& os, const entry&); // overloaded stream insertion operator

    bool operator ==(const entry); //overloaded equality operator
    bool operator >(const entry&);  //overloaded greater than operator

    char firstLetter(); //returns first letter of word

    void addToNum(int); //adds int to pageNumbers michaelVector


private:
    michaelString word; //word of the entry
     michaelVector<int> pageNumbers; //michaelVector holding all page numbers for word

friend ostream& operator <<(ostream& os, const entry& ent){ //overloaded << operator for display

        os << ent.word << ":";
        for (int i = 0; i < ent.pageNumbers.getLength(); i++){

           os << ent.pageNumbers[i] << " ";
        }
        os << endl;
        return os;
    }

};

#endif // ENTRY_H
