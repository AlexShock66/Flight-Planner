//
// Created by Alex Shockley on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHTPLANNER_H
#define INC_20F_FLT_PLN_FLIGHTPLANNER_H
#include "SString.h"
#include "Stack.h"
#include "AList.h"
#include "DSList.h"
#include "City.h"
#include "Flight.h"
#include <iostream>
#include<fstream>
#include <sstream>
#include <cstring>
#include "DesiredFlight.h"
#include "FlightPlan.h"
using namespace std;
class FlightPlanner {
public:
    FlightPlanner();
    ~FlightPlanner();
    void run();
    void setInputFile(char* fileName);
    void setOutputFile(char* fileName);
    void generateFlightList();
    void setHandleFile(char* fileName);
    void generateDesiredFlights();
    void printDesiredFlights();
    void outputFlights(int i);
    void printFlights();
    void saveFlightPath(Stack<City> stack);
    void sortByTime();
    void sortByCost();
    void generatePlans();
    void printCorrectFlights();
    void outputToFile(int i);
private:
    AList<City> aList;
    DSList<FlightPlan> plans;
    ofstream fout;
    ifstream input;
    ifstream input2;
    DSList<Flight> flights;
    DSList<DesiredFlight> desiredFlights;
    DSList<DSList<City>> correctFlights;
    DSList<pair<double,FlightPlan>> costSort;
    DSList<pair<double,FlightPlan>> timeSort;



};


#endif //INC_20F_FLT_PLN_FLIGHTPLANNER_H
