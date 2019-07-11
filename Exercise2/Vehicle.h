//
// Created by Admin on 19/05/2018.
//

#include <iostream>

#ifndef HW2_VEHICLE_H
#define HW2_VEHICLE_H


using namespace std;


/** This is a Base Abstract Class that describes a type of Vehicle in Oranjestad city
 * every vehicle in the city has a type described by the enum
 *
 *  All of it's derived classes have a static integer that describes it's stop time. the variable is static because it's sharable by
 *  every instance of the inherit class
 * **/
class Vehicle {
public:
    typedef enum  {Bus, Sprinter , Rail, Tram} VehicleType;

    Vehicle(VehicleType);

    virtual VehicleType getVehicleType() = 0;

    virtual int getStopTime()=0;

protected:
    VehicleType vh;
};


#endif //HW2_VEHICLE_H
