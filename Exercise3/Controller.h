//
// Created by raviv on 6/17/18.
//

#ifndef EXERCISE3_CONTROLLER_H
#define EXERCISE3_CONTROLLER_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include "Model.h"
#include "Geometry.h"
#include "MyExceptions.h"
#include "View.h"

using namespace std;

class Controller {

public:


    /******** The big 5 *********/
    Controller(int argc, char* argv[]); // Ctor -> initializes model and view as well

    Controller(const Controller&) = default;

    Controller(Controller&&) = default;

    Controller& operator=(const Controller&) = default;

    Controller& operator=(Controller&&) = default;

    virtual ~Controller() = default;

    void initPorts(int argc, char* argv[]); //initializes the ports from argv

    void run(); // function that communicates with user

    /** Saving the Max Speed of every boat**/

    static const int MAX_SPEED_PATROL = 15;

    static const int MAX_SPEED_FREIGHTER = 40;

    static const int MAX_SPEED_CRUISER = 75;

private:
    int hashing(std::string);

    void initVectorCommands(); // initializes the vector with possible commands from user by a string

    inline bool isDouble(const std::string& s) { // lambda func that checks if a given string is a double
        return !s.empty() &&
               std::find_if(s.begin(), s.end(), [](char c) { return !(std::isdigit(c) || c == '.' || c == '-'); }) == s.end();
    }

    inline bool isInteger(const std::string& s) {// lambda func that checks if a given string is am integer (all integers in the program must be positive)
        return !s.empty() &&
               std::find_if(s.begin(), s.end(), [](char c) { return !(std::isdigit(c)); }) == s.end();
    }

    std::vector<string> vecOfCommands;

    View view;
};


#endif //EXERCISE3_CONTROLLER_H
