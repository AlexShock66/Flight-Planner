//
// Created by Alex Shockley on 10/29/2020.
//

#include "DesiredFlight.h"

DesiredFlight::DesiredFlight() {

}

DesiredFlight::DesiredFlight(pair<City, City> path, char a) { // constructor to assign path and reason
    this->path = path;
    reason = a;
}

const pair<City, City> &DesiredFlight::getPath() const { // getters and setters
    return path;
}

void DesiredFlight::setPath(const pair<City, City>&path) {
    DesiredFlight::path = path;
}

char DesiredFlight::getReason() const {
    return reason;
}

void DesiredFlight::setReason(char a) {
    DesiredFlight::reason = a;
}
