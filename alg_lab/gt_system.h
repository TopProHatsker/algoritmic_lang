#ifndef GT_SYSTEM_H
#define GT_SYSTEM_H

#include "pipe.h"
#include "station.h"
#include <fstream>
#include <iostream>
#include <vector>


class System {

    string name;
    vector<Pipe> pipes;
    vector<Station> stations;

public:

    System(string name = "") {
        this->name = name;
    };

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
        pipes.push_back(p);
    }
    void add(Station s) {
        stations.push_back(s);
    }

    vector<Pipe>& getPipes() {
        return this->pipes;
    }

    vector<Station>* getStations() {
        return &this->stations;
    }

    void editPipe() {

    }

};

#endif // GT_SYSTEM_H
