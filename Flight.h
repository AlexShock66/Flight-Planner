//
// Created by Alex Shockley on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHT_H
#define INC_20F_FLT_PLN_FLIGHT_H

#include "City.h"
#include "SString.h"
using namespace std;
class Flight { // wrapper class that contains all the info for one given flight in the input file
public:
    const pair<City,City> &getPath() const;

    void setPath(const pair<City,City> &path);

    double getPrice() const;

    void setPrice(double price);

    const SString &getAirline() const;

    void setAirline(const SString &airline);

    double getTime() const;

    void setTime(double time);
    Flight(City a, City b, double price, SString airline, double time);
    Flight();
    Flight(const Flight &a);

public:


private:
    pair<City,City> path;
    double price;
    SString airline;
    double time;

};


#endif //INC_20F_FLT_PLN_FLIGHT_H
