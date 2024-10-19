#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <fstream>

using namespace std;

class Pipe {

    string name = "";
    double length = 0;
    double diameter = 0;
    bool on_repair = false;

public:

    Pipe() {};
    Pipe(string name, double length, double diameter, bool on_repair) {
        this->name = name;
        this->diameter = diameter;
        this->length = length;
        this->on_repair = on_repair;
    }

    bool isRepair() {
        return on_repair;
    }

    void setRepairStatus(bool on_repair) {
        this->on_repair = on_repair;
    }

    void print() {
        cout << " Name: " << name
             << "\tDiameter: " << diameter
             << "\tLength: " << length
             << "\tOn repair: " << on_repair << endl;
    }

    friend istream&  operator >> (istream&   in, Pipe& new_pipe);
    friend ostream&  operator << (ostream&  out, Pipe& new_pipe);
    friend ofstream& operator << (ofstream& ofs, Pipe& new_pipe);
    friend ifstream& operator >> (ifstream& ifs, Pipe& new_pipe);

};


#endif // PIPE_H
