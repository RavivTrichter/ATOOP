//
// Created by Admin onstd::numeric_limits<int>::max() 19/05/2018.
//

#include "Destination.h"



/* C'tor */
Destination::Destination(weak_ptr<Station> station, shared_ptr<Vehicle> vehicle, int weight,const string& name) :
        station(station), vehicle(vehicle), weight(weight), stationName(name) {}



/**  Getters & Setters **/


const weak_ptr<Station> &Destination::getStation() const {
    return station;
}

void Destination::setStation(const weak_ptr<Station> &station) {
    Destination::station = station;
}

const shared_ptr<Vehicle> &Destination::getVehicle() const {
    return vehicle;
}

void Destination::setVehicle(const shared_ptr<Vehicle> &vehicle) {
    Destination::vehicle = vehicle;
}

int Destination::getWeight() const {
    return weight;
}

void Destination::setWeight(int weight) {
    Destination::weight = weight;
}

const string &Destination::getStationName() const {
    return stationName;
}

bool Destination::operator==(const weak_ptr<Destination> rhs) {
    return stationName == rhs.lock()->stationName;
}

