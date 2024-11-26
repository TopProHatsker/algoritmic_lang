#include "station.h"
#include "func.h"


uint Station::ST_MaxID = 1;


istream&  operator >> (istream& in, Station& station) {
    cout << "Name: ";
    getline(cin, station.name);

    cout << "Total workshops num: ";
    station.workshops_num = check_input(0, 999);

    cout << "Worked num: ";
    station.workshops_work = check_input(0, (int)station.workshops_num);

    cout << "Efficiency: ";
    station.eff = check_input(0., 99.9);

    //in.ignore();
    return in;
}


ostream&  operator << (ostream& out, Station& station) {
    printf("%3.d| %20s| %5.d| %5d| %8.f",
           station.ID,
           station.name.c_str(),
           station.workshops_num,
           station.workshops_work,
           station.eff
    );
    return out;
}


ofstream& operator << (ofstream& ofs, Station& station) {
    ofs << station.name           << '\n';
    ofs << station.workshops_num  << '\n';
    ofs << station.workshops_work << '\n';
    ofs << station.eff            << '\n';

    ofs << station.ID             << '\n';

    return ofs;
}

ifstream& operator >> (ifstream& ifs, Station& station) {
    //ifs >> station.ID;
    ifs.ignore();   // Ignore '\n' after numbers row
    getline(ifs, station.name);
    //ifs >> station.name;
    ifs >> station.workshops_num;
    ifs >> station.workshops_work;
    ifs >> station.eff;

    ifs >> station.ID;

    return ifs;
}

uint Station::getTotalWS() { return this->workshops_num; }

bool Station::setWorkWS(uint num) {
    if (num > this->workshops_num)
        return 1;

    this->workshops_work = num;
    return 0;
}

void Station::setEfficiency(float eff) { this->eff = eff; }

void Station::print() {
    cout << "UID: " << ID << "\tName: " << name
         << "\tTotal WS num: " << workshops_num
         << "\tWork WS num: " << workshops_work << "\tEfficiency: " << eff
         << endl;
}

uint Station::getId() const { return this->ID; }

std::string Station::getName() const { return this->name; }

float Station::getUnUsagePerc() const {
    return (float)this->workshops_work / (float)this->workshops_num;
}

