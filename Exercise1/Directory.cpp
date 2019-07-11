//
// Created by raviv on 29/03/18.
//

#include "Directory.h"

using namespace std;

using namespace std::__exception_ptr;




Directory::Directory() {
    FolderVector.push_back(FolderObj("V","V/"));
    pwd = "V/";
}


void Directory::readFromFile(const string* stringArray) {
    int pos;

    std::vector<FileObj>::iterator it;

    it = findFile(stringArray[1]); // returns the file, by given string file path
    if (it == FileVector.end())
        throw runtime_error("can't read from from file, file not found\n");
    string name = (*it).getValue()->IsHardLinked == false ? stringArray[2] : (*it).getValue()->linkedFileName;
    stringstream ss(name);// position
    (*it).getValue()->file->open((*it).getName());
    if(!(*it).getValue()->file->is_open())
        throw runtime_error("can't open file\n");
    ss >> pos;
    cout << (*it)[pos] << '\n';
    (*it).getValue()->file->close();
}


void Directory::writeToFile(const string* stringArray) {
    int pos;
    stringstream ss(stringArray[2]);//position
    std::vector<FileObj>::iterator it;

    it = findFile(stringArray[1]); // returns the file, by given string file path
    if (it == FileVector.end())
        throw runtime_error("can't write to file, file not found\n");
    (*it).getValue()->file->open((*it).getName());
    if(!(*it).getValue()->file->is_open())
        throw runtime_error("can't open file\n");
    ss >> pos;
    (*it)[pos] = *(stringArray[3].c_str());// the character I want to write to the file
    (*it).getValue()->file->close();
}


void Directory::touchFile(string stringA) {
    std::vector<FileObj>::iterator it;

    it = findFile(stringA);
    if (it == FileVector.end()) { // the file does not exist
        FileVector.push_back(FileObj(DeCompose(stringA), stringA));
        it = findFile(stringA);
    }
    (*it).touch(); // the file exists
}


void Directory::copyFiles(const string *stringArr) {
    std::vector<FileObj>::iterator src;
    std::vector<FileObj>::iterator trg;

    src = findFile(stringArr[1]);
    trg = findFile(stringArr[2]);
    if (src == FileVector.end())
        throw runtime_error("source file not found\n"); // source file does not exist;
    if (trg == FileVector.end()) {// target file not exist, creating a new one
        FileVector.push_back(FileObj(DeCompose(stringArr[2]),stringArr[2]));
        trg = findFile(stringArr[2]);
        src = findFile(stringArr[1]);
    }
    (*src).getValue()->file->open((*src).getName());
    if(!(*src).getValue()->file->is_open())
        throw runtime_error("can't open file\n");
    (*trg).getValue()->file->open((*trg).getName());
    if(!(*trg).getValue()->file->is_open())
        throw runtime_error("can't open file\n");
    (*src).copy(*trg);
    (*src).getValue()->file->close();
    (*trg).getValue()->file->close();
}



void Directory::removeFile(const string stringArr) {
    unsigned int i;
    for (i = 0; i < FileVector.size(); ++i) {
        if(FileVector[i].getName() == stringArr)
            break;
    }
    if ( i == FileVector.size() )
        throw runtime_error("can't remove file, file not found\n"); //file does not exist;
    std::remove(stringArr.c_str());
    FileVector.erase(FileVector.begin() + i);

}

void Directory::moveFile(const string *stringArr) {
    copyFiles(stringArr);
    std::vector<FileObj>::iterator it = findFile(stringArr[1]);
    removeFile(stringArr[1]);
}


void Directory::catFile(const string *stringArr) {
    std::vector<FileObj>::iterator it;

    it = findFile(stringArr[1]);
    if (it == FileVector.end())
        throw runtime_error("can't print file content, file not found\n"); //file does not exist;
    (*it).cat();
}

void Directory::lnFiles(const string* stringArr) {
    std::vector<FileObj>::iterator src;
    std::vector<FileObj>::iterator trg;

    src = findFile(stringArr[1]);
    trg = findFile(stringArr[2]);
    if(src == FileVector.end())
        throw runtime_error("target file not found\n"); // source file does not exist;
    if(trg == FileVector.end())
        throw runtime_error("link name file not found\n"); // source file does not exist;
    (*src).ln(*trg);
}



void Directory::wcFile(const string *stringArr) {
    std::vector<FileObj>::iterator it;

    it = findFile(stringArr[1]);
    if (it == FileVector.end())
        throw runtime_error("file not found\n"); //file does not exist;
    (*it).wc();
}

void Directory::makeDirectory(const string *stringArr) {
    std::vector<FolderObj>::iterator it;
    isValidFolder(stringArr[1]);
    it = findFolder(stringArr[1]);
    if (it == FolderVector.end())
        FolderVector.push_back(FolderObj(DeCompose(stringArr[1]), stringArr[1]));
    else
        throw invalid_argument("directory already exists\n");
}

void Directory::changeDirectory(const string *stringArr) {
    std::vector<FolderObj>::iterator it;

    it = findFolder(stringArr[1]);
    if (it == FolderVector.end())
        throw runtime_error("can't change directory, folder not found\n");
    setPwd((*it).getPath());
}

void Directory::removeDirectory(const string *stringArr) {
    std::vector<FolderObj>::iterator folderIt;
    std::vector<FileObj>::iterator fileIt;

    folderIt = findFolder(stringArr[1]);
    if(folderIt == FolderVector.end())
        throw runtime_error("can't remove directory, folder not found\n");
    if((*folderIt).getPath() == pwd)
        if(!goToFather())
            throw invalid_argument("can't erase home directory\n");
    sortFileVectors();
    sortFolderVectors();
    deleteSubFiles(((*folderIt).getPath()));
    deleteSubDirectories((*folderIt).getPath());
}


void Directory::lsFolders(const string *stringArr) {
    std::vector<FolderObj>::iterator src;

    sortFileVectors();
    sortFolderVectors();

    src = findFolder(stringArr[1]);
    if(src == FolderVector.end())
        throw runtime_error("folder not found\n");
    ls(src, false);
}



void Directory::ls(std::vector<FolderObj>::iterator foldIter, bool flag) {
    string str  = (*foldIter).getPath(); // the path that is the "father" of the folders and files
    cout << str << " : \n";

    while( ++foldIter != FolderVector.end()) { // folder vector is already sorted
        if(isContainedFolder(str, (*foldIter).getPath())) // exactly is a subDirectory of the Directory
            cout << "\e[1m" << printNameDir((*foldIter).getPath()) << "\e[0m" << "\t\t"; //printing bold letters on directory
    }
    cout << '\n';
    std::vector<FileObj>::iterator begin = FileVector.begin();
    std::vector<FileObj>::iterator end = FileVector.end();

    while(begin != end) {
        if (isContainedFile(str,(*begin).getPath())) { // the file is in the path of the directory
            if(flag)
                cout << printNameFile((*begin).getPath()) << '\t' << " RC : " << (*begin).getValue()->refCount << '\n';
            else
                cout << printNameFile((*begin).getPath()) << '\t';
        }
        begin++;
    }
    cout << '\n';

}

void Directory::LProot() {

    sortFileVectors();
    sortFolderVectors();
    std::vector<FolderObj>::iterator begin = FolderVector.begin();
    std::vector<FolderObj>::iterator end = FolderVector.end();

    while(begin != end){
        ls(begin++,true);
    }
}



/**                       HELP METHODS                          **/




/** searches for a speicific file in the vector of files **/
vector<FileObj>::iterator Directory::findFile(string path) {// gets string path and returns the FileObj
    vector<FileObj>::iterator begin = FileVector.begin();
    vector<FileObj>::iterator end = FileVector.end();

    while(begin != end && (*begin).getPath() != path) {
        begin++;
    }
    return begin;
}
/** searches for a specific folder in the vector of folders **/
vector<FolderObj>::iterator Directory::findFolder(string path) { // gets string path and returns the FileObj
    vector<FolderObj>::iterator begin = FolderVector.begin();
    vector<FolderObj>::iterator end = FolderVector.end();

    while(begin != end && (*begin).getPath() != path )
        begin++;
    return begin;
}


/** data member name is exactly the path without '/' for uniqueness
 *  so this function deletes all the '/' and returns the path without '/'
 * **/
string Directory::DeCompose(string path) {
    string str;
    for (unsigned int i = 0; i < path.size(); ++i) {
        if(path[i] == '/')
            continue;
        else
            str += path[i];
    }
    return str;
}

void Directory::sortFileVectors() {
    sort(FileVector.begin(), FileVector.end(), [](FileObj a, FileObj b)->bool {
        return a.getName() < b.getName();
    });
}

void Directory::sortFolderVectors() {
    sort(FolderVector.begin(),FolderVector.end(),[](FolderObj a, FolderObj b) ->bool {
       return a.getName() < b.getName();
    });
}

bool Directory::isContainedFolder(const string dir, const string subDir) const {
    unsigned int i,cnt = 0;
    for (i = 0; i < dir.size(); ++i)
        if(dir[i] != subDir[i])
            return false;
    for (unsigned int j = i; j < subDir.size() ; ++j)
        if(subDir[j] == '/') { // if the subDir's position is exactly at the dir's directory
            cnt++;
    }
    return cnt <= 1 ? true : false;
}

bool Directory::isContainedFile(const string dir, const string subDir) const {
    unsigned int i = 0;
    for (i = 0; i < dir.size(); ++i)
        if(dir[i] != subDir[i])
            return false;
    for (unsigned int j = i; j < subDir.size() ; ++j) {
        if(subDir[j] == '/') //the file is inside a subDirectory of the directory
            return false;
    }
    return true;
}


void Directory::deleteSubDirectories(string papa) {

    vector<FolderObj>::iterator begin = FolderVector.begin();
    vector<FolderObj>::iterator end = FolderVector.end();
    while( begin != end ) {
        if (isContainedFolder(papa, (*begin).getPath())) {
            begin = FolderVector.erase(begin);
        }
        begin++;
    }
}

void Directory::deleteSubFiles(string papa) {

    vector<FileObj>::iterator begin = FileVector.begin();
    vector<FileObj>::iterator end = FileVector.end();

    while( begin != end ) {
        if (isContainedFile(papa, (*begin).getPath())) {
            removeFile((*begin).getName());
        }
        begin++;
    }
}


string Directory::printNameFile(const string str) const {
    unsigned int pos;
    string res;

    for (unsigned int i = 0; i < str.size(); ++i){
        if(str[i] == '/' && (i != str.size() - 1))
            pos = i;
    }
    res = str.substr(pos+1);
    return res;
}

string Directory::printNameDir(const string str) const {
    unsigned int pos;
    string res;

    for (unsigned int i = 0; i < str.size(); ++i) {
        if (str[i] == '/' && (i != str.size() - 1))
            pos = i;
    }

    res = str.substr(pos + 1);
    res.pop_back();
    return res;
}

const string &Directory::getPwd() const {
    return pwd;
}

void Directory::setPwd(const string &pwd) {
    Directory::pwd = pwd;
}

void Directory::clearVectors() {
    FileVector.clear();
    FolderVector.clear();
}

bool Directory::goToFather() {
    string str{pwd};
    if (str == "V/")
        return false;
    unsigned int pos1,pos2;

    for (unsigned int i = 0; i <str.size(); ++i){
        if(str[i] == '/' && (i != str.size() - 1 )){
            pos1 = i;
            pos2 = pos1;
        }
    }
    pwd = str.substr(0,pos2+1);
    return true;
}

 void Directory::isValidFolder(string folder){
 	unsigned int pos = 0, i = 0;
 	string papa;

 	if(folder.substr(0,2) != "V/")
 		throw invalid_argument("V/ is the home directory\n");
 	for(i = 0 ; i < folder.size() ; ++i){
 		if(folder[i] == '/' && i != folder.size()-1){
 			pos = i;
 		}
 	}
 	papa = folder.substr(0,++pos);
 	vector<FolderObj>::iterator it = findFolder(papa);
 	if(it == FolderVector.end())
 		throw invalid_argument("the file is contained in a directory that doesn't exist\n");
 }


