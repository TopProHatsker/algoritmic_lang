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

    unordered_map<uint, Pipe> getPipes() {
        return this->pipes;
    }

    unordered_map<uint, Station> getStations() {
        return this->stations;
    }

    Pipe& getMPipe(const uint key) {
        return this->pipes.at(key);
    }

    Station& getMStation (const uint key) {
        return this->stations.at(key);
    }

    void editPipe(const uint ID);

};

#endif // GT_SYSTEM_H
