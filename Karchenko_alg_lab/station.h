#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <fstream>

using namespace std;


class Station {

    string name = "";
    uint workshops_num = 0;
    uint workshops_work = 0;
    double eff = 0.0;

public:

    Station() {};
    Station(string name, uint workshops_num, uint workshops_work, double eff) {
        this->name = name;
        this->workshops_num = workshops_num;
        this->workshops_work = workshops_work;
        this->eff = eff;
    }

    friend istream&  operator >> (istream&   in, Station& station);
    friend ostream&  operator << (ostream&  out, Station& station);
    friend ofstream& operator << (ofstream& ofs, Station& station);
    friend ifstream& operator >> (ifstream& ifs, Station& station);

};

#endif // STATION_H