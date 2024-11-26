#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <fstream>

using namespace std;


class Station {

    static uint ST_MaxID;

    uint ID = 0;
    string name = "";
    uint workshops_num = 0;
    uint workshops_work = 0;
    float eff = 0.0;

public:

    Station() {
        this->ID = ST_MaxID++;
    };

    Station(
        string name,
        uint workshops_num,
        uint workshops_work,
        double eff
    ) : Station() {

        this->name = name;
        this->workshops_num = workshops_num;
        this->workshops_work = workshops_work;
        this->eff = eff;
    }

    void print();

    uint getTotalWS();
    bool setWorkWS(uint num);
    void setEfficiency(float eff);

    friend istream&  operator >> (istream&   in, Station& station);
    friend ostream&  operator << (ostream&  out, Station& station);
    friend ofstream& operator << (ofstream& ofs, Station& station);
    friend ifstream& operator >> (ifstream& ifs, Station& station);

    uint getId() const ;
    string getName() const;
    float getUnUsagePerc() const;
};

#endif // STATION_H
