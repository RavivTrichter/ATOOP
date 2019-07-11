//
// Created by Admin on 19/06/2018.
//

#include "Model.h"
#include "ShipFactory.h"

//Ctor
Model::Model() : time(0) {
    Point p(50,5);
    portVec.emplace_back(make_shared<Port>("Nagoya",p,1000000,1000)); // creating Nagoya by default
    shipFactory = std::make_shared<ShipFactory>(); // initializes the shipFactory data member
}


//iterating on both vectors and updating all the elements
void Model::update() {
    time++; // incrementing time every update
    for (int i = 0; i < shipVec.size(); ++i)
        shipVec[i]->update();
    for (int i = 0; i < portVec.size(); ++i)
        portVec[i]->update();
}


//with given arguments adding a new port to the vector
void Model::addPort(const string portName, const Point &pos, const int GasStoke, const int produce) {
    portVec.emplace_back(new Port(portName,pos,GasStoke,produce));
}


//with given arguments adding a ship to the vector
void Model::addShip(const string &shipType, const string &shipName, Point &pos, int resOatt, int rangeOcap) {
    shipVec.emplace_back(shipFactory->getShip(shipType,shipName,pos,resOatt,rangeOcap));
}


// prints all objects status
void Model::printAllObjectsStatus() const{
    for (auto tmpPort : portVec)
        tmpPort->printStatus();
    for(auto tmpShip : shipVec)
        tmpShip->printStatus();
}

//iterates on all the ship vector and returns the ship if found, else it returns an iterator to the end of the vector
std::vector<shared_ptr<Ship>>::iterator Model::findShip(const string &name) {
    auto beg = shipVec.begin();
    auto end = shipVec.end();
    while(beg != end) {
        if((*beg)->getName() == name)
            return beg;
        beg++;
    }
    return beg;
}
//iterates on all the port vector and returns the port if found, else it returns an iterator to the end of the vector
std::vector<shared_ptr<Port>>::iterator Model::findPort(const string &name) {
    auto beg = portVec.begin();
    auto end = portVec.end();
    while(beg != end) {
        if((*beg)->getPortName() == name)
            return beg;
        beg++;
    }
    return beg;
}


/*Given a go command, iterating on all the commands in the vector and executing them */
void Model::go() {

    Point point;


    for (auto Command : vectorOfCommands) {
        try {
            if (Command[1] == "course") {
                (*findShip(Command[0]))->Moving(std::stod(Command[2]), std::stoi(Command[3]));
            } else if (Command[1] == "position") {
                point.x = std::stod(Command[2]);
                point.y = std::stod(Command[3]);
                (*findShip(Command[0]))->Moving(point, std::stoi(Command[4]));
            } else if (Command[1] == "destination") {
                (*findShip(Command[0]))->Moving((*findPort(Command[2])), std::stoi(Command[3]));
            } else if (Command[1] == "load_at") {
                (*findShip(Command[0]))->load_at((*findPort(Command[2])));
            } else if (Command[1] == "unload_at") {
                (*findShip(Command[0]))->unload_at((*findPort(Command[2])), std::stoi(Command[3]));
            } else if (Command[1] == "dock_at") {
                (*findShip(Command[0]))->dock((*findPort(Command[2])));
            } else if (Command[1] == "refuel") {
                (*findShip(Command[0]))->refuel();
            } else if (Command[1] == "stop") {
                (*findShip(Command[0]))->stop();
                stopThisShip(Command[1]);
            } else if (Command[1] == "attack") {
                (*findShip(Command[0]))->attack((*findShip(Command[2])));
            }
        }catch(MyExceptions::ShipStatusException& sse){
            sse.print();
        }catch(MyExceptions::ShipRefuelException& sre){
            sre.print();
        }catch(MyExceptions::OutOfRangeException& ooe){
            ooe.print();
        }

    }
    vectorOfCommands.clear();
    update();
}

void Model::stopThisShip(const string &shipName) { // erasing all the future commands of this ship
    for (int i = 0; i < vectorOfCommands.size(); ++i) {
            if(vectorOfCommands[i][0] == shipName){ // in ship commands all the ships are the first word
                vectorOfCommands.erase(vectorOfCommands.begin() + i);
                break;
            }
    }
}

void Model::sortVectorOfPort() {//sorting vector of ports
    sort(portVec.begin(), portVec.end(), [](const shared_ptr<Port> a, const shared_ptr<Port> b) -> bool {
         return a->getPortName() < b->getPortName();
     });
}


/* This function get's a two points that represent a gap between two points in the map
 * OIt checks first randomly the ports if there is a point in the range and then the ships
 *
 * */
string Model::BullsEye(const Point &start, const Point& end) {
    string returnValueString = ". "; // init to a dot and space for the map


    //Lambda that checks if there is a port that his position is between the start and end point
    auto portObj = std::find_if(Model::getInstance().getPortVec().begin(),Model::getInstance().getPortVec().end(),[&start, &end] (shared_ptr<Port> a) ->bool {
        return ((a->getPosition().x >= start.x && a->getPosition().x < end.x) && (a->getPosition().y >= start.y && a->getPosition().y < end.y));});

    if(portObj == Model::getInstance().getPortVec().end()){ // if there is not so we check the ships but if there is portObj != end and we return that ports 2 chars name
        //Lambda that checks if there is a ship in the range of start and end
        auto shipObj = std::find_if(Model::getInstance().getShipVec().begin(),Model::getInstance().getShipVec().end(),[&start,&end](shared_ptr<Ship> s)->bool {
            return ((s->getTrackBase().getPosition().x >= start.x  && s->getTrackBase().getPosition().x < end.x) &&
                    (s->getTrackBase().getPosition().y >= start.y && s->getTrackBase().getPosition().y < end.y)); });
        if(shipObj == Model::getInstance().getShipVec().end()) // if there is not so we know that there isnt a ship or a vec so we return thr empty String ". "
            return returnValueString;
        returnValueString = (*shipObj)->getName(); // there is a ship that is in the range so we return the ships name
        return returnValueString.substr(0,2);
    }
    //there is a port so we return it's name
    returnValueString = (*portObj)->getPortName();
    return returnValueString.substr(0,2);

}

Model& Model::getInstance() { // static function, constructs and destructs this instance one time -> Meyers singleton
    static Model m;
    return m;
}

/** Getters **/

vector<vector<string>> &Model::getVectorOfCommands() {
    return vectorOfCommands;
}


const vector<shared_ptr<Port>> &Model::getPortVec() const {
    return portVec;
}

int Model::getTime() const {
    return time;
}

const vector<shared_ptr<Ship>> &Model::getShipVec() const {
    return shipVec;
}
