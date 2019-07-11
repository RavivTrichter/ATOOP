//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H


#include "Destination.h"
#include <vector>
#include <limits>
#include <map>
#include <set>
#include <fstream>
#include "Bus.h"
#include "Rail.h"
#include "Tram.h"
#include "Sprinter.h"

#include "Central.h"
#include "Intercity.h"
#include "Stad.h"
#include "PriorityQueue.h"


class Graph {


public:
    /** Data Members **/

    /* this map holds a string that represents a source Node (Station) and a vector of Destinations for that node */
    std::map< string ,shared_ptr<std::vector<shared_ptr<Destination>>>> StationsMap;

    /* this is a set of vertices -> every Vertex has to be unique */
    std::set<shared_ptr<Station>> Vertices;

    /* A vector that every element in it is a route between two nodes
     * every element is another vector that has all the destinations in the route
     * */
    std::vector<std::vector<weak_ptr<Destination>>> Routes;


    /** Functions **/

    void print(ofstream& of,string&) const; // prints all the Edges in the Graph

    void outbound(const string& sourceNode); // returns all the Vertices a given Station can reach in the graph

    void DFS(weak_ptr<Station> source, Vehicle::VehicleType vehicleType,bool* printed, const string&); // Depth First Search Algorithm

    std::set<shared_ptr<Station>>::iterator findVertex(const string& lookingFor); // returns an iterator to a Vertex in the Vertices set

    //adds an edge to the graph by a given source and destination strings, vehicle type and weight
    void addEdge(const string& sourceString, const string& destinationString , Vehicle::VehicleType vehicleType, const int weight );

    Graph reversedGraph(); // returns a reversed graph

    
    bool checkValidArgumentsForUni(const string& src, const string& dest);

    void shortestPath(const string&, const string&, Vehicle::VehicleType);//Dijkstra's algorithm of finding shortest path between 2 nodes

    /*multi Express function -> allows to move from one vehicle to the other */
    void multiShortestPath(const string& src, const string& dest);
	
	class NodeDoesNotExistException : public exception{
        string name;
    public:
        NodeDoesNotExistException(const string& name){this->name = name; }
        
        virtual const char* what(){return "does not exist in the current network";}
        
        const string& getName()const{ return name;}
    };


private:
	shared_ptr<Station> makeStation(const string& stationName); // with a given string returns an allocated Station

    //with a given string,weight and Vehicle returns an allocated Destination
    shared_ptr<Destination> makeDestination(weak_ptr<Station> destination, int weight, Vehicle::VehicleType,string);

        /*calculates the cost of a given route */
    int calculateCostOfGivenPath(std::vector<weak_ptr<Destination>>&);

    void returnVertexToStandard(); // a function that is runned after DFS,Dijkstra and re-initializes specific data members to standard

        /*This function will find all the paths in the graph between 2 nodes*/
    void FindAllPaths(weak_ptr<Destination> source, weak_ptr<Destination> destination, std::vector<weak_ptr<Destination>>& path);



};


#endif //HW2_GRAPH_H
