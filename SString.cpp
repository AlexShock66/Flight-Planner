//
// Created by Alex Shockley on 9/17/2020.
//

#include "SString.h"
#include "DSVector.h"
//
// Created by Alex Shockley on 9/2/2020.
//

#include <cstring>
#include <iostream>
#include "SString.h"

SString::SString() { // default constructor that assigns base values
    size = 0;
    maxSize = 10;
    data = new char[1];
    data[0] = '\0';
}

SString::SString(char newWord[]) { // overloaded constructor that copies the contents of the passed in char[] into it's data and sets the size to the size of the passed in data

    this->size = strlen(newWord);
    this->data = new char[size + 1];
    for(int i = 0; i < size; i ++) {
        this->data[i] = newWord[i];
    }
    if(maxSize < size){
        this->maxSize = size;
    }
    data[size] = '\0'; // ensure that the null character is present in each Sstring because we are searching for it later on

}

void SString::removePunct() { // function that removes trailing punctuation
    for(int i = size-1; i > 0; i--) { // start at the end of the array and as long as the last character is a punctuation character, continue to remove it
        if(ispunct(data[i]) == 0) {
            break;
        } else {
            data[i] = '\0';
        }
    }
}

char &SString::operator[](int index) { // accessoperator that return the character at some index
    if(index > size){
        std::cout << "----------- INDEX OUT OF BOUNDS ON SSTRING----------" <<std::endl;
        return data[0];
    }
    return data[index];
}

SString::~SString() { // destructor
      delete[] this->data;

}



SString &SString::operator+=(const char *stringToAdd) { // += operator that appends the char array to the end of data and corrects size
    char buffer[size];
    this->size += strlen(stringToAdd);
    strcpy(buffer,data); // copy original data to buffer
    delete[] data;
    data = new char[size];
    strcpy(data,buffer); // copy buffer back to data
    int j = 0;
    for(int i = strlen(data); i < size; i++) { // add whatever string the user passes in to the end of the string
        data[i] = stringToAdd[j];
        j++;
    }
    data[size] = '\0'; // null character as always
    return *this;
}


char *SString::getData() const { // getter
    return this->data;
}

void SString::setString(char *string) { // set string method that deletes the current data and reassigns it based on what is passed in by the user, Updates the size aswell
    if(this->data != nullptr) {
        delete[] this->data;
    }
    data = nullptr;

    this->size = strlen(string);
    this->data = new char[this->size + 1];
    for(int i = 0; i < this->size; i ++) {
        this->data[i] = string[i];
    }
    if(maxSize < size){
        this->maxSize = size;
    }
    data[size] = '\0';

}

int SString::getSize() const {
    return size;
}


SString &SString::operator=(const SString & copy) { // overloaded = operator that assigns the new value a deep copy
    if (this != &copy) {
        if(data != nullptr)delete[] this->data;

        this->size = copy.size;
        this->data = new char[copy.size +1];

        for (int i = 0; i < size + 1; i++) {
            data[i] = copy.data[i];
        }
        data[size] = '\0';
    }

    return *this;
}



bool SString::contains(char *check) { // function that checks if a string is contained within another string, returns true if it is, returns false if it is not

    return strstr(this->data, check);
}

void SString::removeChar(char charToRemove) {
    DSVector<char> newWord;
    for(int i = 0; i < size; i ++) { // create a vector<char> that contains every char accept the charToRemove
        if(data[i] == charToRemove) {
           continue;
        }
        newWord.push_Back(data[i]);
    }
    delete [] data;
    data = new char[newWord.getCurrSize()];
    for(int i = 0; i < newWord.getCurrSize(); i ++) { // refill data with the vector<char> such that it is the original string without the charToRemove
        data[i] = newWord[i];
    }
    data[newWord.getCurrSize()] = '\0'; // be sure to add the null character

}

void SString::removeUntil(char stopChar) {
    char currChar = ' ';
    DSVector<char> newString;
    int stopCharIndex = 0;
    for(int i = 0; i < size; i ++) { // find the index of the char to stop deleting at
        currChar = data[i];
        if( currChar != stopChar) {
            stopCharIndex++;
            continue;

        } else {
            stopCharIndex++;
           break;
        }
    }
    for(int i = stopCharIndex; i < size; i ++) { // copy the string but start at the index as to skip over every char before the stopChar
        newString.push_Back(data[i]);
    }

    size = newString.getCurrSize(); // set the size
        for(int i =0 ; i < size; i ++) { // fill the data with newString
            data[i] = newString[i];
        }

        data[size] = '\0'; // add the null character



}

bool SString::contains(char *check, int startPos) { // more indepth function to check if a string is contained within another string, but it also accepts a starting index so it doesnt have to search the entire string
    int checkSize = 0;
    char test = ' ';
    bool value = false;
    while(test != '\0') {
        test = check[checkSize];
        checkSize++;
    }
    checkSize--;
    for(int i = startPos; i < this->size; i ++) { // iterate through the size of the this->data
        for(int j = 0; j < checkSize; j++) { // iterate through the size of the string passed in
            if(check[j] != this->data[i]) { // check character for character to see if the set of characters is the same, if it gets through the entire word that is passed in, then it returns true
                value = false;
                break;
            } else {
                value = true;
                i++;
            }
        }
        if(value == true) {
            break;
        }
    }
    return value;
}





SString::SString(const SString &copy) { // copy constructor to create a deep copy for use in vectors

    this->maxSize = copy.maxSize;
    this->size = copy.size;
    this->data = new char[size + 1];
    for(int i = 0; i < size; i ++) {
        data[i] = copy.data[i];
    }
    data[size] = '\0';

}

void SString::toUpper() { // convert string to all uppercase
    for(int i = 0; i < size; i ++) {
        data[i] = toupper(data[i]);
    }
}

void SString::toLower() { // convert string to all lowercase
    for(int i =0; i < size; i ++) {
        data[i] = tolower(data[i]);
    }
}

SString SString::wordAt(int counter) { // takes the string and returns a new SString at the index that is passed in
    int z = 0;
    SString realWord = SString();
    if(counter > this->size) return realWord; // if the index is out of bounds, return a blank SString
    for(int i = 0; i <= counter; i++) { // for loop running index amount of times
        int j = 0;
        if(z > strlen(this->data) ) break;
        char word[20];
        char currChar = 'b';
        while (currChar != ' ') { // as long as the character doesnt = ' ', continue "building" the word



            currChar = this->data[z]; // assign the character to the word

            if(currChar != ' ') word[j] = this->data[z];

            j++;
            z++;
        }


        realWord.setString(word); // set the SString to whatever word is present at index counter

        memset(word,0,strlen(word)); // clear the contents of word variable

    }
    return realWord; // return the Sstring that was created using the word at index counter
}

int SString::getNumWords() { // function that counts the number of spaces in an SString and returns that value
    char currChar = ' ';
    int i = 0;
    int wordCount = 0;
    for(int j; j < strlen(this->data); j++) {
        currChar = this->data[i];
        i++;
        if(currChar == ' '){
            wordCount++;
        }
    }
    return wordCount + 1;
}
bool SString::operator <(const SString &var) const { // overloaded < operator
    if(strcmp(data,var.data) < 0) {
        return true;
    } else {
        return false;
    }
}

bool SString::operator>(const SString &var) const{ // overloaded > operator
    if(strcmp(data,var.data) > 0) {
        return true;
    } else {
        return false;
    }
}

bool SString::operator==(const SString &var) const { //overloaded == operator
    if(strcmp(this->data,var.data) == 0) {
        return true;
    } else {
        return false;
    }
}

void SString::moveWordBetweenToFront(char firstChar, char secondChar) { // I am the king of for loops and no one can tell me otherwise
    DSVector<char> wordBetween;
    char currChar = ' ';
    int firstCharIndex = 0;
    int secondCharIndex = 0;
    char oldData[size];

    for(int i = 0; i < size; i++) { // find index of first char
        currChar = data[i];
        if(currChar == firstChar) break;
        firstCharIndex++;
    }
    secondCharIndex = firstCharIndex;
    for(int i = firstCharIndex; i < size; i++) { // find index of the second char
        currChar = data[i];
        if(currChar == secondChar) break;
        secondCharIndex++;
    }
    for(int i = firstCharIndex; i <= secondCharIndex; i ++) { // copy the word between the first and second char to a vector
       if(i == size) break;
       wordBetween.push_Back(data[i]);
    }
    int dataIndex = 0; // keeps track of oldData
    strcpy(oldData,data); // copy over the original data to the char array oldData
    for(int i = 0; i < size; i ++) { // this works because we are not changing the size of the array
        if(i < wordBetween.getCurrSize()) { // if i is < the size of the word between the 2 chars, add the char from wordBetween
            data[i] = wordBetween[i];
        } else { // otherwise copy over the value from the oldData
            data[i] = oldData[dataIndex];
            dataIndex++;
        }
    }

}

bool SString::operator !=(const SString &var) const{ //overloaded != operator
    return strcmp(data, var.data) != 0;
}
