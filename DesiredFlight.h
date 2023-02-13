//
// Created by Alex Shockley on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_DESIREDFLIGHT_H
#define INC_20F_FLT_PLN_DESIREDFLIGHT_H
#include "City.h"

class DesiredFlight { // Wrapper for a pair of cities Probably did not need this class in the first place but Its too late to change it now
public:
    DesiredFlight();
    DesiredFlight(pair<City,City>, char a);


    const pair<City,City> &getPath() const;

    void setPath(const pair<City,City> &path);

    char getReason() const;

    void setReason(char reason);

private:
    pair<City,City> path;
    char reason;
};


#endif //INC_20F_FLT_PLN_DESIREDFLIGHT_H
