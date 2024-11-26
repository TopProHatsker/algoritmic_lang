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

    void print() const;

    bool isRepair() const;
    void setRepairStatus(bool on_repair);

    friend istream&  operator >> (istream&   in, Pipe& new_pipe);
    friend ostream&  operator << (ostream&  out, Pipe& new_pipe);
    friend ofstream& operator << (ofstream& ofs, Pipe& new_pipe);
    friend ifstream& operator >> (ifstream& ifs, Pipe& new_pipe);

    uint getId() const;
    string getName() const;
    uint getDiam() const;
    uint getLength() const;

    bool isConnected() const;
    void connect(uint src_id, uint dest_id);
    void disconnect();
    pair<uint, uint> getSTid() const;

};


#endif // PIPE_H
