//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_BUS_H
#define HW2_BUS_H


#include "Vehicle.h"

/** This class is a Vehicle, describes us the default Stop time**/

class Bus : public Vehicle {

public:
    Bus();

    static int busTime;

    virtual VehicleType getVehicleType();

    virtual int getStopTime(){return busTime;}
};


#endif //HW2_BUS_H
