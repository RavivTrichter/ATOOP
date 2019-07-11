//
// Created by Admin on 19/06/2018.
//

#ifndef EXERCISE3_PATROLBOAT_H
#define EXERCISE3_PATROLBOAT_H

#include <ostream>
#include "Ship.h"
#include "Model.h"



class PatrolBoat : public Ship{
public:

    static const int MAX_GAS_PATROL = 900000;

    static const int GAS_USE_PER_NM_PATROL = 2000;

    /******** The big 5 *********/

    PatrolBoat(const std::string& shipName, const Point& pos, int Resistance);

    PatrolBoat(const PatrolBoat&) = default;

    PatrolBoat(PatrolBoat&&) = default;

    PatrolBoat& operator=(const PatrolBoat&) = default;

    PatrolBoat& operator=(PatrolBoat&&) = default;

    virtual ~PatrolBoat() = default;


    virtual void Moving(weak_ptr<class Port> port, int speed);/*moving by port*/

    virtual void Moving(Point &point, int speed);/*moving by point*/

    virtual void Moving(double angle, int speed);/*moving by angle*/

    virtual void update();

    virtual void printStatus() const;

    virtual void stop();

    virtual void refuelAfterQue(); //when a ship exit from refuel queue. the function fuel the ship

    const vector<shared_ptr<Ship>>& getVecShip()const{ return Model::getInstance().getShipVec();}

    std::weak_ptr<Port> givesTheCloserPort();//gives the next port are closest to the current port

    /******* getters & setters *******/
    int getResistance() const;

    void setResistance(int Resistance);

    virtual TypeIdShip getTypeName(){ return myType;}

    virtual int getNumOfMoves() const;

    void setNumOfMoves(int numOfMoves);

private:

    int Resistance,index,numOfMoves;

    double Gas;

    TypeIdShip myType;

    vector<bool> visitedPorts;/*vector that will be with the same place in vector of ports*. when the field true the ship visited*/

    int indexOfFirstPort;/*save the index of the first port. when the ship finish the round she return to this port*/

    //functions
    void decreaseGas();/*decreasing gas from ship*/

    void docked();/* when the ship in docked*/

    int givesIndexOfPort(std::weak_ptr<Port> port);/*gives the index of port in the vector of ports*/
};


#endif //EXERCISE3_PATROLBOAT_H
