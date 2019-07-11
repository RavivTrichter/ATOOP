//
// Created by Admin on 19/05/2018.
//

#include "Central.h"

int Central::centralTime = 5; // default stop time at Central Station

Central::Central(const string &stationName, Station::StationType stationType) : Station(stationType, stationName) {}



