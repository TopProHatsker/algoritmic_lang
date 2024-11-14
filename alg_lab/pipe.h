#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <fstream>

using namespace std;

class Pipe {

    static uint PP_MaxID;

    uint ID = 0;
    uint src_ID = 0;
    uint dest_ID = 0;

    string name = "";
    double length = 0;
    uint diameter = 0;
    bool on_repair = false;

public:

    Pipe() {
        this->ID = PP_MaxID++;
    };

    Pipe(
        string name,
        double length,
        double diameter,
        bool on_repair
    ) : Pipe() {

        this->name = name;
        this->diameter = diameter;
        this->length = length;
        this->on_repair = on_repair;
    }

    bool isRepair() const {
        return on_repair;
    }

    void setRepairStatus(bool on_repair) {
        this->on_repair = on_repair;
    }

    void print() const {
        cout << "ID: " << ID
             << "\tName: " << name
             << "\tDiameter: " << diameter
             << "\tLength: " << length
             << "\tOn repair: " << on_repair << endl;
    }

    friend istream&  operator >> (istream&   in, Pipe& new_pipe);
    friend ostream&  operator << (ostream&  out, Pipe& new_pipe);
    friend ofstream& operator << (ofstream& ofs, Pipe& new_pipe);
    friend ifstream& operator >> (ifstream& ifs, Pipe& new_pipe);

    uint getId() const {
        return this->ID;
    }

    string getName() const {
        return this->name;
    }

    uint getDiam() const {
        return this->diameter;
    }

    uint getLength() const {
        return this->length;
    }

    bool isConnected() const {
        return (bool)this->src_ID + (bool)this->dest_ID;
    }

    void connect(uint src_id, uint dest_id) {
        this->src_ID = src_id;
        this->dest_ID = dest_id;
    }

    void disconnect() {
        this->src_ID = 0;
        this->dest_ID = 0;
    }

    pair<uint, uint> getSTid() const {
        return {this->src_ID, this->dest_ID};
    }

};


#endif // PIPE_H
