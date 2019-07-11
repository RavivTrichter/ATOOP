//
// Created by raviv on 13/04/18.
//

#include "FolderObj.h"



const string &FolderObj::getName() const {
    return name;
}

void FolderObj::setName(const string& name) {
    this->name = name;
}

const string &FolderObj::getPath() const {
    return path;
}

void FolderObj::setPath(const string &path) {
    this->path = path;
}

FolderObj FolderObj::operator=(const FolderObj &rhs) {
    if(this != &rhs){
        name = rhs.name;
        path = rhs.path;
    }
    return *this;
}
