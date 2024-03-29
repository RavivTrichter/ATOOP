//
// Created by raviv on 6/17/18.
//

#include "Geometry.h"
#include <cmath>
#include <ctgmath>
const double pi = 2. * atan2(1., 0.);
double to_radians(double theta_d)
{
    return theta_d * pi / 180.0;
}

double to_degrees(double theta_r)
{
    return theta_r * 180.0 / pi;
}
// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}
Cartesian_vector::Cartesian_vector()
{
    delta_x = 0.0;
    delta_y = 0.0;
}
void Cartesian_vector::operator=(const Polar_vector& pv)
{
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}



// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}
Polar_vector::Polar_vector()
{
    r = 0.0;
    theta = 0.0;
}
void Polar_vector::operator=(const Cartesian_vector& cv)
{
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}



Point::Point(double x, double y) : x(x), y(y)
{
}

double Point::distance(const Point& p)const{
    double x_diff = x - p.x;
    double y_diff = y - p.y;
    return std::sqrt((x_diff * x_diff) + (y_diff * y_diff));

}

Point::Point()
{
    x = 0.0;
    y = 0.0;
}

void Point::print() const
{
    cout << setprecision(2) << "(" << x << ", " << y << ")";
}

bool Point::operator==(const Point & rhs)
{
    return x == rhs.x && y == rhs.y;
}

double Point::toAngle(const Point& p) const {
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    double theta = atan2(p.y - y,p.x - x) * 180 / pi;

    if (theta < 0.)
        theta += 360.0; // normalize theta positive
    return theta;
}

Point Point::givesTheNextPoint(double radius, double angle)const {
    double delta_x = (radius * cos(angle * pi / 180))+x;
    double delta_y = (radius * sin(angle * pi / 180))+y;
    return Point(delta_x,delta_y);
}


