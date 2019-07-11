//
// Created by Admin on 19/06/2018.
//

#include "Ship.h"
#include "Model.h"


Ship::Ship(const string& name,const Point& point, const Status& status ) :
        name(name), trackBase(TrackBase(point)), status(status), existInQueueGas(false){}

void Ship::printMoveWay() const {
    if(trackBase.getMovingWay() == TrackBase::MovingType::PointDest){
        cout << "Moving to ";
        trackBase.getDestination().print();
        cout << " on course " << fixed << trackBase.getPosition().toAngle(trackBase.getDestination())
             << " deg, speed " << trackBase.getSpeed() << " nm/hr ";
    }
    else if(trackBase.getMovingWay() == TrackBase::MovingType::ByPort){
        cout << "Moving to " << trackBase.getPort().lock()->getPortName()<< " on course "<< fixed
             << trackBase.getPosition().toAngle(trackBase.getPort().lock()->getPosition()) << " deg, speed "
             << trackBase.getSpeed() << " nm/hr ";
    }
    else if(trackBase.getMovingWay() == TrackBase::MovingType::Angle){
        cout << "Moving on course " << fixed << trackBase.getAngle() << " deg, speed " << trackBase.getSpeed() << " nm/hr ";
    }
}

/*moving only for the cruiser the other will be overloaded*/
void Ship::Moving(Point &point, int speed) {
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::PointDest);
    trackBase.setDestination(point);
    trackBase.setSpeed(speed);
}

/*moving only for the cruiser the other will be overloaded*/
void Ship::Moving(double angle, int speed) {
    setStatus(Ship::Status::MovingTo);
    trackBase.setMovingWay(TrackBase::Angle);
    trackBase.setAngle(angle);
    trackBase.setSpeed(speed);
}

/*calculate the next move of ship in water, with three ways: 1. with angle, 2. with port, 3.with point*/
void Ship::stepOnWater() {
    //this function will be the next movement of ship
    if(trackBase.getMovingWay() == TrackBase::Angle){
        Point newPos = trackBase.getPosition().givesTheNextPoint
                (trackBase.getSpeed(),trackBase.getAngle());
        trackBase.setPosition(newPos);
    }
    else if(trackBase.getMovingWay() == TrackBase::ByPort){
        //return point that will be the next point destination
        Point newPos = trackBase.getPosition().givesTheNextPoint
                (trackBase.getSpeed(),trackBase.getPosition().toAngle(trackBase.getPort().lock()->getPosition()));
        if(trackBase.getPosition().distance(newPos) >= trackBase.getPosition().distance(trackBase.getPort().lock()->getPosition())){
            trackBase.setPosition(trackBase.getPort().lock()->getPosition());//the ship arrive to port
            setStatus(Ship::Status::Docked);
        }else{
            trackBase.setPosition(newPos);
        }
    }
    else{
        Point newPos = trackBase.getPosition().givesTheNextPoint
                (trackBase.getSpeed(),trackBase.getPosition().toAngle(trackBase.getDestination()));
        if(trackBase.getPosition().distance(newPos) >= trackBase.getPosition().distance(trackBase.getDestination())){
            trackBase.setPosition(trackBase.getDestination());//the ship arrive to position
            setStatus(Ship::Status::Stopped);
        }else{
            trackBase.setPosition(newPos);
        }
    }
}

void Ship::refuel() {
    if (status != Ship::Status::Docked) {
        throw MyExceptions::ShipStatusException("Cannot refuel a ship that isn't docked");
    }

    auto ship = Model::getInstance().findShip(name);

    if (!existInQueueGas) {//the queue ships doesn't have this ship
        trackBase.getPort().lock()->insertToGasQueue(ship);
        existInQueueGas = true;
    }
}

const TrackBase &Ship::getTrackBase() const {
    return trackBase;
}

void Ship::setStatus(Ship::Status status) {
    Ship::status = status;
}


