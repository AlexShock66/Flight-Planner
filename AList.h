//
// Created by Alex Shockley on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_ALIST_H
#define INC_20F_FLT_PLN_ALIST_H
#include "DSList.h"
using namespace std;
template<typename TheType>
class AList { // Adjacency list
public:
    AList();
    TheType getMainNode(int index);
     DSList<TheType>& getAdjNodes(TheType nodeToFind);
    void pushMain(TheType nodeToAdd);
    void pushAdj(TheType mainNode, TheType nodeToAdd);
    void printList();
    bool contains(TheType check);
    int getSize() const;
    int find(TheType a);
    void moveItr(TheType nodeToFind);
    void resetItr(TheType nodeToFind);
    bool isItrNull(TheType nodeToFind);
    ~AList();
private:
    int size;
    DSList<pair<TheType,DSList<TheType> *>> list;
};

template<typename TheType>
AList<TheType>::AList() { // default constructor that assigns size to 0
    list = DSList<pair<TheType,DSList<TheType> *>>();
    size = 0;
}

template<typename TheType>
AList<TheType>::~AList() {
    for(int i = 0; i < size; i ++) {
        delete list[i].second;
    }
}

template<typename TheType>
TheType AList<TheType>::getMainNode(int index) { // returns the main node at some index
    return list[index].first;
}



template<typename TheType>
int AList<TheType>::getSize() const { // returns the size of the AList (Note: the size is the number of main nodes not number of total nodes)
    return size;
}



template<typename TheType>
void AList<TheType>::pushMain(TheType nodeToAdd) { // Function that adds a new main node of TheType to the AList
    if(!contains(nodeToAdd)) { // My implimentation only contains unique main nodes, no duplicates allowed
        pair<TheType, DSList<TheType> *> temp;
        TheType a = nodeToAdd;
        auto *adjList = new DSList<TheType>(); // create new list on the heap
        temp.first = nodeToAdd;
        temp.second = adjList; // assign the pair
        list.push_back(temp); // push back the pair to the main list
        size++; // incriment size (Idk how to spell that word so :/ )
    }

}

template<typename TheType>
void AList<TheType>::pushAdj(TheType mainNode, TheType nodeToAdd) { // pushes a node to the adjacent list of a given main node
    int indexOfMain = -1;
    for(int i = 0; i < list.getSize(); i ++) { // forloop to find the index of the main node
        if(list[i].first == mainNode) {
            indexOfMain = i;
            break;
        }
    }
    if(indexOfMain == -1) { // if the index is out of bounds, tell user
        cout << "-----------------ERROR: MAIN NODE NOT FOUND-------------" <<endl;
        return;
    }
    list[indexOfMain].second->push_back(nodeToAdd); // the node to add back to the list attached to the main node at the index

}

template<typename TheType>
 DSList<TheType>& AList<TheType>::getAdjNodes(TheType nodeToFind) { // returns the list of nodes attached to a given main node
    int indexOfNode = -1;
    for(int i = 0; i < list.getSize(); i ++) { // forloop to find the index of the main node
        if(list[i].first == nodeToFind) {
            indexOfNode = i;
            break;
        }
    }
    if(indexOfNode == -1) {
        cout << "-----------------ERROR: MAIN NODE NOT FOUND-------------" <<endl; // if it's out of bounds, tell user
        return *list[0].second;
    } else {
        return *list[indexOfNode].second; // otherwise, return the list that is attached to nodeToFind
    }
}

template<typename TheType>
void AList<TheType>::printList() { // print function for debugging that prints in the format: MainNode: (All attached nodes) \n
    cout << "-------------- ALIST CONTENTS------------------" <<endl;
    for(int i = 0; i < list.getSize(); i ++) {
        cout << list[i].first << ": ";

        for(int j = 0; j < list[i].second->getSize(); j ++) {

            cout << list[i].second->at(j);
            if(j == list[i].second->getSize() - 1) {
                cout <<endl;
            } else {
                cout <<", ";
            }
        }

    }
}

template<typename TheType>
bool AList<TheType>::contains(TheType check) { // bool function to check if a main node is contained in the aList already
    bool contains = false;
    for(int i =0; i < size; i++) {
        if(list[i].first == check) {
            contains = true;
            break;
        }
    }

    return contains;
}

template<typename TheType>
int AList<TheType>::find(TheType a) { // returns the index of a given main node
    int index = -1;
    for(int i = 0;i < size; i++) {
        if(list[i].first == a) {
            index = i;
            break;
        }
    }
    return index;
}

template<typename TheType>
void AList<TheType>::moveItr(TheType nodeToFind) { // moves the iterator of the given mainNode's attached linkedList to the next value
    int indexOfNode = -1;
    for(int i = 0; i < list.getSize(); i ++) { // for loop to find the index of the main node
        if(list[i].first == nodeToFind) {
            indexOfNode = i;
            break;
        }
    }
    if(indexOfNode == -1) {
        cout << "-----------------ERROR: MAIN NODE NOT FOUND IN MOVE ITR FUNCT-------------" << endl;
    }
    list[indexOfNode].second->moveItr();
}

template<typename TheType>
void AList<TheType>::resetItr(TheType nodeToFind) { // function that resets the iterator of a given main node
    int indexOfNode = -1;
    for(int i = 0; i < list.getSize(); i ++) { // forloop to find the index of the main node (In hienzSight I ptobably should have just used find() but I'm too dumb for that :P)
        if(list[i].first == nodeToFind) {
            indexOfNode = i;
            break;
        }
    }
    if(indexOfNode == -1) {
        cout << "-----------------ERROR: MAIN NODE NOT FOUND IN RESET ITR FUNCT-------------" << endl;
    }
    list[indexOfNode].second->resetItr();
}

template<typename TheType>
bool AList<TheType>::isItrNull(TheType nodeToFind) { // checks if the iterator is null at a given main node
    int indexOfNode = -1;
    for(int i = 0; i < list.getSize(); i ++) { // same for loop...
        if(list[i].first == nodeToFind) {
            indexOfNode = i;
            break;
        }
    }
    if(indexOfNode == -1) {
        cout << "-----------------ERROR: MAIN NODE NOT FOUND IN ISITRNULL FUNCT-------------" << endl;
    }
    return list[indexOfNode].second->isIteratorNull();
}

#endif //INC_20F_FLT_PLN_ALIST_H
