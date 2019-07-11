//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_RAIL_H
#define HW2_RAIL_H


#include "Vehicle.h"

class Rail : public Vehicle{
public:
    Rail();

    static int railTime;

    virtual VehicleType getVehicleType();

    virtual int getStopTime(){return railTime;}

};


#endif //HW2_RAIL_H
