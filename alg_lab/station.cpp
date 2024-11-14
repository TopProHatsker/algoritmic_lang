#include "station.h"
#include "func.h"


uint Station::ST_MaxID = 1;


istream&  operator >> (istream& in, Station& station) {
    cout << "Name: ";
    getline(cin, station.name);
    //cin >> station.name;

    cout << "Total workshops num: ";
    station.workshops_num = check_input(0, 999);

    cout << "Worked num: ";
    station.workshops_work = check_input(0, (int)station.workshops_num);

    cout << "Efficiency: ";
    station.eff = check_input(0., 99.9);

    //in.ignore();
    return in;
}


// ostream&  operator << (ostream& out, Station& station) {
//     out << station.ID << '\t';
//     out << station.name << '\t';
//     out << station.workshops_num << '\t';
//     out << station.workshops_work << '\t';
//     out << station.eff << '\t';

//     return out;
// }

ostream&  operator << (ostream& out, Station& station) {
    printf("%3.d| %20s| %5.d| %5d| %8.f",
           station.ID,
           //station.src_ID,
           //station.dest_ID,
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
    //ofs << station.src_ID         << '\n';
    //ofs << station.dest_ID        << '\n';

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
    //ifs >> station.src_ID;
    //ifs >> station.dest_ID;

    return ifs;
}
