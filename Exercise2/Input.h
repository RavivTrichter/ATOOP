//
// Created by Admin on 19/05/2018.
//

#ifndef HW2_INPUT_H
#define HW2_INPUT_H


#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Vehicle.h"
#include "Graph.h"
#include "Bus.h"
#include "Rail.h"
#include "Tram.h"
#include "Sprinter.h"

class Input {
public:
    Input()= default;

    Input(const Input& rhs) = default;//copy c'tor

    /*recieves all the input files and rearranges them */
    void insertToGraph(Graph& graph, const int num_of_arguments, char **strings_of_arguments);
    /* checks valid line in the file */
    void insertToGraphOneLine(Graph& graph, const char* fileName);

    void ConfigureFile(const char* filename);/*responsible for the configure file */

    string& getFileName();

    void setFileName(const string& rhs);

    ofstream& getOutPutFile() const { return *outPutFile;}
    /*  Exceptions classes*/

    class CommandNotFoundException{};

    class NumberOfArgumentsException{};

    class FileNameException{};

    class FileInputException : public exception{};

private:
	int hashing(string&);/*function that sums the ASCII of a given string */

	void LineToEdge(Graph& ,string&, Vehicle::VehicleType); /* converts a line in the file to an edge in the graph */

	Vehicle::VehicleType checkNameOfFile(const char* fileName);


    unique_ptr<std::ofstream> outPutFile;

    string fileName;

};


#endif //HW2_INPUT_H
