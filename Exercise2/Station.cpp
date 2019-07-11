
//
// Created by Admin on 18/05/2018.
//

#include "Station.h"




Station::Station(Station::StationType stationType, const string &stationName) :
        stationType(stationType), stationName(stationName), distance(std::numeric_limits<int>::max()){}


/**  Getters & Setters  **/


Station::StationType Station::getStationType() const {
    return stationType;
}

const string &Station::getStationName() const {
    return stationName;
}

int Station::getDistance() const {
    return distance;
}

void Station::setDistance(int distance) {
    Station::distance = distance;
}

bool Station::operator<(const Station& station) {
    return distance < station.distance;
}

bool Station::operator>(const Station& station) {
    return distance > station.distance;
}

