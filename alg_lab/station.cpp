#include "station.h"
#include "func.h"


uint Station::ST_MaxID = 0;


istream&  operator >> (istream& in, Station& station) {
    cout << "Name: ";
    cin >> station.name;

    cout << "Total workshops num: ";
    station.workshops_num = check_input(0, 999);

    cout << "Worked num: ";
    station.workshops_work = check_input(0, (int)station.workshops_num);

    cout << "Efficiency: ";
    station.eff = check_input(0., 999.9);

    return in;
}


ostream&  operator << (ostream& out, Station& station) {
    out << station.ID << '\t';
    out << station.name << '\t';
    out << station.workshops_num << '\t';
    out << station.workshops_work << '\t';
    out << station.eff << '\t';

    return out;
}


ofstream& operator << (ofstream& ofs, Station& station) {
    ofs << station.ID << '\n';
    ofs << station.name << '\n';
    ofs << station.workshops_num << '\n';
    ofs << station.workshops_work << '\n';
    ofs << station.eff << '\n';

    return ofs;
}


ifstream& operator >> (ifstream& ifs, Station& station) {
    ifs >> station.ID;
    ifs >> station.name;
    ifs >> station.workshops_num;
    ifs >> station.workshops_work;
    ifs >> station.eff;

    return ifs;
}
