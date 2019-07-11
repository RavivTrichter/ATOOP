//
// Created by Admin on 19/05/2018.
//

#include "Stad.h"

int Stad::stadTime = 10;

Stad::Stad(const string &stationName, Station::StationType stationType) :
        Station(stationType, stationName) {} // C'tor


