//
// Created by Admin on 19/05/2018.
//

#include "Rail.h"

int Rail::railTime = 5;//default time is 5 min

Rail::Rail() : Vehicle(VehicleType::Rail) {}

Vehicle::VehicleType Rail::getVehicleType() {
    return VehicleType::Rail;
}
