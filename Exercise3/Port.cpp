//
// Created by Admin on 19/06/2018.
//

#include <vector>
#include "Port.h"
#include "Ship.h"
#include "PatrolBoat.h"


void Port::update(){
    gasStoke += produce;
    std::weak_ptr<Ship> ship();
    if(!shipQueue.empty()) {
        std::weak_ptr<Ship> ship = shipQueue.front();
        ship.lock()->refuelAfterQue();
        shipQueue.pop_front();
    }
}

void Port::printStatus() {
    cout << "Port " << portName << " at position ";
    position.print();
    cout << ", Fuel available: " << fixed << gasStoke << " kl" << endl;
}

void Port::insertToGasQueue(std::vector<shared_ptr<Ship>>::iterator it) {
    shipQueue.push_back(*it);
}

void Port::eraseFromGasQue(std::string shipName) {// erasing from gas queue
    auto begin = shipQueue.begin();
    auto end = shipQueue.end();
    for( ; begin != end; begin++){
        if((*begin).lock()->getName() == shipName){
            shipQueue.erase(begin);
            return;
        }
    }
}

bool Port::theShipFirstInQue(const std::string &shipName) {//checks if ship is first in queue
    if(!shipQueue.empty() && shipQueue.front().lock()->getName() == shipName)
        return true;
    return false;
}




