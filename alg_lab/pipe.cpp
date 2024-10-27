#include "pipe.h"
#include "func.h"

uint Pipe::PP_MaxID = 0;

istream&  operator >> (istream& in, Pipe& pipe) {
    cout << "Name: ";
    cin >> pipe.name;

    cout << "Length: ";
    pipe.length = check_input(0, 999);

    cout << "Diameter: ";
    pipe.diameter = check_input(0, 999);

    cout << "On repair? (1 - yes, 0 - no): ";
    pipe.on_repair = check_input(0, 1);

    return in;
}


ostream&  operator << (ostream& out, Pipe& pipe) {
    out << pipe.ID      << '\t';
    out << pipe.name      << '\t';
    out << pipe.diameter  << '\t';
    out << pipe.length    << '\t';
    out << pipe.on_repair << '\t';

    return out;
}


ofstream& operator << (ofstream& ofs, Pipe& pipe) {
    ofs << pipe.ID      << '\n';
    ofs << pipe.name      << '\n';
    ofs << pipe.diameter  << '\n';
    ofs << pipe.length    << '\n';
    ofs << pipe.on_repair << '\n';

    return ofs;
}


ifstream& operator >> (ifstream& ifs, Pipe& pipe) {
    ifs >> pipe.ID;
    ifs >> pipe.name;
    ifs >> pipe.diameter;
    ifs >> pipe.length;
    ifs >> pipe.on_repair;

    return ifs;
}
