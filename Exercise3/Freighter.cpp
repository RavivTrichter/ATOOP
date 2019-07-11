//
// Created by raviv on 6/17/18.
//

#include <sstream>
#include "Freighter.h"
#include "Model.h"

Freighter::Freighter(std::string shipName, const Point& pos, int Resistance,int Containers) : Ship(shipName, pos), Resistance(Resistance)
        , Containers(Containers), Gas(MAX_GAS_FREIGHTER), myType(FR), maxContainers(Containers){}

void Freighter::update() {
    if(status == Ship::Status::Docked){
        docked();
    }
    else if(status == Ship::Status::MovingTo){
        stepOnWater();
        decreaseGas();
    }
}

void Freighter::Moving(weak_ptr<class Port> port, int speed) {
    if(status == Ship::Status::DeadInTheWater){
        throw MyExceptions::ShipStatusException("The ship is dead in the water, can't move");
    }
    if(status == Docked){
        if(existInMissionQue()){
            throw MyExceptions::ShipStatusException("The ship needs to unload or load in this port");
        }
        else if(existInQueueGas) {//checks if the ship in fuel queue
            throw MyExceptions::ShipRefuelException("The ship needs to refuel before move");
        }
    }
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::ByPort);
    trackBase.setPort(port);
    trackBase.setSpeed(speed);
}


void Freighter::Moving(Point &point, int speed) {
    if(status == Ship::Status::DeadInTheWater){
        throw MyExceptions::ShipStatusException("The ship is dead in the water, can't move");
    }
    if(status == Docked){
        if(existInMissionQue()){
            throw MyExceptions::ShipStatusException("The ship needs to unload or load in this port");
        }
        else if(existInQueueGas) {
            throw MyExceptions::ShipRefuelException("The ship needs to refuel before move");
        }
    }

    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::PointDest);
    trackBase.setDestination(point);
    trackBase.setSpeed(speed);
}

void Freighter::Moving(double angle, int speed) {
    if(status == Ship::Status::DeadInTheWater){
        throw MyExceptions::ShipStatusException("The ship is dead in the water, can't move");
    }
    if(status == Docked){
        if(existInMissionQue()){
            throw MyExceptions::ShipStatusException("The ship needs to unload or load in this port");
        }
        else if(existInQueueGas) {
            throw MyExceptions::ShipRefuelException("The ship needs to refuel before move");
        }
    }
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::Angle);
    trackBase.setAngle(angle);
    trackBase.setSpeed(speed);
}

/*missionQue holds pair of port name in th first field and in the second filed holds the string load*/
void Freighter::load_at(std::weak_ptr<Port> port) {
    std::pair<std::string,std::string> load{port.lock()->getPortName(), "load"};
    missionQue.emplace_back(port.lock()->getPortName(), "load");
}

/*missionQue holds pair of port name in th first field and in the second filed holds num of containers to unload*/
void Freighter::unload_at(std::weak_ptr<Port> port, int containers) {
    stringstream os{};
    os << containers;
    missionQue.emplace_back(std::make_pair(port.lock()->getPortName(),os.str()));
}


void Freighter::docked() {//when the ship docks
    auto begin = missionQue.begin();
    auto end = missionQue.end();
    for(; begin != end; begin++){//Checks if the ship has a command of load or unload from the port that is docked
        if((*begin).first == trackBase.getPort().lock()->getPortName())
            break;
    }
    if(begin != end){//if the vector have this port its means that have a command to do
        if(trackBase.getPort().lock()->theShipFirstInQue(name))//checks if the ship first in queue and that command load or unload will be in the next time step
            return;
        if((*begin).second == "load"){
            Containers = maxContainers;
        }
        else{
            stringstream iss{(*begin).second};
            int numOfContainers;
            iss >> numOfContainers;
            if(numOfContainers >= Containers){//checks if the user want to unload containers more than ship has
                Containers = 0;
                cout << "Warnings the ship " << name << "doesn't have enough containers to unload " << endl;
            }
            else{
                Containers -= numOfContainers;
            }
        }
        missionQue.erase(begin);
    }
}

void Freighter::dock(std::weak_ptr<Port> port) {
    if(trackBase.getPosition().distance(port.lock()->getPosition()) <= 0.1){//checks if the ship can docks
        setStatus(Ship::Status::Docked);
        trackBase.setPort(port);
        trackBase.setSpeed(0);
        trackBase.setPosition(port.lock()->getPosition());
    }
    else
        throw MyExceptions::ShipStatusException("The port isn't in distance of 0.1 nm so the ship cannot dock ");
}

void Freighter::decreaseGas() {
    Gas -= trackBase.getSpeed()*GAS_USE_PER_NM_FREIGHTER;
    if(Gas <=0){//if the ship doesn't have gas she changes her status to dead in water
        setStatus(Ship::Status::DeadInTheWater);
        Gas = 0;
    }
}

void Freighter::printStatus() const {
    cout << "Freighter " << name << " at ";
    trackBase.getPosition().print();
    cout << " , fuel: " << fixed << Gas/1000 << " kl, resistance: " << Resistance << ", ";
    if(status == Ship::Status::MovingTo)
        printMoveWay();
    else if(status == Ship::Status::Stopped)
        cout << "Stopped";
    else if(status == Ship::Status::DeadInTheWater)
        cout << "Dead in the water";
    else
        cout << "Docked at " << trackBase.getPort().lock()->getPortName();
    cout << " ,Containers: " << Containers << endl;

}

void Freighter::refuelAfterQue() {
    auto port  = trackBase.getPort().lock();
    if((port->getGasStoke()+(Gas/1000)) <= (MAX_GAS_FREIGHTER/1000)){//when the port doesn't enough gas to fuel
        Gas += (port->getGasStoke()*1000);
        port->setGasStoke(0);
    }
    else{
        int x = MAX_GAS_FREIGHTER - Gas;
        Gas += x;
        port->setGasStoke(port->getGasStoke() - (x/1000));
    }
    existInQueueGas = false;
}

bool Freighter::existInMissionQue() {
    for(auto x : missionQue){
        if(x.first == trackBase.getPort().lock()->getPortName())
            return true;
    }
    return false;
}

void Freighter::stop() {
    missionQue.clear();
    trackBase.getPort().lock()->eraseFromGasQue(name);
    existInQueueGas = false;
    status = Stopped;
}

int Freighter::getResistance() const {
    return Resistance;
}

void Freighter::setContainers(int Containers) {
    Freighter::Containers = Containers;
}

