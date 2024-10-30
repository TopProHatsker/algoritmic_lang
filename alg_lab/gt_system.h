#ifndef GT_SYSTEM_H
#define GT_SYSTEM_H

#include "pipe.h"
#include "station.h"
#include <climits>
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

    void addPipe(istream& is) {
        Pipe p;
        is >> p;
        is.ignore();
        pipes.emplace(p.getId(), p);
    }
    void addStation(istream& is) {
        Station s;
        is >> s;
        is.ignore();
        stations.emplace(s.getId(), s);
    }

    unordered_map<uint, Pipe> getPipes() {
        return this->pipes;
    }

    unordered_map<uint, Station> getStations() {
        return this->stations;
    }

    // Pipe& getMPipe(const uint key) {
    //     return this->pipes.at(key);
    // }

    // Station& getMStation (const uint key) {
    //     return this->stations.at(key);
    // }

    void editPipe   (const uint id);
    void editStation(const uint id);

    template <typename T>
    void deleteObj(istream& is, ostream& os, unordered_map<uint, T>& arr) {
        os << "> Enter id: ";
        uint id;
        cin >> id;
        is.ignore();

        auto iter = arr.find(id);
        if (iter == arr.end()) {
            os << " Not found." << endl;
            return;
        } else {
            arr.erase(iter);
            os << " ok." << endl;
        }
    }

    void deleteStation(istream& is, ostream& os) {
        deleteObj(is, os, this->stations);
    }
    void deletePipe   (istream& is, ostream& os) {
        deleteObj(is, os, this->pipes);
    }

};

#endif // GT_SYSTEM_H
