//
// Created by raviv on 6/17/18.
//

#include "TrackBase.h"

TrackBase::TrackBase(const Point &p) : position(p),destination(Point()), movingWay(MovingType::PointDest), angle(0), port(), speed(0){}

const Point &TrackBase::getPosition() const {
    return position;
}

void TrackBase::setPosition(const Point &position) {
    TrackBase::position = position;
}

const Point &TrackBase::getDestination() const {
    return destination;
}

void TrackBase::setDestination(const Point &destination) {
    TrackBase::destination = destination;
}

TrackBase::MovingType TrackBase::getMovingWay() const {
    return movingWay;
}

void TrackBase::setMovingWay(TrackBase::MovingType movingWay) {
    TrackBase::movingWay = movingWay;
}

double TrackBase::getAngle() const {
    return angle;
}

void TrackBase::setAngle(double angle) {
    TrackBase::angle = angle;
}

const weak_ptr<Port> &TrackBase::getPort() const {
    return port;
}

void TrackBase::setPort(const weak_ptr<Port> &port) {
    TrackBase::port = port;
}

double TrackBase::getSpeed() const {
    return speed;
}

void TrackBase::setSpeed(double speed) {
    TrackBase::speed = speed;
}

