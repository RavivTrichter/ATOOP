//
// Created by raviv on 19/05/18.
//

#include "Oranjestad.h"

Oranjestad::Oranjestad(int num_of_arguments, char **strings_of_arguments) { //C'tor
    init(num_of_arguments,strings_of_arguments);
}

void Oranjestad::init(int num_of_arguments, char **strings_of_arguments) { // initializes all the Vertices and Edges in the graph
    input.insertToGraph(graph,num_of_arguments,strings_of_arguments);
}


/* prints all the nodes in the graph that can reach the given source node (represented by a string) */
void Oranjestad::inbound(const string &sourceNode) {
    Graph G = graph.reversedGraph();
    G.outbound(sourceNode);
}



/**  Getters & Setters  **/

const Graph& Oranjestad::getGraph() const {
    return graph;
}

const Input& Oranjestad::getInput() const {
    return input;
}

void Oranjestad::run() {
    string command;
    string path;
    istringstream iss;
    while (getline(cin, command)) {
        try {
            if (command.length() == 0)
                continue;
            istringstream iss(command);/*Separate the input of user by spaces*/
            std::vector<std::string> inputFromUser((std::istream_iterator<std::string>(iss)),
                                                   std::istream_iterator<std::string>());
            if("load" == inputFromUser[0]){
                if(inputFromUser.size() != 2){
                    throw Input::NumberOfArgumentsException();
                }
                input.insertToGraphOneLine(graph, inputFromUser[1].c_str());
                cout << "Update was successful." << endl;

            }
            else if("outbound" == inputFromUser[0]){
                if(inputFromUser.size() != 2){
                    throw Input::NumberOfArgumentsException();
                }
                graph.outbound(inputFromUser[1]);
            }
            else if("inbound" == inputFromUser[0]){
                if(inputFromUser.size() != 2){
                    throw Input::NumberOfArgumentsException();
                }
                inbound(inputFromUser[1]);
            }
            else if("uniExpress" == inputFromUser[0]){
                if(inputFromUser.size() != 3){
                    throw Input::NumberOfArgumentsException();
                }
                if(graph.checkValidArgumentsForUni(inputFromUser[1],inputFromUser[2]));
                cout << "Bus: "; graph.shortestPath(inputFromUser[1], inputFromUser[2], Vehicle::Bus);
                cout << "Tram: "; graph.shortestPath(inputFromUser[1], inputFromUser[2], Vehicle::Tram);
                cout << "Sprinter: "; graph.shortestPath(inputFromUser[1], inputFromUser[2], Vehicle::Sprinter);
                cout << "Rail: "; graph.shortestPath(inputFromUser[1], inputFromUser[2], Vehicle::Rail);
            }
            else if("multiExpress" == inputFromUser[0]){
                if(inputFromUser.size() != 3){
                    throw Input::NumberOfArgumentsException();
                }
                graph.multiShortestPath(inputFromUser[1], inputFromUser[2]);
            }
            else if("print" == inputFromUser[0]){
                graph.print(input.getOutPutFile(),input.getFileName());
            }
            else if("QUIT" == inputFromUser[0]){
                return;
            }
            else{
                throw Input::CommandNotFoundException();
            }
        }catch(Input::NumberOfArgumentsException& e){cerr << "The number of arguments doesn't match the command" << endl;}
        catch(Input::CommandNotFoundException& e){cerr << "Command not found" << endl;}
        catch(Graph::NodeDoesNotExistException& e){cerr << e.getName()<< " " << e.what() << endl;}
    }
}
