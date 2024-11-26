#ifndef GT_SYSTEM_H
#define GT_SYSTEM_H

#include "pipe.h"
#include "station.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>



class GTSystem {

    string name;
    unordered_map<uint, Pipe> pipes;
    unordered_map<uint, Station> stations;

public:

    GTSystem(string name = "") {
        this->name = name;
    };

    void clear();

    void print(ostream& out);
    void printStations(ostream& out);
    void printPipes(ostream& out);

    int saveToFile(ofstream& ofs);
    int importFromFile(ifstream& ifs);

    uint getPipesNum() const;
    uint getStationsNum() const;

    void addPipe(istream &is);
    void addStation(istream &is);

    unordered_map<uint, Pipe> getPipes();
    unordered_map<uint, Station> getStations();

    Pipe getPipe(const uint key) const;

    const Station &getStation(const uint key) const;

    void editPipe   (const uint id);
    int editPipeStatus(const uint id, const uint status);

    void editStation(const uint id);
    int editStationEff(const uint id, const float eff);

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

    template <typename T>
    int deleteObj(uint id, unordered_map<uint, T>& arr) {
        auto iter = arr.find(id);
        if (iter == arr.end()) {
            return 1;
        } else {
            arr.erase(iter);
            return 0;
        }
    }

    void deleteStation(istream &is, ostream &os);
    void deletePipe(istream &is, ostream &os);

    bool isStation(uint key) const;
    bool isPipe(uint key) const;

    void connectPipe(istream& is, ostream& os);
    void disconnectPipe(istream& is, ostream& os);

    vector<uint> getPipes(bool (*filter) (const Pipe& p, const void * diam), void * size);

    vector<vector<uint>> getMaxtrix();
    vector<vector<float>> getEffMaxtrix();
};

#endif // GT_SYSTEM_H
