//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_SHIP_H
#define EXERCISE3_SHIP_H

#include <iostream>
#include <memory>
#include <iomanip>
#include "TrackBase.h"
#include "MyExceptions.h"



class Ship {
public:
    typedef enum{Stopped, Docked,DeadInTheWater, MovingTo} Status;

    typedef enum{PB, FR, CR} TypeIdShip;

    /******** The big 5 *********/

    Ship(const std::string& name,const Point& point, const Status& status = Status::Stopped );

    Ship(const Ship&) = default;

    Ship(Ship&&) = default;

    Ship& operator=(const Ship&) = default;

    Ship& operator=(Ship&&) = default;

    virtual ~Ship() = default;

    friend bool operator==(std::shared_ptr<Ship> s1, const Ship& s2){return s1->name == s2.name;}

    friend bool operator==(std::shared_ptr<Ship> s1 , std::weak_ptr<Ship> s2) {return s1->name == s2.lock()->name;}

    virtual void update() = 0;

    virtual void printStatus() const = 0;

    virtual TypeIdShip getTypeName()=0;

    virtual void stop()=0;

    virtual void load_at(std::weak_ptr<Port> port){}

    virtual void Moving(weak_ptr<Port> port, int speed){throw MyExceptions::ShipStatusException("Cruiser cannot go to ports");}

    virtual void Moving(Point& point, int speed);

    virtual void Moving(double angle, int speed);

    virtual void unload_at(std::weak_ptr<Port> port, int containers){}

    virtual void dock(std::weak_ptr<Port> port){}

    virtual void stepOnWater();//calculate the next move of ship in water, with three ways: 1. with angle, 2. with port, 3.with point

    virtual void attack(std::weak_ptr<Ship> ship){}

    virtual void refuelAfterQue(){}

    void refuel();

    void printMoveWay()const;

    /******* getters & setters *******/

    inline std::string getName(){return name;}

    const TrackBase &getTrackBase() const;

    void setStatus(Status status);

    virtual int getNumOfMoves() const{}
protected:

    std::string name;

    TrackBase trackBase;

    Status status;

    bool existInQueueGas;

};


#endif //EXERCISE3_SHIP_H


