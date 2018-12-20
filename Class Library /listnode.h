#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
using namespace std;



//template <class Object> class LinkedList;

template <typename T>
class ListNode
{
template <typename U>
friend class LinkedList; //establishes LinkedList as friend class
private:
   T data; //data to be stored in node
   ListNode<T>* previous = nullptr; //pointer to previous node in list
   ListNode<T>* next = nullptr; //pointer to next node in list

public:
    ListNode(){
        previous = nullptr;
        next = nullptr;
    } //default constructor

    ListNode(T); //constructor

    ListNode(const ListNode &ListNodeToCopy); //copy constructor
    ~ListNode(){ //destructor resets all pointers
        previous = nullptr;
        next = nullptr;
    }

    ListNode& operator =(const ListNode& ); //assignment operator
    bool operator ==(ListNode); //comparison operator
    bool operator !=(ListNode);
    bool operator <(ListNode);  //comparison operator
    bool operator >(ListNode);  //comparison operator

    T& getData(); //returns data of node
    ListNode<T>*& getNext();
    ListNode<T>*& getPrevious();
    void setData(T); //sets data of node



};
template <typename S>
 ostream& operator <<(ostream& os, const ListNode<S>& List){ //overloaded << operator to print out node
    cout << List.getData() << endl;
    return os;
}
template <typename T>
ListNode<T>::ListNode(const ListNode<T> &ListNodeToCopy){ //copy constructor
    this->data = ListNodeToCopy.data; //copies node data
    this->next = ListNodeToCopy.next; //copies node's next pointer
    this->previous = ListNodeToCopy.previous; //copies nodes's previpus pointer
}

template <typename T>
ListNode<T>& ListNode<T> :: operator =(const ListNode& NodetoCopy){ //assignment operator
    this->data = NodetoCopy.getData(); //copies data from NodetoCopy to node
    this->next = NodetoCopy.next; //copies next pointer from NodetoCopy to node
    this->previous = NodetoCopy.previous; //copies previous pointer from NodetoCopy to node
    return *this;
}
template <typename T>
bool ListNode<T> :: operator ==( ListNode<T> nodeToCompare){ //comparison operator
    if(this->data == nodeToCompare.data && this->previous == nodeToCompare.previous && this->previous == this->next) //checks data next and previous pointer of each node against one another
        return true; //if same return true
    else
        return false; //else false
}
template <typename T>
bool ListNode<T>:: operator !=( ListNode<T> nodeToCompare){ //comparison operator
    return !(*this == nodeToCompare); //calls opposiote result of ==
}

template <typename T>
 ListNode<T>::ListNode(T information){ //constrctor for node intialized with data
    next = nullptr;
    previous = nullptr;
    data = information;
}
template <typename T>
T& ListNode<T>::getData() { //returns data from node
    return data;
}
template <typename T>
ListNode<T>*& ListNode<T>::getNext() { //returns data from node
    return next;
}
template <typename T>
ListNode<T>*& ListNode<T>::getPrevious() { //returns data from node
    return previous;
}



#endif // LISTNODE_H
