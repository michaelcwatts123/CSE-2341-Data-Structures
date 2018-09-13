#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "listnode.h"
#include <iostream>
template <typename T>
class LinkedList
{
private:
    ListNode<T> * first = nullptr; //points to first element of linkedList
    ListNode<T> * last = nullptr; //points to last element of linked list
    ListNode<T> * current = nullptr; //points to any element of linked list
public:
    LinkedList(){ //default constructor sets all pointers to null
        this->first = nullptr;
        this->last = nullptr;
        this->current = nullptr;
    }

    LinkedList(const LinkedList &LinkedListToCopy); //copy constructor

    ~LinkedList(){ //destructor resets all pointers

      first = nullptr;
      current = nullptr;
      last  = nullptr;
    }

    LinkedList& operator =(const LinkedList& ); //assignment operator


    void insert(T data); //inserts element into LinkedList
    void remove(T data); //removes an element from the LinkedList by data
    bool search(T); //searches LinkedList to determine if element is in it
    bool operator ==(const LinkedList&);
    T pop(); //returns and removes final element of list
    bool isEmpty(); //checks if List is empty
    void print(); //prints out content of list

    ListNode<T>& getCurrent(); //returns current pointer
    ListNode<T>& getFirst(); //returns first pointer
    ListNode<T>& getLast(); //returns last pointer
    void interate();
    void reset(); //sets the current pointer to the first element in the list
};

template <typename T>
bool LinkedList<T>:: operator ==(const LinkedList<T>& listToCompare){ //comparison operator

    if(this->first == listToCompare.first && this->last == listToCompare.last){ //compares list to see if pointers are the same
        return true;
    } else {
        return false;
    }
}
//-----------------------------------------------------------------------------------------------------------


template <typename T>
LinkedList<T>& LinkedList<T> ::operator =(const LinkedList<T>& List){ //assignment operators
    if(*this == List){ //checks if elements are the same
        return *this; //returns this pointer if they are
    } else { //sets all pointers of this object equal to pointers of list object
        this->first = List.first;
        this->current = List.current;
        this->last = List.last;
        return *this;
    }
}
template <typename T>
T LinkedList<T>:: pop(){ //removes and returns last element
    T item;
    if (!isEmpty()){ //confirms list is not empty of elements
     item = last->getData();
    if(last != first){ //check to see if only one element is in list
    last->previous->next = nullptr; //removes last element from list
    last = last->previous; //moves last pointer
    } else {
        first = nullptr;
        last = nullptr;
    }
    return item; //returns last element of list
    }
    else {
        return item; //returns empty T type item if list is empty
    }

}

template <typename T>
LinkedList<T> :: LinkedList(const LinkedList &LinkedListToCopy){
    if(*this == LinkedListToCopy){ //checks if elements are the same

    } else { //sets all pointers of this object equal to pointers of list object
        this->first = LinkedListToCopy.first;
        this->current = LinkedListToCopy.current;
        this->last = LinkedListToCopy.last;

    }

}
template <typename T>
bool LinkedList<T>::search(T itemToCheck){ //searches list for specific item
    reset(); //resets current pointer to first
    while(current->next!=nullptr){ //iterates through entire list
        if(current->getData() == itemToCheck){ //checks if data of node equals search item
            return true; //if so return true
        } else {
            current = current->next; //else iterates to next node
        }
    }
    return false; //if loop ends, returns false
}

template <typename T>
void LinkedList<T>::insert(T data){ //function to insert into linkedList

    if (this->isEmpty()){ //checks if List is empty

        first = new ListNode<T> (data); //if so adds new node to front
        first->previous = nullptr;
        first->next = nullptr;
        last = first; //sets last pointer to first


    } else {
        while(last->next!=nullptr){ //iterates last pointer to end of list
            last = last->next;
        }
        current = last; //sets current pointer to last
        last->next =  new ListNode<T> (data); //adds new node to end of list
        last = last->next; //moves last pointer
        last->previous = current;
        last->next = nullptr; //sets next pointer of last to null



    }
}
template <typename T>
void LinkedList<T>::remove(T data){ //removes node containing data
        if(!isEmpty()){ //first checks if list is empty
        reset(); //sets current pointer to first
        while(current->next!=nullptr){
            if(current->getData() == data){
                break;
            } else {
                current = current->next;
            }
        }
        if(current == first){
            current->next->previous = nullptr;
            first = current->next;
        } else{
        if (current == last){
            current->previous->next = nullptr;
            last = current->previous;
        } else {
        current->previous->next = current->next;
        current->next->previous = current->previous;
        }
        }

        }
        current = first;
}
template <typename T>
bool LinkedList<T>::isEmpty(){ //checks if list is empty
    if (this->first == nullptr && this->last == nullptr){ //if both first and last pointer point to null return true
        return true;
    } else { //else false
        return false;
    }
}

template <typename T>
void LinkedList<T>::print(){ //prints out contents of list
    this->reset(); //resets current pointer to top of the list


    while(this->current->next !=nullptr){ //checks to see if at end of list to stop
       cout << this->current->getData() << endl; //prints out node current pointer points to
       this->current = this->current->next; //moves current pointer to next node
   }
     cout << this->current->getData() << endl; //prints last node
}
template <typename T> //sets current pointer to first pointer
void LinkedList<T>::reset(){
   this->current = this->first;
}
template <typename T>
ListNode<T>& LinkedList<T>::getCurrent(){ //returns the current pointer
    return *current;
}
template <typename T>
ListNode<T>& LinkedList<T>::getFirst(){ //returns the first pointer
    return *first;
}
template <typename T>
ListNode<T>& LinkedList<T>::getLast(){ //returns the last pointer
    return *last;
}
template <typename T>
void LinkedList<T>::interate(){ //sets current pointer to current's next
    if(!(current==last)){ //if at end of list, leaves current where it is
        current = current->next;
    }
}
template <typename S>
 ostream& operator <<(ostream& os, const LinkedList<S>& List){ //overloaded << operator to print out node
    cout << List.getData() << endl;
    return os;
}
#endif // LINKEDLIST_H
