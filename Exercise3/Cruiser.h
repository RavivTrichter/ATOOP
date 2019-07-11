//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_CRUISER_H
#define EXERCISE3_CRUISER_H

#include <iostream>
#include "Ship.h"

class Cruiser : public Ship{

public:

    /******** The big 5 *********/
    Cruiser(std::string shipName, const Point& pos, int resOatt, int rangeOcap );

    Cruiser(const Cruiser&) = default;

    Cruiser(Cruiser&&) = default;

    Cruiser& operator=(const Cruiser&) = default;

    Cruiser& operator=(Cruiser&&) = default;

    virtual ~Cruiser() = default;

    virtual TypeIdShip getTypeName(){ return myType;}

    virtual void attack(std::weak_ptr<Ship> ship);//attacking a specific ship in range of attack

    void update();//updating the next move

    void printStatus() const;

    virtual void stop();
private:
    int Force_of_attack, range;

    TypeIdShip myType;
};


#endif //EXERCISE3_CRUISER_H
