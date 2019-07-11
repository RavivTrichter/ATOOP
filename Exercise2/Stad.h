//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_STAD_H
#define HW2_STAD_H


#include "Station.h"


//Derived class of Station -> get's all it's methods and data members
class Stad : public Station{

public:
    static int stadTime;

    Stad(const string& stationName, StationType stationType = StationType::Stad);

    virtual int getTransitTime(){ return stadTime;}

};


#endif //HW2_STAD_H
