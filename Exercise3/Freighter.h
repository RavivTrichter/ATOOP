//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_FREIGHTER_H
#define EXERCISE3_FREIGHTER_H


#include "Ship.h"

class Freighter : public Ship {
public:

    static const int GAS_USE_PER_NM_FREIGHTER = 1000; // use of gas per nm

    static const int MAX_GAS_FREIGHTER = 500000; // max gas that a freighter can contain


    /******** The big 5 *********/
    Freighter(std::string shipName, const Point& pos,int Resistance,int Containers);

    Freighter(const Freighter&) = default;

    Freighter(Freighter&&) = default;

    Freighter& operator=(const Freighter&) = default;

    Freighter& operator=(Freighter&&) = default;

    virtual ~Freighter() = default;

    virtual void update();

    virtual void printStatus() const;

    virtual void stop();

    virtual TypeIdShip getTypeName(){ return myType;}

    virtual void Moving(weak_ptr<class Port> port, int speed);

    virtual void Moving(Point &point, int speed);

    virtual void Moving(double angle, int speed);

    virtual void load_at(std::weak_ptr<Port> port);// loading containers at a specific port

    void docked();//when the ship is docked

    void dock(std::weak_ptr<Port> port);//when the ship in radius 0.1 from specific port

    void unload_at(std::weak_ptr<Port> port, int containers);//unloading number of containers in a specific port

    virtual void refuelAfterQue(); //when a ship exit from refuel queue. the function fuel the ship

    int getResistance() const;

    void setContainers(int Containers);

private:

    int Resistance, Containers;

    double Gas;

    TypeIdShip myType;

    const int maxContainers;

    vector<std::pair<std::string,std::string>> missionQue;

    //function

    bool existInMissionQue();

    void decreaseGas();
};


#endif //EXERCISE3_FREIGHTER_H
