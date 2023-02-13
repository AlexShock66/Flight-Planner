//
// Created by Alex Shockley on 10/28/2020.
//

#ifndef INC_20F_FLT_PLN_STACK_H
#define INC_20F_FLT_PLN_STACK_H
#include "DSList.h"
template<typename TheType>
class Stack {
public:
    Stack<TheType>();
    TheType pop();
    void push(TheType elementToAdd);
    bool isEmpty();
    TheType peek();
    int getSize();
    bool contains(TheType a);
    Stack(const Stack &copy);
private:
DSList<TheType> list;
int size;
};

template<typename TheType>
Stack<TheType>::Stack() { // initialize data members
    size = 0;
    list = DSList<TheType>();
}

template<typename TheType>
bool Stack<TheType>::contains(TheType a) { // check to see if the stack contains a certain value
    bool b = false;
    for(int i = 0; i < list.getSize(); i ++) { // linear search for the data a, if it exists, then return true, otherwise return false
        if(list.at(i) == a) {
            b = true;
            break;
        }
    }
    return b;
}

template<typename TheType>
Stack<TheType>::Stack(const Stack &copy) { // lets me copy the Stack so i can save it by popping
    this->size = copy.size;
    this->list = copy.list;
}

template<typename TheType>
TheType Stack<TheType>::pop() { // remove the top thing on the stack and return it
    TheType a = list[size-1];
    list.pop_Back();
    size--;
    return a;
}

template<typename TheType>
void Stack<TheType>::push(TheType elementToAdd) { // add something to the top of the stack
    list.push_back(elementToAdd);
    size++;
}

template<typename TheType>
bool Stack<TheType>::isEmpty() { // check to see if the stack is empty
    return size == 0;
}

template<typename TheType>
TheType Stack<TheType>::peek() { // return a copy of the data at top of the stack
    if(size != 0) {
        return list[size - 1];
    } else {
        return 0;
    }
}



template<typename TheType>
int Stack<TheType>::getSize() { // returns the stack's size
    return size;
}


#endif //INC_20F_FLT_PLN_STACK_H
