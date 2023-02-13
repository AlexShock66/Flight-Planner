//
// Created by Alex Shockley on 10/27/2020.
//

#ifndef INC_20F_FLT_PLN_CITY_H
#define INC_20F_FLT_PLN_CITY_H
#include "SString.h"
#include <iostream>
using namespace std;
class City { // basically a wrapper class for SString
private:
SString name;
bool beenHere;
public:
    City();
    City(char* newName);
    char* getName();
    void setName(char* newName);
    friend ostream& operator<<(ostream& os, const City& c);
    bool operator==(const City &var) const;
    bool isVisited();
    void visit();
    void unVisit();
    City(const City &copy);
    City& operator=(const City &copy);




};


#endif //INC_20F_FLT_PLN_CITY_H
