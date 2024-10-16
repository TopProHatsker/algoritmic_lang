#include "station.h"

istream&  operator >> (istream& in, Station& station) {}
ostream&  operator << (ostream& out, Station& station) {
    out << station.name << '\t';
    out << station.workshops_num << '\t';
    out << station.workshops_work << '\t';
    out << station.eff << '\t';

    return out;
}


ofstream& operator << (ofstream& ofs, Station& station) {
    ofs << station.name << '\n';
    ofs << station.workshops_num << '\n';
    ofs << station.workshops_work << '\n';
    ofs << station.eff << '\n';

    return ofs;
}


ifstream& operator >> (ifstream& ifs, Station& station) {
    ifs >> station.name;
    ifs >> station.workshops_num;
    ifs >> station.workshops_work;
    ifs >> station.eff;

    return ifs;
}
