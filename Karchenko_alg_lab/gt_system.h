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

        // stations.push_back(Station("Test1", 10, 9, 3.14));
        // stations.push_back(Station("Test2", 10, 9, 3.14));
        // stations.push_back(Station("Test3", 11, 3, 13.14));
        // stations.push_back(Station("Test4", 20, 2, 23.14));
        // stations.push_back(Station("Test5", 33, 1, 33.14));
        // stations.push_back(Station("Test6", 1, 0, 34.14));

        // pipes.push_back(Pipe("Test1", 10, 1, 1));
        // pipes.push_back(Pipe("Test2", 222, 2, 0));
    };

    void print(ostream& out);
    int saveToFile(ofstream& ofs);
    int importFromFile(ifstream& ifs);

    void add(Pipe p) {
        pipes.push_back(p);
    }
    void add(Station s) {
        stations.push_back(s);
    }

};

#endif // GT_SYSTEM_H
