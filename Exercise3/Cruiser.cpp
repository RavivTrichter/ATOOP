//
// Created by raviv on 6/17/18.
//

#include "Cruiser.h"
#include "Freighter.h"
#include "PatrolBoat.h"

Cruiser::Cruiser(std::string shipName, const Point& pos, int resOatt, int rangeOcap) : Ship(shipName,pos)
, Force_of_attack(resOatt), range(rangeOcap),myType(CR){}


void Cruiser::update() {
    stepOnWater();
}

void Cruiser::attack(std::weak_ptr<Ship> ship){
    if(range < trackBase.getPosition().distance(ship.lock()->getTrackBase().getPosition())){
        throw MyExceptions::OutOfRangeException("The ship is out of range for attack");
    }
    ship.lock()->setStatus(Stopped);
    if(ship.lock()->getTypeName() == Ship::TypeIdShip::FR) {//if the ship is attacked is a freighter
        auto fr = dynamic_pointer_cast<Freighter>(ship.lock());

        if (Force_of_attack > fr->getResistance()) {// compares the resistance and force
            Force_of_attack++;
            fr->setContainers(0);
        } else {
            Force_of_attack--;
        }
    }
    else if(ship.lock()->getTypeName() == Ship::TypeIdShip::PB){//if the ship is attacked is a patrol boat
        auto fr = dynamic_pointer_cast<PatrolBoat>(ship.lock());
        if(Force_of_attack > fr->getResistance()){
            Force_of_attack++;
            fr->setResistance(fr->getResistance()-1);
        }
        else {
            Force_of_attack--;
            fr->setResistance(fr->getResistance()+1);
        }
        fr->setNumOfMoves(3); // when the value of "numOfMoves" the ship does not in round
    }
}

void Cruiser::printStatus() const {
    cout << "Cruiser " << name << " at";
    trackBase.getPosition().print();
    cout << " force: " << Force_of_attack << " ";
    if(status == Ship::MovingTo)
        printMoveWay();
    else if(status == Ship::Status::Stopped)
        cout << "Stopped";
    cout << endl;
}

void Cruiser::stop() {
    status = Stopped;
}


