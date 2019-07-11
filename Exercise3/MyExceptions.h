//
// Created by Admin on 26/06/2018.
//

#ifndef EXERCISE3_MYEXCEPTIONS_H
#define EXERCISE3_MYEXCEPTIONS_H

#include <iostream>

using namespace std;

class MyExceptions {
public:

    class InvalidArgument{
    public:
        const std::string s;
        InvalidArgument(const string& str): s(str) {}
        void print() const { cout << s << endl;}
    };

    class InvalidInput{
    public:
        const std::string s;
        InvalidInput(const string& str) : s(str) { }
        void print() const {cout << s << endl;}
    };

    class ParsingError{
    public:
        const std::string s;
        ParsingError(const string& str) : s(str) { }
        void print() const {cout << s << endl;}
    };

    class ShipStatusException{
    public:
        const std::string s;
        ShipStatusException(const string& s) : s(s){}
        void print() const {cout << s << endl;}
    };

    class ShipRefuelException{
    public:
        const std::string s;
        ShipRefuelException(const string& s) : s(s){}
        void print() const {cout << s << endl;}
    };

    class OutOfRangeException{
    public:
        const std::string s;
        OutOfRangeException(const string& s) : s(s){}
        void print() const {cout << s << endl;}
    };

};


#endif //EXERCISE3_MYEXCEPTIONS_H
