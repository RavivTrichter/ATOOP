//
// Created by raviv on 13/04/18.
//

#ifndef TERMINAL_FOLDEROBJ_H
#define TERMINAL_FOLDEROBJ_H

#include <iostream>
#include "FileObj.h"



using namespace std;


class FolderObj {
public:

    FolderObj(string name, string path) : name(name), path(path){} // C'tor

    FolderObj(const FolderObj& rhs) : name(rhs.name), path(rhs.path) {} // Copy C'tor

    ~FolderObj(){}

    FolderObj operator=(const FolderObj& rhs);


    const string &getName() const;

    void setName(const string &name);

    const string &getPath() const;

    void setPath(const string &path);



private:

    string name,path;

};


#endif //TERMINAL_FOLDEROBJ_H
