//
// Created by raviv on 19/05/18.
//

#ifndef HW2_ORANJESTAD_H
#define HW2_ORANJESTAD_H


#include "Graph.h"
#include "Input.h"
#include <iterator>



/** This object describes the public transport in the city Oranjestaad
 *  it connects all the classes in this project and manages them
 *
 * **/

class Oranjestad {
public:
    Oranjestad(int num_of_arguments, char **strings_of_arguments); // C'tor

    void inbound(const string& sourceNode); // prints all the nodes that can reach the source node

    void run();

    /** Getters and Setters **/

    const Graph &getGraph() const;

    const Input & getInput() const;

private:

	void init(int num_of_arguments, char **strings_of_arguments); //initializes the graph
	
    Graph graph;

    Input input; // Manages the input


};


#endif //HW2_ORANJESTAD_H
