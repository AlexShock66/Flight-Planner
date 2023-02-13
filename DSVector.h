//
// Created by Alex Shockley on 9/27/2020.
//
#include<iostream>
#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H
template<typename TheType>
class DSVector {
private:
    TheType *data;
    int currSize;
    int maxSize;
    void quickSort(DSVector<TheType> &vectorToSort, int low, int high);
    int partition(DSVector<TheType> &vectorToSort, int low, int high);
public:
    DSVector();
    ~DSVector();
    void push_Back(TheType newData);
    TheType &operator[](int index);
    DSVector<TheType> & operator=(const DSVector<TheType> copyList);
    DSVector(const DSVector &newList);
    int getCurrSize() const;
    void setCurrSize(int currSize);
    int getMaxSize() const;
    void setMaxSize(int maxSize);
    void sort();
    void removeAtIndex(int index);
    void print();
    void swap(int firstIndex, int secondIndex);
};

template<typename TheType>
DSVector<TheType>::DSVector() { // assign base values
    data = new TheType[10];
    currSize = 0;
    maxSize = 10;
}

template<typename TheType>
DSVector<TheType>::~DSVector() { // clear data
    delete[] data;
}

template<typename TheType>
void DSVector<TheType>::push_Back(TheType newData) {
    if(currSize + 1 > maxSize) { // if adding the value will be out of bounds, create a new array that is 2 times as big, copy the old array over and delete the original array
        maxSize *= 2;
        TheType *updatedArray = new TheType[maxSize];
        for (int i = 0; i < currSize; i++) {
            updatedArray[i] = data[i];
        }
        delete[] data;
        data = updatedArray;
    } //assign the value to the array at size and increment size
    data[currSize] = newData;
    currSize++;
}

template<typename TheType>
TheType &DSVector<TheType>::operator[](int index) { // access, if its out of bounds, let the user know with cout and return the first element in the list
    if(index >= currSize) {
        std::cout << "---------------INDEX OUT OF BOUNDS IN DSVECTOR CLASS-------------" << std::endl;
        return data[0];
    }
    return data[index];
}

template<typename TheType>
DSVector<TheType> &DSVector<TheType>::operator=(const DSVector<TheType> copyList) {
     // create a deep copy of the list and return this
    delete[] this->data;
    this->maxSize = copyList.maxSize;
    this->currSize = copyList.currSize;
    data = new TheType[maxSize];
    for(int i = 0; i < currSize; i ++) {
        data[i] = copyList[i];
    }
    return *this;
}

template<typename TheType>
int DSVector<TheType>::getCurrSize() const {
    return currSize;
}

template<typename TheType>
void DSVector<TheType>::setCurrSize(int currSize) {
    DSVector::currSize = currSize;
}

template<typename TheType>
int DSVector<TheType>::getMaxSize() const {
    return maxSize;
}

template<typename TheType>
void DSVector<TheType>::setMaxSize(int maxSize) {
    DSVector::maxSize = maxSize;
}

template<typename TheType>
DSVector<TheType>::DSVector(const DSVector &newList) { // copy constructor that deep copies the copyList
    currSize = newList.currSize;
    maxSize = newList.maxSize;
    data = new TheType[maxSize];
    for(int i = 0; i < currSize; i ++) {
        data[i] = newList[i];
    }
}

template<typename TheType>
void DSVector<TheType>::sort() { // also a fun one :)
    quickSort(*this,0,currSize - 1);
}

template<typename TheType>
void DSVector<TheType>::removeAtIndex(int index) { // remove a value at some index by copying over it and decrementing size
    for(int i = index; i < currSize - index; i ++) {
        data[i] = data[i+1];
    }
    currSize--;
}

template<typename TheType>
void DSVector<TheType>::print() { // print the array to the console
    for(int i = 0; i < currSize; i ++) {
        std::cout << data[i] << ", " ;
    }
    std::cout << std::endl;
}

template<typename TheType>
void DSVector<TheType>::swap(int firstIndex, int secondIndex) { // function to swap two values by passing in the indexs of the values that you want to swap
    TheType firstValue = data[firstIndex];
    TheType secondValue = data[secondIndex];
    data[firstIndex] = secondValue;
    data[secondIndex] = firstValue;
}

template<typename TheType>
void DSVector<TheType>::quickSort(DSVector<TheType> & vectorToSort, int low, int high) { // fun part :)

    if(low < high) { // if the start pos is less than the end pos, run this
        int partitionIndex = partition(vectorToSort,low,high); // put the pivot in the correct place and return the index of the pivot

        quickSort(vectorToSort,low,partitionIndex - 1); // recursivly sort the left half of the array
        quickSort(vectorToSort,partitionIndex + 1, high); // recursively sort the right half of the array
    }
}

template<typename TheType>
int DSVector<TheType>::partition(DSVector<TheType> &vectorToSort, int low, int high) {
    TheType pivot = vectorToSort[high]; // set the right most value as the pivot
    int i = low - 1; // keeps track of where to put the value
    for(int j = low; j < high; j++) { // iterate through starting at the low and finishing at the high
        if(vectorToSort[j] < pivot) { // if the value at j is < pivot, swap the value at j with the value at i
            i++;
            swap(i, j);
        }
    }
    swap(i+1,high); // finally, swap the pivot to where it belongs in the list
    return i + 1; // return the index of the pivot

}



#endif //INC_20F_AUTO_IDX_DSVECTOR_H
