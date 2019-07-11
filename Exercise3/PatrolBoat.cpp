//
// Created by Admin on 19/06/2018.
//

#include "PatrolBoat.h"

PatrolBoat::PatrolBoat(const std::string& shipName, const Point& pos, int Resistance) :
        Ship(shipName, pos), Resistance(Resistance),Gas(MAX_GAS_PATROL),myType(PB),indexOfFirstPort(-1),numOfMoves(3){
    visitedPorts.insert(visitedPorts.begin(),Model::getInstance().getSizeOfPortVector(),false);
}

int PatrolBoat::getResistance() const {
    return Resistance;
}

void PatrolBoat::setResistance(int Resistance) {
    PatrolBoat::Resistance = Resistance;
}

void PatrolBoat::Moving(Point &point, int speed) {
    if((status == MovingTo && trackBase.getMovingWay() == TrackBase::ByPort) || status == DeadInTheWater){
        if(status == DeadInTheWater){//If the ship is dead in the water she cannot move
            throw MyExceptions::ShipStatusException("The ship is dead in the water");
        }
        throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
    }
    if(status == Docked && (existInQueueGas || numOfMoves != 3)){
        if(numOfMoves != 3){//If num of moves different of 3 the ship in middle of round
            throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
        }
        throw MyExceptions::ShipStatusException("The ship exists in the queue, cant move ");
    }
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::PointDest);
    trackBase.setDestination(point);
    trackBase.setSpeed(speed);
}

void PatrolBoat::Moving(double angle, int speed) {
    if((status == MovingTo && trackBase.getMovingWay() == TrackBase::ByPort) || status == DeadInTheWater){
        if(status == DeadInTheWater){//If the ship is dead in the water she cannot move
            throw MyExceptions::ShipStatusException("The ship is dead in the water");
        }
        throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
    }
    if(status == Docked && (existInQueueGas || numOfMoves != 3)){
        if(numOfMoves != 3){//If num of moves different of 3 the ship in middle of round
            throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
        }
        throw MyExceptions::ShipStatusException("The ship exists in the queue, cant move ");
    }
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::Angle);
    trackBase.setAngle(angle);
    trackBase.setSpeed(speed);
}

void PatrolBoat::Moving(weak_ptr<class Port> port, int speed) {
    if((status == MovingTo && trackBase.getMovingWay() == TrackBase::ByPort) || status == DeadInTheWater){
        if(status == DeadInTheWater){//If the ship is dead in the water she cannot move
            throw MyExceptions::ShipStatusException("The ship is dead in the water");
        }
        throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
    }
    if(status == Docked && (existInQueueGas || numOfMoves != 3)){
        if(numOfMoves != 3){//If num of moves different of 3 the ship in middle of round
            throw MyExceptions::ShipStatusException("The ship can't change destination in the middle of a round ");
        }
        throw MyExceptions::ShipStatusException("The ship exists in the queue, cant move ");
    }
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::ByPort);
    trackBase.setPort(port);
    trackBase.setSpeed(speed);
    std::fill(visitedPorts.begin(), visitedPorts.end(), false);//fill the boolean vector with false fields
    indexOfFirstPort = givesIndexOfPort(port);
    visitedPorts[indexOfFirstPort] = true;
    index = indexOfFirstPort;
    numOfMoves = 0;
}

void PatrolBoat::update() {
    if(status == Ship::Status::Docked){
        docked();
    }
    else if(status == Ship::Status::MovingTo){
        stepOnWater();
        decreaseGas();
    }
}

/*when ship in docked she can to be in 3 states*/
void PatrolBoat::docked() {
    weak_ptr<Port> closePort;
    switch (numOfMoves) {
        case 0://trying to refuel if she cannot she gets into a refuel queue
            refuel();
            break;
        case 1:// do not nothing
            numOfMoves++;
            break;
        case 2:// moving to port that closest
            setStatus(Ship::Status::MovingTo);
            trackBase.setMovingWay(TrackBase::ByPort);
            closePort = givesTheCloserPort();
            if(closePort.lock() == nullptr) {//this scope will be only when the ship finish round
                auto FirstPort = Model::getInstance().getPortVec()[indexOfFirstPort];//getting a port to return the first port
                trackBase.setPort(FirstPort);
                numOfMoves++;// now num of moves will be 3 that means that the ship finish round*/
                return;
            }
            trackBase.setPort(closePort);
            index = givesIndexOfPort(closePort);
            visitedPorts[index] = true;
            numOfMoves = 0;
            break;
        case 3:
            cout << "The boat: " << name << " finished it's round" << endl;
            break;
    }
}


std::weak_ptr<Port> PatrolBoat::givesTheCloserPort() {//this function will gives the port closest
    auto vectOfPorts = Model::getInstance().getPortVec();
    std::shared_ptr<Port> theClosePort(nullptr);

    for(int i=0; i<vectOfPorts.size(); i++){
        if(visitedPorts[i] == true){//the ship visited in this port and this round
            continue;
        }
        if(theClosePort == nullptr){
            theClosePort = vectOfPorts[i];
        }
        if(trackBase.getPosition().distance(theClosePort->getPosition()) >
                trackBase.getPosition().distance(vectOfPorts[i]->getPosition()) ){
            theClosePort = vectOfPorts[i];
        }
    }
    return theClosePort;
}

void PatrolBoat::refuelAfterQue() {
    auto port  = trackBase.getPort().lock();
    if((port->getGasStoke()+(Gas/1000)) <= (MAX_GAS_PATROL/1000)){//when the port doesn't enough gas to fuel
        Gas += (port->getGasStoke()*1000);
        port->setGasStoke(0);
    }
    else{
        int x = MAX_GAS_PATROL - Gas;
        Gas += x;
        port->setGasStoke(port->getGasStoke() - (x/1000));
    }
    existInQueueGas = false;
    numOfMoves++;
}

void PatrolBoat::printStatus() const {

    cout << "Patrol_boat " << name << " at ";
    trackBase.getPosition().print();
    cout << ", fuel: " << fixed << Gas/1000 << " kl, resistance: "
         << Resistance << ", ";

    if(status == Ship::MovingTo)
        printMoveWay();
    else if(status == Ship::Status::Stopped)
        cout << "Stopped";
    else if(status == Ship::Status::DeadInTheWater)
        cout << "Dead in the water";
    else
        cout << "Docked at " << trackBase.getPort().lock()->getPortName();
    cout << endl;

}

int PatrolBoat::givesIndexOfPort(std::weak_ptr<Port> port) {
    int i=0;
    for(std::weak_ptr<Port> x : Model::getInstance().getPortVec()){
        if(x == port)
            break;
        i++;
    }
    return i;
}

void PatrolBoat::decreaseGas() {
    Gas -= trackBase.getSpeed()*GAS_USE_PER_NM_PATROL;
    if(Gas <=0){//if the ship doesn't have gas she change her status to dead in water
        setStatus(Ship::Status::DeadInTheWater);
        Gas = 0;
    }
}

int PatrolBoat::getNumOfMoves() const {
    return numOfMoves;
}

void PatrolBoat::setNumOfMoves(int numOfMoves) {
    PatrolBoat::numOfMoves = numOfMoves;
}

void PatrolBoat::stop() {
    status = Stopped;
    trackBase.getPort().lock()->eraseFromGasQue(name);
    numOfMoves = 3; // when the value of "numOfMoves" the ship does not in round
}




