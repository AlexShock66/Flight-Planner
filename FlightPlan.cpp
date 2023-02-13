//
// Created by Alex Shockley on 11/7/2020.
//

#include "FlightPlan.h"

void FlightPlan::addFlight(Flight f) { // adds a flight to the list of flights
    flights.push_back(f);
}

void FlightPlan::display() { // displays the data in the class with formatting
    cout << "FLIGHT PLAN" <<endl;
    cout << "Total cost: " <<*totalCost <<endl;
    cout << "Total time: " <<*totalTime <<endl;
    for(int i = 0; i < flights.getSize(); i ++) {
        cout << flights[i].getPath().first <<" -> ";
        cout << flights[i].getPath().second <<endl;
    }
    cout <<endl;
}

void FlightPlan::calculateCost() { // calculates the total cost of the entire trip based on instructions in the Project file

    for(int i = 0; i < flights.getSize(); i ++) {

        *totalCost += flights[i].getPrice();
        if(i != 0)
        *totalCost += 19;

    }
}

void FlightPlan::calculateTime() { // calculates total time for entire trip based on instructions
    SString prevAirline = flights[0].getAirline();
    for(int i = 0; i < flights.getSize(); i ++) {
        *totalTime+= flights[i].getTime();
        if(i != 0 )
            *totalTime+= 43;
        if(flights[i].getAirline() != prevAirline)
            *totalTime += 22;
        prevAirline = flights[i].getAirline();
    }
}

FlightPlan::FlightPlan() { // constructor
    totalCost = new double(0);
    totalTime = new double(0);
}



double *FlightPlan::getTotalCost() const { // getters and setters
    return totalCost;
}

void FlightPlan::setTotalCost(double *totalCost) {
    FlightPlan::totalCost = totalCost;
}

double *FlightPlan::getTotalTime() const {
    return totalTime;
}

void FlightPlan::setTotalTime(double *totalTime) {
    FlightPlan::totalTime = totalTime;
}

FlightPlan::FlightPlan(const FlightPlan &f) { // copy constructor
//
    this->totalTime = f.totalTime;
    this->totalCost = f.totalCost;
    this->flights = f.flights;
}

FlightPlan &FlightPlan::operator=(const FlightPlan &copy) { // overloaded = operator

    this->totalTime = copy.totalTime;
    this->totalCost = copy.totalCost;
    this->flights = copy.flights;
    return *this;
}

bool FlightPlan::operator<(const FlightPlan &var) const {
    return *this->totalCost < *var.totalCost;
}

bool FlightPlan::operator>(const FlightPlan &var) const {
    return *this->totalCost > *var.totalCost;
}

ostream &operator<<(ostream &os, const FlightPlan &f) { // ensure we can print out an entire flight plan to make my life easier on outputting to file
    DSList<Flight> temp = f.flights;
    for(int i = 0; i < f.flights.getSize(); i ++) {
        os << temp[i].getPath().first;
        if(i + 1 != f.flights.getSize()) {
            os <<" -> ";
        } else {
            os << " -> "<< temp[i].getPath().second <<". ";
        }
    }

    return os;
}
