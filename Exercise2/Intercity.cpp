//
// Created by Admin on 18/05/2018.
//

#include "Intercity.h"

int Intercity::interCityTime = 15; // default stop time for InterCity


Intercity::Intercity(const string &stationName, StationType stationType) :
Station(stationType,stationName) {}

