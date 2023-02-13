//
// Created by Alex Shockley on 11/7/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHTPLAN_H
#define INC_20F_FLT_PLN_FLIGHTPLAN_H
#include "Flight.h"
#include "DSList.h"
#include <iostream>
using namespace std;
class FlightPlan {
public:
    FlightPlan();

    FlightPlan(const FlightPlan &f);
    void addFlight(Flight f);
    void display();
    void calculateCost();
    void calculateTime();
    FlightPlan& operator=(const FlightPlan &copy);

    double *getTotalCost() const;

    void setTotalCost(double *totalCost);
    friend ostream& operator<<(ostream& os, const FlightPlan& f);
    double *getTotalTime() const;
    bool operator<(const FlightPlan &var) const;
    bool operator>(const FlightPlan &var) const;
    void setTotalTime(double *totalTime);

private:
    DSList<Flight> flights;
    double *totalCost;
    double *totalTime;

};


#endif //INC_20F_FLT_PLN_FLIGHTPLAN_H
