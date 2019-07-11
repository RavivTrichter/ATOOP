//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_CENTRAL_H
#define HW2_CENTRAL_H


#include "Station.h"


/** This class ia s Station, it represents a type of station and has it's own default stop time **/


class Central : public Station{ // inheriting from Station -> central is a type of station
public:
    Central(const string& stationName,StationType stationType = StationType::Central);

    static int centralTime; // default time

    virtual int getTransitTime(){ return centralTime;}
};


#endif //HW2_CENTRAL_H
