#ifndef STACK_H
#define STACK_H
#include <../../lib/linkedlist.h>
template <typename T>
class Stack{
private:
    LinkedList<T> List; //LinkedList backbone of stack
public:
    Stack(){} //default constructor
    Stack(const Stack&); //copy constructor
    Stack& operator =(const Stack); //assignment operator
    ~Stack(){}//default destructor

    void push(T); //method to add things to top of stack
    T pop();//method to remove last object from stack and return it
    bool search(T); //searches stack to determine if object is on it
    T peek(); //returns top object of stack without removing it
    bool isEmpty(); //checks to see if stack is empty
    bool operator ==( Stack<T>); //comparison operator
    bool operator !=( Stack<T>); //comparison operator
};
template <typename T>
Stack<T>::Stack(const Stack &stackToCopy){ //copy constructor
    this->List = stackToCopy.List; //copies list from stack object to this
}
template <typename T>
Stack<T>& Stack<T>::operator =(const Stack stackToCopy){ //assignment operator
    this->List = stackToCopy.List; //copies list to this
    return *this; //returns this pointer
}
template <typename T>
void Stack<T>::push(T element){ //adds element to top of stack
    List.insert(element); //insets element at end of list
}
template <typename T>
T Stack<T>::pop(){ //removes and returns last object in stack
    return List.pop(); //calls LinkedList pop method
}
template <typename T>
bool Stack<T>:: search(T element){ //searchs stack for element
    return List.search(element); //calls LinkedList search method
}
template <typename T>
T Stack<T>::peek(){ //returns last object in list without removing it
    return List.getLast().getData(); //returns data from list's last pointer
}
template <typename T>
bool Stack<T>::isEmpty(){ //checks if stack is empty
    return List.isEmpty(); //calls List isEMpty method
}
template <typename T>
bool Stack<T>::operator ==(Stack<T> stackToCompare){ //comparison operator
   Stack<T> * stack2 = new Stack<T>; //temporary stack
   stack2 = this; //copies this stack to stack2
    while(true){ //infinite loop
    if(stack2->isEmpty() && stackToCompare.isEmpty()){ //if both empty
       delete stack2;
        return true; //return true
    }
    if(stack2->isEmpty()  && !stackToCompare.isEmpty()){ //if one is empty and other not
        delete stack2;
        return false; //return false
    }
    if(!stack2->isEmpty()  && stackToCompare.isEmpty()){ //if one is empty and other not
        delete stack2;
        return false; //return false
    }
    else {
        T thisData = stack2->pop(); //pops off data of stack 2
        T stackToCompareData = stackToCompare.pop(); //pops off data of stackTo compare
        if(thisData == stackToCompareData){ //if data is same, continue loop

            continue;
        } else{ //else return false
            delete stack2;
            return false;
        }
    }
    }
}
template <typename T>
bool Stack<T>::operator !=(Stack<T> stackToCompare){//comaprison operator
    return !(*this == stackToCompare); //calls == and negates it
}

#endif // STACK_H
