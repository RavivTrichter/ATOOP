//
// Created by Admin on 24/06/2018.
//

#ifndef EXERCISE3_ABSTRACTFACTORY_H
#define EXERCISE3_ABSTRACTFACTORY_H

#include <iostream>
#include <memory>
#include "Geometry.h"

class AbstractFactory {
public:
    virtual std::shared_ptr<class Ship> getShip(const string& shipType ,const string& shipName, Point& pos, int resOatt, int rangeOcap = 0 ) = 0;
};


#endif //EXERCISE3_ABSTRACTFACTORY_H
