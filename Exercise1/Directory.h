//
// Created by raviv on 30/03/18.
//

#ifndef TERMINAL_DIRECTORY_H
#define TERMINAL_DIRECTORY_H


#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "FolderObj.h"
#include "FileObj.h"
#include "Terminal.h"



/* Sometimes in the code I have folders and sometime directories they are both pointing on the object folder but are named by directories */


using namespace std;

using namespace std::__exception_ptr;

class Directory {

public:

    Directory();

    void ls(std::vector<FolderObj>::iterator, bool); // ls function

    void readFromFile(const string[]); // reads a charcter from a file

    void touchFile(const string);//creates new file

    void writeToFile(const string[]); // writes to a file a given char

    void copyFiles(const string*); // copy the content of a source file to a target file

    void removeFile(const string); // removes a file by a given string

    void moveFile(const string*); // moves the content of a file to an other file and deletes the cource file

    void catFile(const string*) ; // prints the content of a file

    void wcFile(const string* stringArr); // prints the number of chars,words and lines of a given file

    void lnFiles(const string*); // creates a hard link between two files

    void makeDirectory(const string*); // creates a new folder

    void changeDirectory(const string*);//changes the current position in the Terminal

    void removeDirectory(const string*); // removes a file from the vector

    void lsFolders(const string*); // prints the content of a folder (files & folders)

    void LProot(); //prints all the folders and files in the Terminal


    /**  HELP METHODS  **/


    string printNameFile(const string) const ; // prints a file name

    string printNameDir(const string) const; // prints a folder name

    void clearVectors(); // removes all the objects from both vectors

    bool goToFather(); // if rmdir was executed on the current pwd, this func turns pwd to his "father" directory

    vector<FileObj>::iterator findFile(string); // func to find a file in the vector

    vector<FolderObj>::iterator findFolder(string); // func to find a folder in the vector

    string DeCompose(string path); // func to delete all '/' characters form a given string

    void sortFileVectors(); // sorts the file vector

    void sortFolderVectors(); // sorts the folder vector

    bool isContainedFolder(const string,const string) const ; // returns true if a subFolder in an other folder

    bool isContainedFile(const string, const string) const;// returns true if a file is in a folder or sub folder of an other folder

    void deleteSubDirectories(const string papa); // deletes sub folders of a given folder

    void deleteSubFiles(const string papa); //deletes sub files of a given folder

    void isValidFolder(string); // checks the input if the new folder is valid



private:
    string pwd;
public:
    const string &getPwd() const;

    void setPwd(const string &pwd);

private:

    std::vector<FolderObj> FolderVector;

    std::vector<FileObj> FileVector;
};



#endif //TERMINAL_DIRECTORY_H
