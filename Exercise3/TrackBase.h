//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_TRACKBASE_H
#define EXERCISE3_TRACKBASE_H


#include <memory>
#include "Port.h"


class TrackBase {
public:
    typedef enum {Angle,ByPort,PointDest} MovingType;

    /******** The big 5 *********/
    TrackBase(const Point &p);

    TrackBase(const TrackBase&) = default;

    TrackBase(TrackBase&&) = default;

    TrackBase& operator=(const TrackBase&) = default;

    TrackBase& operator=(TrackBase&&) = default;

    virtual ~TrackBase() = default;

    const Point &getPosition() const;

    void setPosition(const Point &position);

    const Point &getDestination() const;

    void setDestination(const Point &destination);

    MovingType getMovingWay() const;

    void setMovingWay(MovingType movingWay);

    double getAngle() const;

    void setAngle(double angle);

    const weak_ptr<Port> &getPort() const;

    void setPort(const weak_ptr<Port> &port);

    double getSpeed() const;

    void setSpeed(double speed);

private:

    Point position,destination;

    MovingType movingWay;

    double angle;

    weak_ptr<class Port> port;

    double speed;
};


#endif //EXERCISE3_TRACKBASE_H
