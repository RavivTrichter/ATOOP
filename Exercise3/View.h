//
// Created by Admin on 19/06/2018.
//

#ifndef EXERCISE3_VIEW_H
#define EXERCISE3_VIEW_H

#include "Model.h"


class View {

public:

    /******** The big 5 *********/
    View(Model& mo) : model(mo), size(25), scale(2.0), axis(Point(-10.00,-10.00)) {} // Ctor

    View(const View&) = default;

    View(View&&) = default;

    View& operator=(const View&) = default;

    View& operator=(View&&) = default;

    virtual ~View() = default;

    void defaultParam(); // returns to default parameters

    void show(); // prints the map to the screen

    void setSize(int size); // sets the size

    void setScale(double scale); // sets the scale

    void setAxis(const Point &axis); // sets the origin axis

    int HowManyChars(int num); // returns how many characters there are in a given num and if it is negative or positive


private:

    Model& model;

    int size;

    double scale;

    Point axis;

};


#endif //EXERCISE3_VIEW_H
