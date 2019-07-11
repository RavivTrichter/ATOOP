//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_SPRINTER_H
#define HW2_SPRINTER_H


#include "Vehicle.h"


/* Derived class of vehicle -> derives all it's methods and data members
 *
 * describes the stop time of this vehicle and it's type
 * */

class Sprinter : public Vehicle{

public:
    Sprinter();

    virtual VehicleType getVehicleType();

    static int sprinterTime;

    virtual int getStopTime(){return sprinterTime;}

};


#endif //HW2_SPRINTER_H
