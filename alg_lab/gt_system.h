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

    void clear() {
        this->stations.clear();
        this->pipes.clear();
    }

    void print(ostream& out);
    void printStations(ostream& out);
    void printPipes(ostream& out);

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

    Pipe getPipe(const uint key) const {
        return this->pipes.find(key)->second;
    }

    const Station& getStation (const uint key) const {
        // auto t = this->stations.find(key);
        // if (t != this->stations.end())
        //     return t->second;
        return this->stations.find(key)->second;
        //return this->stations[key];
    }

    void editPipe   (const uint id);
    int editPipeStatus (const uint id, const uint status) {
        auto t = this->pipes.find(id);
        if (t != this->pipes.end()) {
            t->second.setRepairStatus(status);
            return 0;
        }
        return 1;
    }
    void editStation(const uint id);
    int editStationEff(const uint id, const float eff) {
        auto t = this->stations.find(id);
        if (t != this->stations.end()) {
            t->second.setEfficiency(eff);
            return 0;
        }
        return 1;
    }

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

    void deleteStation(istream& is, ostream& os) {
        os << "> Enter id: ";
        uint station_id;
        cin >> station_id;
        is.ignore();

        auto iter = this->stations.find(station_id);
        if (iter == this->stations.end()) {
            os << " Not found." << endl;
            return;
        } else {
            os << "> Founded" << endl;
        }

        os << "> Station status: ";
        vector<uint> pipe_id;
        for (const auto& t: this->pipes)
            if (
                t.second.getSTid().first  == station_id ||
                t.second.getSTid().second == station_id
            ) pipe_id.push_back(t.first);

        if (pipe_id.empty()) {
            os << "Not connected" << endl;
        } else {
            os << "connected to (";
            for (auto t: pipe_id) {
                os << " " << this->pipes[t].getName() << ";";
            }
            os << ")" << endl;

            os << "> Want to delete station anyway [N/y]: ";
            string res;
            getline(is, res);
            if (res[0] == 'y') {

            } else {
                return;
            }
        }

        for (auto id: pipe_id)
            this->pipes[id].disconnect();

        this->stations.erase(iter);
        os << "> Deleted" << endl;
    }


    void deletePipe   (istream& is, ostream& os) {
        os << "> Enter id: ";
        uint id;
        cin >> id;
        is.ignore();

        auto iter = pipes.find(id);
        if (iter == this->pipes.end()) {
            os << " Not found." << endl;
            return;
        } else {
            os << "> Founded" << endl;
        }

        os << "> Pipe status: ";
        if (iter->second.isConnected()) {
            os << "Connected" << endl;

            os << "> Want to delete pipe anyway [N/y]: ";
            string res;
            getline(is, res);
            if (res[0] == 'y') {
                // this->pipes.erase(iter);
                // os << "> Deleted" << endl;
            } else {
                return;
            }

        } else {
            os << "Not Connected" << endl;
        }

        this->pipes.erase(iter);
        os << "> Deleted" << endl;

    }


    bool isStation(uint key) const {
        return this->stations.find(key) != this->stations.end();
    }
    bool isPipe(uint key) const {
        return this->pipes.find(key) != this->pipes.end();
    }

    void connectPipe(istream& is, ostream& os);
    void disconnectPipe(istream& is, ostream& os);

    vector<uint> getPipes(bool (*filter) (const Pipe& p, const void * diam), void * size);

    vector<vector<uint>> getMaxtrix() {
        vector<uint> row = {0};
        row.resize(this->getStationsNum());
        vector<vector<uint>> mtr;
        for (uint i = 0; i < this->getStationsNum(); i++)
            mtr.push_back(row);

        for (auto& t: this->pipes) {
            pair<uint, uint> ids = t.second.getSTid();
            if (ids.first > 0 && ids.second > 0) {
                mtr[ids.first - 1][ids.second - 1] = t.second.getLength();
                //mtr[ids.second][ids.first] = t.second.getLength(); // TODO:
            }
        }

        return mtr;
    }

};

#endif // GT_SYSTEM_H
