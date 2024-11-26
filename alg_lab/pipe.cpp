#include "pipe.h"
#include "func.h"

uint Pipe::PP_MaxID = 1;

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

    pipe.src_ID = 0;
    pipe.dest_ID = 0;

    return in;
}


ostream&  operator << (ostream& out, Pipe& pipe) {
    printf("%3.d| %3.d| %3.d| %20s| %5.d| %5.lf| %7.d",
           pipe.ID,
           pipe.src_ID,
           pipe.dest_ID,
           pipe.name.c_str(),
           pipe.diameter,
           pipe.length,
           pipe.on_repair
    );

    return out;
}


ofstream& operator << (ofstream& ofs, Pipe& pipe) {
    ofs << pipe.name      << '\n';
    ofs << pipe.diameter  << '\n';
    ofs << pipe.length    << '\n';
    ofs << pipe.on_repair << '\n';

    ofs << pipe.ID        << '\n';
    ofs << pipe.src_ID    << '\n';
    ofs << pipe.dest_ID   << '\n';

    return ofs;
}


ifstream& operator >> (ifstream& ifs, Pipe& pipe) {
    ifs.ignore();   // Ignore '\n' after numbers row
    getline(ifs, pipe.name);
    //ifs >> pipe.name;
    ifs >> pipe.diameter;
    ifs >> pipe.length;
    ifs >> pipe.on_repair;

    ifs >> pipe.ID;
    ifs >> pipe.src_ID;
    ifs >> pipe.dest_ID;

    return ifs;
}


void Pipe::connect(uint src_id, uint dest_id) {
    this->src_ID = src_id;
    this->dest_ID = dest_id;
}

void Pipe::disconnect() {
    this->src_ID = 0;
    this->dest_ID = 0;
}

std::pair<uint, uint> Pipe::getSTid() const {
    return {this->src_ID, this->dest_ID};
}

bool Pipe::isConnected() const {
    return (bool)this->src_ID + (bool)this->dest_ID;
}

uint Pipe::getLength() const { return this->length; }

uint Pipe::getDiam() const { return this->diameter; }

std::string Pipe::getName() const { return this->name; }

uint Pipe::getId() const { return this->ID; }

void Pipe::print() const {
    cout
        << "ID: " << ID
        << "\tName: " << name
        << "\tDiameter: " << diameter
        << "\tLength: " << length
        << "\tOn repair: " << on_repair
        << endl;
}

void Pipe::setRepairStatus(bool on_repair) { this->on_repair = on_repair; }
bool Pipe::isRepair() const { return on_repair; }
