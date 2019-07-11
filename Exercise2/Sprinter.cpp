//
// Created by Admin on 19/05/2018.
//

#include "Sprinter.h"

int Sprinter::sprinterTime = 4;//default stop time is 4 minutes

Sprinter::Sprinter() : Vehicle(VehicleType::Sprinter){}

Vehicle::VehicleType Sprinter::getVehicleType() {
    return VehicleType::Sprinter;
}
