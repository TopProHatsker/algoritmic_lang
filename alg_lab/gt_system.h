#ifndef GT_SYSTEM_H
#define GT_SYSTEM_H

#include "pipe.h"
#include "station.h"
#include <fstream>
#include <iostream>
#include <unordered_map>


class GTSystem {

    string name;
    unordered_map<uint, Pipe> pipes;
    unordered_map<uint, Station> stations;

public:

    GTSystem(string name = "") {
        this->name = name;
    };

    void clear() {
        this->stations.clear();
        this->pipes.clear();
    }

    void print(ostream& out);
    int saveToFile(ofstream& ofs);
    int importFromFile(ifstream& ifs);

    uint getPipesNum() {
        return this->pipes.size();
    }

    uint getStationsNum() {
        return this->stations.size();
    }

    void add(Pipe p) {
        pipes.insert({p.getId(), p});
    }
    void add(Station s) {
        stations.insert({s.getId(), s});
    }

    // vector<Pipe>& getPipes() {
    //     return this->pipes;
    // }

    // vector<Station>* getStations() {
    //     return &this->stations;
    // }

    void editPipe() {

    }

};

#endif // GT_SYSTEM_H
