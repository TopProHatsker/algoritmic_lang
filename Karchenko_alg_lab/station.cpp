#include "station.h"


template <typename T>
T check_input(T min, T max)
{
    T x;
    while ((cin >> x).fail() || (cin).peek() != '\n' || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n!> Enter the correct data (" << min << " - " << max << ") ";
    }
    return x;
}



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
