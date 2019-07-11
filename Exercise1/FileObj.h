//
// Created by raviv on 25/03/18.
//

#include <iostream>
#include <fstream>
#include <cstring>

#ifndef TERMINAL_FILEOBJ_H
#define TERMINAL_FILEOBJ_H

using namespace std;
using namespace std::__exception_ptr;

class FileObj {


public:


    class CharProxy {
    public:
        CharProxy(fstream &file, fstream::pos_type pos) : file_(file), pos_(pos) {}
        CharProxy& operator=(char c) {
            file_.seekp(pos_);
            file_.put(c);
            return *this;
        }
        operator char() {
            file_.seekg(pos_);
            return char(file_.get());
        }
    private:
        fstream& file_;
        fstream::pos_type pos_;
    };


    explicit  FileObj(string name,string path); // C'tor

    FileObj(){}

    FileObj(const FileObj& rhs); // copy ctor

    ~FileObj(); // dtor

    FileObj& operator=(const FileObj& rhs); // operator = (The big three)

    const char operator[](fstream::pos_type i) const;

    CharProxy operator[](fstream::pos_type i);

    void touch() const;

    void cat() const;

    void wc() const;

    void copy(FileObj& trg) const;

    void ln(FileObj& trg) const;

    const string &getName() const;

    const string &getPath() const;

    string printName(string) const;



private :
    struct myFile{

        int refCount;

        string linkedFileName;



        fstream* file;

        myFile(string);

    public:
        myFile(string linkedName,fstream* file);

        bool IsHardLinked = false;

        ~myFile();


    };


    /** Data Members Of FileObj  **/

    myFile* value;

    string name,path;

public:
    void setValue(myFile *value);

    myFile *getValue() const;


};






#endif //TERMINAL_FILEOBJ_H
