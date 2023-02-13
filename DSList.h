#include <iostream>//
#include "DSVector.h"
// Created by Alex Shockley on 9/17/2020.
//

#ifndef INC_20F_AUTO_IDX_DSLIST_H
#define INC_20F_AUTO_IDX_DSLIST_H
template<typename TheType>
struct Node { // node struct
    TheType data;
    Node<TheType> *next;
    Node<TheType> *prev;
    Node(TheType data) {
        next = nullptr; // assign pointers to nullptr and data to whatever is passed in
        prev = nullptr;
        this->data = data;
    }
    Node(const Node &a) {
        this->data = a.data;
        this->prev = a.prev;
        this->next = a.next;
    }
};
template<typename TheType>
class DSList {
public:
    DSList();
    ~DSList();
    DSList(const DSList &newList);
    DSList<TheType> & operator=(const DSList<TheType> copyList);
    void push_back(TheType value);
    void pop_Front();
    void pop_Back();
    void deleteAtIndex(int index);
    TheType operator[](int index);
    int getSize() const;
    void sort();
    void setSize(int size);
    void print();
    void clear();
    TheType at(int index);
    bool contains(TheType a);
    void remove(TheType a);
    TheType getNext();
    void clearIterator();
    void moveItr();
    void resetItr();
    bool isIteratorNull();
    int getNodeNumber() const;

    void setNodeNumber(int nodeNumber);

    class iterator {
        friend class list;
    private:
        Node<TheType> *nodePtr;
        // The constructor is private, so only our friends
        // can create instances of iterators.

    public:
        iterator() : nodePtr(nullptr) {}
        iterator(Node<TheType> *newPtr) : nodePtr(newPtr) {}

        bool operator!=(const iterator& itr) const {
            return nodePtr != itr.nodePtr;
        }
        bool operator==(nullptr_t) {
            return nodePtr == nullptr;
        }
        // Overload for the dereference operator *
        TheType& operator*() const {
            return nodePtr->data;
        }


        iterator operator++(int) {
            iterator temp = *this;
            nodePtr = nodePtr->next;
            return temp;
        }
    };

    iterator begin() const {
        return iterator(this->head);
    }

    iterator end() const {
        return iterator(this->tail);
    }


private:
    void mergeSort(DSList<TheType> &list);
    void merge(DSList<TheType> &list, DSList<TheType> &leftList, DSList<TheType> &rightList);
    int size;
    Node<TheType> *head;
    Node<TheType> *tail;
    Node<TheType> *curr;
    int nodeNumber;
    iterator itr;


public:

    void setItr(const iterator &itr);
};



template<typename TheType>
int DSList<TheType>::getSize() const {
    return size;
}

template<typename TheType>
void DSList<TheType>::setSize(int size) {
    DSList::size = size;
}

template<typename TheType>
DSList<TheType>::DSList() { // assign base values
    size = 0;
    nodeNumber = 0;

    head = nullptr;
    tail = nullptr;
    curr = nullptr;
}

template<typename TheType>
bool DSList<TheType>::isIteratorNull() {
    return itr == nullptr;
}

template<typename TheType>
TheType DSList<TheType>::getNext() {
    return *itr;
}

template<typename TheType>
void DSList<TheType>::clearIterator() {
    nodeNumber = 0;
}

template<typename TheType>
DSList<TheType>::~DSList() { // remove values for the entire size of the list
    for(int i = 0; i < size; i ++) {
        pop_Front();
    }
}

template<typename TheType>
void DSList<TheType>::moveItr() {
    if(itr != nullptr)
    itr++;
}

template<typename TheType>
void DSList<TheType>::resetItr() {
    itr = this->begin();
}

template<typename TheType>
void DSList<TheType>::remove(TheType a) {
    int index = 0;
    for(int i = 0; i < size; i ++) {
        if(this->at(i) == a) {
            index = i;
            break;
        }
    }

    this->deleteAtIndex(index);
}

template<typename TheType>
DSList<TheType>::DSList(const DSList &newList) { // deep copy of copyList
    Node<TheType> *temp = newList.head;
    size = 0;
    head = nullptr;
    tail = nullptr;
    this->nodeNumber = newList.nodeNumber;
    while(temp != nullptr) {
        this->push_back(temp->data);
        temp = temp->next;
    }
    this->itr = newList.itr;


}
template<typename TheType>
void DSList<TheType>::push_back(TheType value) { // add a node to the end of the list and increment size
    Node<TheType> *newNode = new Node<TheType>(value);
    if(head == nullptr) { // if the list is empty
        head = newNode;
        tail = newNode;
        this->size++;
        itr = this->begin();
    } else { // if its not empty
        Node<TheType> *curr = head;
        while(curr->next != nullptr) { // find where the list ends
            curr = curr->next;
        }

        curr->next = newNode;
        newNode->prev = curr;
        this->size++;
        tail = newNode;
    }
}
template<typename TheType>
TheType DSList<TheType>::operator[](int index) { // access operator
    if(index > this->size - 1) { // if its out of bounds, return the first element in the list and cout a notice
        std::cout << "INDEX OUT OF BOUNDS IN DSLIST" <<std::endl;
        return head->data;
    } else { // otherwise, return the value of the node at the index
        Node<TheType> *currNode;
        currNode = head;
        for(int i = 0; i < index; i++) {
            currNode = currNode->next;
        }
        return currNode->data;

    }

}

template<typename TheType>
TheType DSList<TheType>::at(int index) {
    if(index > this->size - 1) { // if its out of bounds, return the first element in the list and cout a notice
        std::cout << "INDEX OUT OF BOUNDS IN DSLIST" <<std::endl;
        return head->data;
    } else { // otherwise, return the value of the node at the index
        Node<TheType> *currNode;
        currNode = head;
        for(int i = 0; i < index; i++) {
            currNode = currNode->next;
        }
        return currNode->data;

    }
}

template<typename TheType>
void DSList<TheType>::pop_Back() { // remove the last node in the list
    if(tail->prev == nullptr) { // if the list is of size 1 just delete the only node and set tail to nullptr
        delete tail;
        tail = nullptr;
        size--;
    } else { // otherwise, find where the end of the list is and remove that value and reassign tail to the previous node. also unlink it from the list
        Node<TheType> *nodeToDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete nodeToDelete;
        size--;
    }
    if(size == 0) {
        head = nullptr;
        tail = nullptr;
    }
}

template<typename TheType>
void DSList<TheType>::pop_Front() { // same as pop_back but for the first value in the list
    if(head == nullptr) return; // if the list is empty, then do nothing
    if(head->next != nullptr) {// if the list is more than 1 element, then delete the first node, and reassign the head pointer as well as unlink the old first node from the list.
        Node<TheType> *nodeToDelete = head;
        head = head->next;
        head->prev = nullptr;
        delete nodeToDelete;
        size--;
    } else {  // if the list is only one element long, delete the one element and reassign head
        head = nullptr;
        size--;
    }

}

template<typename TheType>
void DSList<TheType>::deleteAtIndex(int index) { // delete a node at some index
    if(index > size){
        return;
    } else if(index == 0) { //treat it like pop front if the index is 0
        pop_Front();
    }else if(index == size - 1) { // if the index is the end, treat it like pop back
        pop_Back();
    } else { // otherwise determine where the node is in the list, unlink it and delete it, and reduce the size
        curr = head;

        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        size--;
        delete curr;
    }
}

template<typename TheType>
DSList<TheType> &DSList<TheType>::operator =(const DSList<TheType> copyList) { // deep copy the copyList to this
    Node<TheType> *temp = copyList.head;
    while(temp != nullptr) {
        this->push_back(temp->data);
        temp = temp->next;
    }
    this->nodeNumber = copyList.nodeNumber;
    this->itr = copyList.itr;
    return *this;
}

template<typename TheType>
void DSList<TheType>::sort() { // Oh this one is fun :)
    mergeSort(*this);
}

template<typename TheType>
void DSList<TheType>::mergeSort(DSList<TheType> &list) { // recursive function to merge sort the list that is passed in
    int sortSize = list.size;

    int middleIndex = sortSize/2; // find the middle
    if(sortSize != 1) { // base case because list of size 1 is technically sorted

        DSList<TheType> rightList;
        DSList<TheType> leftList;

        for(int i = 0; i < middleIndex; i++) { // fill the left list with all the values to the left of the middleIndex
            leftList.push_back(list[i]);
        }
        for(int i = middleIndex; i < sortSize; i++) { //fill the right list with all the values to the right of the middleIndex
            rightList.push_back(list[i]);
        }
        mergeSort(leftList); // recursivly mergeSort the left list
        mergeSort(rightList); // recursivly mergeSort the right list
        merge(list,leftList,rightList); // merge the two lists together
    }
}
template<typename TheType>
void DSList<TheType>::merge(DSList<TheType> &list, DSList<TheType> &leftList, DSList<TheType> &rightList) {
    list.clear(); // clear the original list

    while(leftList.getSize() > 0 && rightList.getSize() > 0) { // as long as neither left or right list is empty, keep comparing them and adding the lower value back into list and removing that value from the left or right list
        TheType leftListItem = leftList[0];
        TheType rightListItem = rightList[0];
        if(leftListItem < rightListItem) {
            list.push_back(leftList[0]);
            leftList.pop_Front();
        } else {
            list.push_back(rightList[0]);
            rightList.pop_Front();
        }
    }

    while(leftList.getSize() > 0) { // if the left list still had values, add them all to list
        list.push_back(leftList[0]);
        leftList.pop_Front();
    }
    while(rightList.getSize() > 0) { // if the right list still has values, add them all to list *** NOTE *** only one of these while loops will run on each iteration
        list.push_back(rightList[0]);
        rightList.pop_Front();
    }

}

template<typename TheType>
void DSList<TheType>::print() { // prints out the values contained in the list
    Node<TheType> *currNode = head;
    for(int i = 0; i < size; i ++) {
        std::cout << currNode->data <<", ";
        currNode = currNode->next;
    }
    std::cout << std::endl;

}

template<typename TheType>
void DSList<TheType>::clear() { // removes all values from the list by calling pop_back size times
    for(int i = size; i >0; i --) {

        pop_Back();
    }

}

template<typename TheType>
bool DSList<TheType>::contains(TheType a) {
    bool found = false;
    for(int i = 0; i < size; i ++) {
        if(this->at(i) == a) {
            found = true;
            break;
        }
    }
    return found;
}

template<typename TheType>
int DSList<TheType>::getNodeNumber() const {
    return nodeNumber;
}

template<typename TheType>
void DSList<TheType>::setNodeNumber(int nodeNumber) {
    DSList::nodeNumber = nodeNumber;
}




template<typename TheType>
void DSList<TheType>::setItr(const DSList::iterator &itr) {
    DSList::itr = itr;
}


#endif //INC_20F_AUTO_IDX_DSLIST_H


