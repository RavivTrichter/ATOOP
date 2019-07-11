//
// Created by Admin on 19/06/2018.
//

#ifndef EXERCISE3_PORT_H
#define EXERCISE3_PORT_H

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include "Geometry.h"



class Port {
public:


    /******** The big 5 *********/

    Port(const std::string portName,const Point& pos, const int GasStoke, const int produce ) : portName(portName), position(pos),
                                                                                                gasStoke(GasStoke), produce(produce){
    }

    Port(const Port&) = default;

    Port(Port&&) = default;

    Port& operator=(const Port&) = default;

    Port& operator=(Port&&) = default;

    virtual ~Port() = default;

    void insertToGasQueue(std::vector<shared_ptr<class Ship>>::iterator it);

    void update();

    void printStatus();

    void eraseFromGasQue(std::string shipName);// erasing from gas queue

    bool theShipFirstInQue(const std::string& shipName );//checks if ship is first in queue

    friend bool operator==(std::weak_ptr<Port> port1 ,std::weak_ptr<Port> port2){
        return port1.lock()->portName==port2.lock()->portName;
    }


    /********** Getters & Setters **********/
    const string &getPortName() const {
        return portName;
    }

    const Point &getPosition() const {
        return position;
    }

    double getGasStoke() const {
        return gasStoke;
    }

    void setGasStoke(double gasStoke) {
        Port::gasStoke = gasStoke;
    }

private:
    std::string portName;
    list<weak_ptr<Ship>> shipQueue;//queue of refuels
    Point position;//position of port
    double gasStoke;
    const int produce;//produce gas
};


#endif //EXERCISE3_PORT_H
