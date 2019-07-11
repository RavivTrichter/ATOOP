
//
// Created by Admin on 18/05/2018.
//

#ifndef HW2_STATION_H
#define HW2_STATION_H



#include <iostream>
#include <limits>
using  namespace std;

/**
 * This class describes a type of station in the city. as we know there are 3 types and they all inherit from this class the data members
 * and methods.
 *  All of it's derived classes have a static integer that describes it's stop time. the variable is static because it's sharable by
 *  every instance of the inherit class
 * **/
class Station {
public:
    bool visited = false; // a data member to describe if the specific node was visited in DFS run

    typedef enum  { InterCity , Stad , Central} StationType;

    Station(StationType stationType,const string& stationName); // C'tor

    bool operator<(const Station&);

    bool operator>(const Station&);
    /** Getters & Setters **/

    StationType getStationType() const;

    const string &getStationName() const;

    int getDistance() const;

    void setDistance(int distance);

    virtual int getTransitTime()=0;


protected:
    StationType stationType;

    string stationName;

    int distance;
};


#endif //HW2_STATION_H
