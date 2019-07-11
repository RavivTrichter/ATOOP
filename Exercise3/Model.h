//

//

#ifndef EXERCISE3_MODEL_H
#define EXERCISE3_MODEL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "AbstractFactory.h"
#include "Ship.h"


class Model {
public:
    //void create(string shipName, TrackBase::MovingType type, const Point& pos, int resOatt, int rangeOcap = 0 );

    /******** The big 5 *********/

    Model(const Model&) = delete;

    Model(Model&&) = delete;

    Model& operator=(const Model&) = delete;

    Model& operator=(Model&&) = delete;

    ~Model() = default;

    void go(); // Go command -> executes all the commands that are in vecOfCommands at Controller

    void update(); // updates all the ships and ports (fuel, position in map etc.)

    void addPort(const std::string portName,const Point& pos, const int GasStoke, const int produce); // adding a port to the vector according to arguments

    void addShip( const string& shipType ,const string& shipName , Point& pos, int resOatt, int rangeOcap = 0 ); // adding a ship to the shipVectro according to arguments

    void printAllObjectsStatus() const; // printsthe status of all objects in the vectors

    std::vector<shared_ptr<Ship>>::iterator findShip(const string& name); // returns an iterator to the ship by name or to nullptr(end)

    std::vector<shared_ptr<Port>>::iterator findPort(const string& name);// returns an iterator to the port by name or to nullptr(end)

    void stopThisShip(const string& shipName); // given the command stop to a ship, handles all possible situations

    string BullsEye(const Point &start, const Point& end); // returns a string of a port or a ship if the object is in the range between start amnd end -> for printing(View)

    void sortVectorOfPort(); // sorts the port vector by name

    /**    Getters & Setters   **/

    const vector<shared_ptr<Port>> &getPortVec() const;

    static Model& getInstance(); // Singleton (Meyer)

    int getTime() const;

    vector<vector<string>> &getVectorOfCommands();

    int getSizeOfPortVector(){return (int)portVec.size();}

    const vector<shared_ptr<Ship>> &getShipVec() const;


private:
    Model();

    std::vector<shared_ptr<Ship>> shipVec; // vector of all types of ships

    std::vector<shared_ptr<Port>> portVec; // vector that holds all the ports -> initialized at start of the program

    std::shared_ptr<AbstractFactory> shipFactory; // our abstract factory

    std::vector<std::vector<std::string>> vectorOfCommands; // holds all the commands by user

    int time; //holds the current time
};



#endif //EXERCISE3_MODEL_H
