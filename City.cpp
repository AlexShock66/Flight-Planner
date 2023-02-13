//
// Created by Alex Shockley on 10/27/2020.
//

#include "City.h"
#include <cstring>

City::City() { // constructyor that defaults to setting the name to a space
name = SString(" ");
beenHere = false;
}

City::City(char *newName) { // getters and setters
    name = SString(newName);
}

char* City::getName() {
    return name.getData();
}

void City::setName(char *newName) {
name = SString(newName);
}

ostream &operator<<(ostream &os, const City &c) { // overloaded << operator for outputting city names
    os << c.name.getData();
    return os;
}

bool City::operator==(const City &var) const { // need to be able to compare cities, so we compare their names
    return strcmp(this->name.getData(), var.name.getData()) == 0;
}

bool City::isVisited() {
    return beenHere;
}

void City::visit() {
    beenHere = true;
}

void City::unVisit() {
    beenHere = false;
}

City::City(const City &copy) { // make sure when we copy a city, its values get copied as well
    this->beenHere = copy.beenHere;
    this->name = copy.name;
}

City &City::operator=(const City &copy) {
    if(*this == copy) return *this;
    this->beenHere = copy.beenHere;
    this->name = copy.name;
    return *this;
}
