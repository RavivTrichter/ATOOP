//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_GEOMETRY_H
#define EXERCISE3_GEOMETRY_H


#include <iostream>
#include <iomanip>
using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);
// class declarations
typedef struct Point {
    double x;
    double y;
    Point(double x, double y);
    Point();
    double toAngle(const Point& p)const;
    Point givesTheNextPoint(double radius, double angle)const;
    double distance(const Point& p)const;
    void print() const;
    bool operator==(const Point& rhs);
} Point;

struct Polar_vector;

typedef struct Cartesian_vector {
    Cartesian_vector(const struct Polar_vector & pv);
    Cartesian_vector();
    void operator=(const struct Polar_vector & pv);
    double delta_x;
    double delta_y;
} Cartesian_vector;
typedef struct Polar_vector {
    Polar_vector(const Cartesian_vector & cv);
    Polar_vector();
    void operator=(const Cartesian_vector & cv);
    double r;
    double theta;
} Polar_vector;

#endif //EXERCISE3_GEOMETRY_H
