//
// Created by Alex Shockley on 10/29/2020.
//

#include "Flight.h"
 // getters and setters
const pair<City,City> &Flight::getPath() const {
    return path;
}

void Flight::setPath(const pair<City,City> &path) {
    Flight::path = path;
}

double Flight::getPrice() const {
    return price;
}

void Flight::setPrice(double price) {
    Flight::price = price;
}

const SString &Flight::getAirline() const {
    return airline;
}

void Flight::setAirline(const SString &airline) {
    Flight::airline = airline;
}

double Flight::getTime() const {
    return time;
}

void Flight::setTime(double time) {
    Flight::time = time;
}

Flight::Flight(City a, City b, double price, SString airline, double time) { // overloaded const to set values
    pair<City,City> tempPair;
    tempPair.first = a;
    tempPair.second = b;
    this->path = tempPair;
    this->price = price;
    this->airline = airline;
    this->time = time;
}

Flight::Flight() {

}

Flight::Flight(const Flight &a) { // copy constructor to make sure it works in a vector/dsList basically :)
    this->time = a.time;
    this->airline = a.airline;
    this->price = a.price;
    this->path = a.path;
}
