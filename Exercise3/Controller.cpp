//
// Created by raviv on 6/17/18.
//

#include <fstream>
#include "Controller.h"

using namespace std;


/*Ctor, gets argc and argv. Initializes Model with getInstance and sends it to initialize view
 * after that initializes the ports into the data structure and checks their validation */
Controller::Controller(int argc, char **argv) : view(Model::getInstance()) {
    initPorts(argc,argv);
    run();
}

/*a function to initialize the ports we get from input file */
void Controller::initPorts(int argc, char **argv) {
    if(argc < 2 ){ // has to get an input file to initialize the ports
        cerr << "Not enough files for program\n Aborting program\n";
        exit(1);
    }
    string line = "";
    ifstream file(argv[1]);
    try{
        while(getline(file,line)){
            istringstream iss(line);/*Separate the input of user by spaces*/
            std::vector<std::string> input((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>()); // holds the line seperated " "
            input[1].erase(input[1].begin(),input[1].begin() + 1); // erasing '(' from X
            input[1].pop_back(); // erasing the ',' from X
            input[2].pop_back(); // erasing the ')' from Y
            if(std::find_if(input[0].begin(), input[0].end(), [](char c) -> bool { return !std::isalpha(c); }) != input[0].end() ){
                throw runtime_error("");
            }
            Model::getInstance().addPort(input[0],Point(std::stod(input[1]),std::stod(input[2])),std::stoi(input[3]),std::stoi(input[4]));
            line = "";
        }

    }catch(invalid_argument& ia){
        cerr << "Cannot parse a non-digit character into a double or an int\n Aborting program\n";
        exit(1);
    }catch(runtime_error& re){
        cerr << "Name of Port Can't contain characters different than letters\n Aborting program\n";
        exit(1);
    }
    Model::getInstance().sortVectorOfPort();

}
//A func that caclulates the sum of an ascii string -> for the commands and comuunication with user (There are no strings with same ascii sum value !!)
int Controller::hashing(std::string name){
    int cnt = 0;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (unsigned int i = 0; i < name.size(); ++i)
        cnt += name[i];
    return cnt;
}


/*
 * run handles the communication with the user. We hold a vector of strings for the command and it's arguments .
 * for each argument of the command there is exactly the right input valid check for example for a double we check that there is only numbers and a point.
 * If there is an invalid input we throw an exception and catch it at the bottom of the function
 * */

void Controller::run() {
    std::string  line,tmp, hashMe;
    const int MAX_SHIP_NAME = 12;
    shared_ptr<Ship> tmpShip;
    Point point;
    int resOatt, rangeOcap,speed,num;
    double zoom;
    bool inLoop = true;
    initVectorCommands();


    typedef  enum {    DEFAULT = 741, SIZE = 443, ZOOM = 453, PAN = 319, SHOW = 449, STATUS = 676, GO = 214, CREATE = 628, COURSE = 657, POSITION = 885,
        DESTINATION = 1186, LOAD_AT = 724, UNLOAD_AT = 951, DOCK_AT = 725, ATTACK = 632, REFUEL = 643, STOP = 454, EXIT = 442 } InputCommand;
        while(inLoop){
            try{
                line = "";
                cout << "Time " << Model::getInstance().getTime() << ": Enter Command: " ;
                getline(cin,line);
                stringstream ss(line);
                std::vector<std::string> inputStringVector((std::istream_iterator<std::string>(ss)), std::istream_iterator<std::string>());
                if(inputStringVector.size() == 0)
                    continue;
                if(find(vecOfCommands.begin(),vecOfCommands.end(),inputStringVector[0]) != vecOfCommands.end())
                    hashMe = inputStringVector[0];
                else if(find(vecOfCommands.begin(),vecOfCommands.end(),inputStringVector[1]) != vecOfCommands.end())
                    hashMe = inputStringVector[1];
                else
                    throw MyExceptions::InvalidInput("Command not found");


                switch(hashing(hashMe)) {
                    case InputCommand::DEFAULT:
                        if(inputStringVector.size() != 1)
                            throw MyExceptions::InvalidInput("Default doesn't need any arguments");
                        view.defaultParam();
                        break;


                    case InputCommand::SIZE:
                        if(inputStringVector.size() != 2)
                            throw MyExceptions::InvalidInput("Size needs exactly 2 arguments");
                        if(!isInteger(inputStringVector[1]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character into a integer that has to be positive");
                        num = std::stoi(inputStringVector[1]);
                        if(num > 30 || num <= 6)
                            throw MyExceptions::InvalidArgument("Error : size of the map need to be between 7 and 30");
                        view.setSize(num);
                        break;


                    case InputCommand::ZOOM:
                        if(inputStringVector.size() != 2)
                            throw MyExceptions::InvalidInput("Zoom needs exactly 2 arguments");
                        if(!isDouble(inputStringVector[1]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character into a double");
                        zoom = std::stod(inputStringVector[1]);
                        if(zoom < 0)
                            throw MyExceptions::InvalidArgument("New zoom size must be a positive double");
                        view.setScale(zoom);
                        break;


                    case InputCommand::PAN:
                        if(inputStringVector.size() != 3)
                            throw MyExceptions::InvalidInput("Pan needs exactly 3 arguments");
                        if(!isDouble(inputStringVector[1]) || !isDouble(inputStringVector[2]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character into a double");
                        view.setAxis(Point(std::stod(inputStringVector[1]), std::stod(inputStringVector[2])));
                        break;


                    case InputCommand::SHOW:
                        if(inputStringVector.size() != 1)
                            throw MyExceptions::InvalidInput("Show doesn't need any arguments");
                        view.show();
                        break;


                    case InputCommand::STATUS:
                        if(inputStringVector.size() != 1)
                            throw MyExceptions::InvalidArgument("Status doesn't need any arguments");
                        Model::getInstance().printAllObjectsStatus();
                        break;


                    case InputCommand::GO:
                        if(inputStringVector.size() != 1)
                            throw MyExceptions::InvalidArgument("Go doesn't need any arguments");
                        Model::getInstance().go();
                        break;


                    case InputCommand::CREATE:


                        if(inputStringVector.size() < 6 || inputStringVector.size() > 7)
                            throw MyExceptions::InvalidArgument("Create needs 7 or 6 arguments");

                        if(Model::getInstance().findShip(inputStringVector[1]) != Model::getInstance().getShipVec().end()) // checks if the ship already exists
                            throw MyExceptions::InvalidInput("Ship already exists");
                        if(inputStringVector[1].size() > MAX_SHIP_NAME)
                            throw MyExceptions::InvalidInput("Ship name can be maximum 12 characters");

                        if(inputStringVector[2] != "Cruiser" && inputStringVector[2] != "Freighter" && inputStringVector[2] != "Patrol_boat")
                            throw MyExceptions::InvalidInput("No such type of ship");

                        inputStringVector[3].erase(inputStringVector[3].begin(),inputStringVector[3].begin() + 1); // erasing '(' from double
                        if(inputStringVector[3][inputStringVector[3].size() - 1] == ',')
                            inputStringVector[3].pop_back();
                        inputStringVector[4].pop_back(); // erasing ')'
                        if(!isDouble(inputStringVector[3]) || !isDouble(inputStringVector[4]) || !isInteger(inputStringVector[5]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to a double or an int");

                        if(inputStringVector[2] != "Patrol_boat" && !isInteger(inputStringVector[6]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to a double or an int");

                        point.x = std::stod(inputStringVector[3]);
                        point.y = std::stod(inputStringVector[4]);

                        resOatt = std::stoi(inputStringVector[5]);//throws invalid_argument of c++ std exceptions if fails

                        if(inputStringVector[2] != "Patrol_boat"){
                            rangeOcap = std::stoi(inputStringVector[6]);
                            Model::getInstance().addShip(inputStringVector[2],inputStringVector[1],point,resOatt,rangeOcap);
                        }else {
                            Model::getInstance().addShip(inputStringVector[2], inputStringVector[1], point, resOatt);
                        }
                        break;




                    case InputCommand::COURSE:

                        if(inputStringVector.size() != 4) // exactly 4 arguments
                            throw MyExceptions::InvalidArgument("Course needs 4 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");

                        tmpShip = (*Model::getInstance().findShip(inputStringVector[0]));
                        if(!isDouble(inputStringVector[2]) || !isDouble(inputStringVector[3])) // checking that we got numbers
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to a double or an int");
                        speed = stoi(inputStringVector[3]);
                        if( (tmpShip->getTypeName() == Ship::PB && MAX_SPEED_PATROL < speed)  ||
                            (tmpShip->getTypeName() == Ship::CR && MAX_SPEED_CRUISER < speed) ||
                            (tmpShip->getTypeName() == Ship::FR && MAX_SPEED_FREIGHTER < speed))
                            throw MyExceptions::InvalidArgument("Speed given is more than this ship can handle");

                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector); //inserting to the vector that holds all the commands for next time update
                        break;




                    case InputCommand::POSITION:

                        if(inputStringVector.size() != 5) // exactly 5 arguments
                            throw MyExceptions::InvalidArgument("Position needs 5 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        tmpShip = (*Model::getInstance().findShip(inputStringVector[0]));

                        inputStringVector[2].erase(inputStringVector[2].begin(),inputStringVector[2].begin() + 1); // erasing '(' from double
                        if(inputStringVector[2][inputStringVector[2].size() - 1] == ',')
                            inputStringVector[2].pop_back();
                        inputStringVector[3].pop_back(); // erasing ')'
                        if( !isDouble(inputStringVector[2]) || !isDouble(inputStringVector[3]) || !isInteger(inputStringVector[4]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to a double or an int");
                        speed = stoi(inputStringVector[4]);
                        if( (tmpShip->getTypeName() == Ship::PB && MAX_SPEED_PATROL < speed)  ||
                            (tmpShip->getTypeName() == Ship::CR && MAX_SPEED_CRUISER < speed) ||
                            (tmpShip->getTypeName() == Ship::FR && MAX_SPEED_FREIGHTER < speed))
                            throw MyExceptions::InvalidArgument("Speed given is more than this ship can handle");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;





                    case InputCommand::DESTINATION:

                        if(inputStringVector.size() != 4)
                            throw MyExceptions::InvalidArgument("Destination needs exactly 4 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");

                        tmpShip = (*Model::getInstance().findShip(inputStringVector[0]));

                        if(Model::getInstance().findPort(inputStringVector[2]) == Model::getInstance().getPortVec().end()) {
                            throw MyExceptions::InvalidArgument("Port doesn't exist");
                        }
                        if(!isInteger(inputStringVector[3])) {
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to an integer");
                        }
                        speed = stoi(inputStringVector[3]);
                        if( (tmpShip->getTypeName() == Ship::PB && MAX_SPEED_PATROL < speed)  ||
                            (tmpShip->getTypeName() == Ship::CR && MAX_SPEED_CRUISER < speed) ||
                            (tmpShip->getTypeName() == Ship::FR && MAX_SPEED_FREIGHTER < speed)) {
                            throw MyExceptions::InvalidArgument("Speed given is more than this ship can handle");
                        }
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);

                        break;




                    case InputCommand::LOAD_AT:

                        if(inputStringVector.size() != 3)
                            throw MyExceptions::InvalidArgument("Load at needs exactly 3 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        if(Model::getInstance().findPort(inputStringVector[2]) == Model::getInstance().getPortVec().end())
                            throw MyExceptions::InvalidArgument("Port doesn't exist");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::UNLOAD_AT:

                        if(inputStringVector.size() != 4)
                            throw MyExceptions::InvalidArgument("Unload at needs exactly 4 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        if(Model::getInstance().findPort(inputStringVector[2]) == Model::getInstance().getPortVec().end())
                            throw MyExceptions::InvalidArgument("Port doesn't exist");
                        if(!isInteger(inputStringVector[3]))
                            throw MyExceptions::ParsingError("Cannot parse a non-digit character to an integer");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::DOCK_AT:
                        if(inputStringVector[1] != "dock_at") // checking command validation
                            throw MyExceptions::InvalidInput("Command not found");
                        if(inputStringVector.size() != 3)
                            throw MyExceptions::InvalidArgument("Dock at needs exactly 3 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        if(Model::getInstance().findPort(inputStringVector[2]) == Model::getInstance().getPortVec().end())
                            throw MyExceptions::InvalidArgument("Port doesn't exist");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::ATTACK:

                        if(inputStringVector.size() != 3)
                            throw MyExceptions::InvalidArgument("Attack needs exactly 3 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end() ||
                           Model::getInstance().findShip(inputStringVector[2]) == Model::getInstance().getShipVec().end()) // checks if the ship exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        if((*Model::getInstance().findShip(inputStringVector[0]))->getTypeName() != Ship::CR)
                            throw MyExceptions::ShipStatusException("Only Cruiser ships can attack");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::REFUEL:

                        if(inputStringVector.size() != 2)
                            throw MyExceptions::InvalidArgument("Refuel needs exactly 2 arguments");
                        if(Model::getInstance().findShip(inputStringVector[0]) == Model::getInstance().getShipVec().end()) // checks if the ship already exists
                            throw MyExceptions::InvalidInput("Ship doesn't exist");
                        if((*(Model::getInstance().findShip(inputStringVector[0])))->getTypeName() != Ship::FR)
                            throw MyExceptions::InvalidArgument("Cannot refuel a patrol boat");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::STOP:

                        if(inputStringVector.size() != 2)
                            throw MyExceptions::InvalidArgument("Stop needs exactly 2 arguments");
                        Model::getInstance().getVectorOfCommands().emplace_back(inputStringVector);
                        break;




                    case InputCommand::EXIT:
                        inLoop = false;
                        break;
                    default:
                        cout << "Command not found\n";

            } // switch
        }  catch (MyExceptions::InvalidInput& ii) {
            ii.print();
        }catch (MyExceptions::InvalidArgument& ia){
            ia.print();
        }catch(MyExceptions::ParsingError& pe){
            pe.print();
        }catch (MyExceptions::ShipStatusException& s){
            s.print();
        }catch (MyExceptions::ShipRefuelException& s){
            s.print();
        }catch (MyExceptions::OutOfRangeException& s){
            s.print();
        }catch(...){
                cout << "Problem occured\n";
            }
    }//while

} // functon run



/* Here we initialize all the possible commands from the user, and in function run we check that the command given is a contained in a vector called vecOfCommands.
 * if not it we throw an exception*/
void Controller::initVectorCommands() {
    vecOfCommands.emplace_back("create");
    vecOfCommands.emplace_back("course");
    vecOfCommands.emplace_back("go");
    vecOfCommands.emplace_back("status");
    vecOfCommands.emplace_back("pan");
    vecOfCommands.emplace_back("default");
    vecOfCommands.emplace_back("size");
    vecOfCommands.emplace_back("zoom");
    vecOfCommands.emplace_back("show");
    vecOfCommands.emplace_back("position");
    vecOfCommands.emplace_back("destination");
    vecOfCommands.emplace_back("load_at");
    vecOfCommands.emplace_back("unload_at");
    vecOfCommands.emplace_back("dock_at");
    vecOfCommands.emplace_back("attack");
    vecOfCommands.emplace_back("refuel");
    vecOfCommands.emplace_back("stop");
    vecOfCommands.emplace_back("exit");

}
// function run()

