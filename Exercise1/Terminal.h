//
// Created by raviv on 29/03/18.
//

#ifndef TERMINAL_TERMINAL_H
#define TERMINAL_TERMINAL_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Directory.h"
#include "FolderObj.h"
#include "FileObj.h"

class Terminal {

public:

    Terminal(){}

    int hashing(string) const;

    void run();


};


#endif //TERMINAL_TERMINAL_H
