//
// Created by Admin on 19/05/2018.
//
#include "Input.h"

bool globalFlagForValidInputFile = false;//a boolean flag that tells us if we have at least one valid input file


/* this function gets input from files and builds the graph, and configures the default times  */
void Input::insertToGraph(Graph& graph, const int num_of_arguments, char **strings_of_arguments) {
    int i = 2;
    for( ; i<num_of_arguments && strcmp(strings_of_arguments[i],"-c") && strcmp(strings_of_arguments[i],"-o"); i++){
        insertToGraphOneLine(graph,strings_of_arguments[i]);
    }
    if(!globalFlagForValidInputFile) {
        cerr << "Invalid Input Files \n";
        exit(1);
    }
    if(i < num_of_arguments) {//there is configure file or output file or both
        if (!strcmp(strings_of_arguments[i], "-c")) {
            i++;
            try {
                ConfigureFile(strings_of_arguments[i++]);
            }catch(FileInputException& e){
                cerr << "file configuration does not good" << endl;
            }
        }
    }
    if ( i < num_of_arguments && !strcmp(strings_of_arguments[i],"-o")){
        outPutFile = unique_ptr<std::ofstream>(new ofstream(strings_of_arguments[++i],ios::out|ios::app));
        fileName = strings_of_arguments[i];

    }
    else{
        outPutFile = unique_ptr<std::ofstream>(new ofstream("output.dat",ios::out|ios::app)); // default
        fileName = "output.dat";
    }
    outPutFile->close();
}


/* a function that sums the ASCII of the string's digit */
int Input::hashing(string& name){
    int cnt = 0;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (unsigned int i = 0; i < name.size(); ++i)
        cnt += name[i];
    return cnt;
}

/* gets a file and changes the relevant data members in the classes  */
void Input::ConfigureFile(const char *filename) {
    ifstream file(filename);
    string line,name;
    int time;
    enum { BUS = 330 ,RAIL = 424 , TRAM = 436 , SPRINTER = 887 , STAD = 428 , CENTRAL = 745 , INTERCITY = 987};

    while(getline(file,line)){
        stringstream ss(line);
        name = "";
        ss >> name;
        time = 0;

        switch( hashing(name) ) {


            case BUS:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "bus" || time < 0)
                    throw FileInputException(); //
                Bus::busTime = time;
                break;


            case RAIL:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "rail" || time < 0)
                    throw FileInputException();

                Rail::railTime = time;
                break;


            case TRAM:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "tram" || time < 0)
                    throw FileInputException(); //
                Tram::tramTime = time;
                break;


            case SPRINTER:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "sprinter" || time < 0)
                    throw FileInputException(); //
                Sprinter::sprinterTime = time;
                break;


            case STAD:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "stad" || time < 0)
                    throw FileInputException(); //
                Stad::stadTime = time;
                break;


            case CENTRAL:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "central" || time < 0)
                    throw FileInputException(); //
                Central::centralTime = time;
                break;

            case INTERCITY:
                if(!(ss >> time)) // checking that input is numbers
                    throw FileInputException(); // second place is not a number
                if(name != "intercity" || time < 0)
                    throw FileInputException(); //
                Intercity::interCityTime = time;
                break;
        }//switch
    } // while

}

/* gets a file and vehicle type, then inerts all the edges into the graph with the vehicle type */
void Input::insertToGraphOneLine(Graph &graph, const char *fileName) {
    std::ifstream inputFile;
    Vehicle::VehicleType vehicleType;
    try {
        vehicleType = checkNameOfFile(fileName); // tram or rail or bus or sprinter
        inputFile.open(fileName);

    }catch (FileNameException& e){
        cerr << "Problem with file name\n";
        return;
    }
    if(!inputFile.is_open()) {
        cerr << "ERROR opening the specified file." << endl;
        return;
    }
    string line;
    while(getline(inputFile,line))
        try{
            LineToEdge(graph,line,vehicleType); //checkinmg the stations names and inserting the edges
        }catch(FileInputException& e){
            cerr << "Wrong input in file" << endl;
            exit(1);
        }
    globalFlagForValidInputFile = true;
}

/* converting a line from the file to an edge in the graph */
void Input::LineToEdge(Graph &graph, string &line, Vehicle::VehicleType vehicleType) {
    stringstream ss(line);
    string src,dest;
    int weight;
    ss >> src;
    ss >> dest;
    if(src.length() > 16 || dest.length() > 16)
        throw FileInputException();
    if(!(ss >> weight) && weight < 0){
        throw FileInputException();
    }
    graph.addEdge(src,dest,vehicleType,weight); // input is valid, inserting edge
}

/* with given file name, checks which vehicle the file represents */
Vehicle::VehicleType Input::checkNameOfFile(const char *fileName) {
    string name(fileName);
    if((name.find("sprinter")) == 0 ){
        return Vehicle::VehicleType::Sprinter;
    }
    else if((name.find("tram")) == 0 ){
        return Vehicle::VehicleType::Tram;
    }
    else if((name.find("rail")) == 0 ){
        return Vehicle::VehicleType::Rail;
    }
    else if((name.find("bus")) == 0 ){
        return Vehicle::VehicleType::Bus;
    } else throw FileNameException();
}


string& Input::getFileName() { return fileName;}

void Input::setFileName(const string& rhs) { fileName = rhs;}


