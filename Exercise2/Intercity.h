//
// Created by Admin on 18/05/2018.
//

#ifndef HW2_INTERCITY_H
#define HW2_INTERCITY_H

#include <iostream>
#include "Station.h"

using namespace std;


/* A derived class of Station */
class Intercity: public Station {
public:
    Intercity(const string &stationName, StationType stationType = StationType::InterCity);

    static int interCityTime;

    virtual int getTransitTime(){ return interCityTime;}

};


#endif //HW2_INTERCITY_H
