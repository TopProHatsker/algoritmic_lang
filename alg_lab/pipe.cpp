#include "pipe.h"
#include "func.h"

uint Pipe::PP_MaxID = 0;

istream&  operator >> (istream& in, Pipe& pipe) {
    cout << "Name: ";
    getline(in, pipe.name);
    //cin >> pipe.name;

    cout << "Length: ";
    pipe.length = check_input(1, 99999);

    cout << "Diameter: ";
    pipe.diameter = check_input(400, 1500);

    cout << "On repair? (1 - yes, 0 - no): ";
    pipe.on_repair = check_input(0, 1);

    return in;
}


ostream&  operator << (ostream& out, Pipe& pipe) {

    // std::locale::global(std::locale("ru_RU.UTF-8"));
    // std::wcout.imbue(std::locale(""));

    out.fill(' ');
    out.width(3);
    out << pipe.ID << "| ";

    out.width(20);
    out << pipe.name << "| ";

    out.width(5);
    out << pipe.diameter << "| ";

    out.width(5);
    out << pipe.length << "| ";

    out.width(7);
    out << pipe.on_repair;

    return out;
}

// ostream&  operator << (ostream& out, Pipe& pipe) {
//     //wchar_t* t = pipe.name;
//     printf("%3d| %20s| %5.lf| %5.lf| %7.d",
//            pipe.ID,
//            pipe.name.c_str(),
//            pipe.diameter,
//            pipe.length,
//            pipe.on_repair
//     );

//     return out;
// }


ofstream& operator << (ofstream& ofs, Pipe& pipe) {
    //ofs << pipe.ID      << '\n';
    ofs << pipe.name      << '\n';
    ofs << pipe.diameter  << '\n';
    ofs << pipe.length    << '\n';
    ofs << pipe.on_repair << '\n';

    return ofs;
}


ifstream& operator >> (ifstream& ifs, Pipe& pipe) {
    //ifs >> pipe.ID;
    ifs.ignore();   // Ignore '\n' after numbers row
    getline(ifs, pipe.name);
    //ifs >> pipe.name;
    ifs >> pipe.diameter;
    ifs >> pipe.length;
    ifs >> pipe.on_repair;

    return ifs;
}
