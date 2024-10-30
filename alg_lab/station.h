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

    uint getTotalWS() {
        return this->workshops_num;
    }

    bool setWorkWS(uint num) {
        if (num > this->workshops_num)
            return 1;

        this->workshops_work = num;
        return 0;
    }

    void print() {
        cout << "UID: " << ID
             << "\tName: " << name
             << "\tTotal WS num: " << workshops_num
             << "\tWork WS num: " << workshops_work
             << "\tEfficiency: " << eff << endl;
    }

    friend istream&  operator >> (istream&   in, Station& station);
    friend ostream&  operator << (ostream&  out, Station& station);
    friend ofstream& operator << (ofstream& ofs, Station& station);
    friend ifstream& operator >> (ifstream& ifs, Station& station);


    uint getId() {
        return this->ID;
    }

    string getName() const {
        return this->name;
    }

    float getUnUsagePerc() const {
        return (float)this->workshops_work / (float)this->workshops_num;
    }

};

#endif // STATION_H
