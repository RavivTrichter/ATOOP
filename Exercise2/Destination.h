//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_DESTINATION_H
#define HW2_DESTINATION_H


#include "Station.h"
#include "Vehicle.h"
#include <memory>


class Destination {

public:
    Destination(weak_ptr<Station> station, shared_ptr<Vehicle> vehicle, int weight,const string& name); // C'tor

public:

    //bool visited; // a data member that represents if the Node has been visited in DFS or not

    /**  Getters And Setters **/

    const weak_ptr<Station> &getStation() const;

    void setStation(const weak_ptr<Station> &station);

    const shared_ptr<Vehicle> &getVehicle() const;

    void setVehicle(const shared_ptr<Vehicle> &vehicle);

    int getWeight() const;

    void setWeight(int weight);

    bool operator==(const weak_ptr<Destination> rhs);

    const string &getStationName() const;

    /** Data Members  **/

    bool visitedForMulti = false;

private:

    weak_ptr<Station> station; // describes the destination station

    shared_ptr<Vehicle> vehicle; // the type of vehicle in the edge

    int weight;

    string stationName;
};


#endif //HW2_DESTINATION_H
