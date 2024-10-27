#include "gt_system.h"

#include "func.h"



void System::print(ostream& out){

    out << "Stations:\n";
    if (stations.empty())
        out << " Empty" << endl;
    else {
        out << " ID\tName\tTotal\tWork WS\tEfficiency" << endl;
        print_vector(out, stations);
    }
    out << "\nPipes:\n";
    if (pipes.empty())
        out << " Empty" << endl;
    else {
        out << " ID\tName\tDiam\tLength\tOnRepair" << endl;
        print_vector(out, pipes);
    }

}


int System::saveToFile(ofstream& ofs) {
    if (!ofs.is_open())
        return 1;

    ofs << this->stations.size()
        << ' '
        << this->pipes.size()
        << '\n';

    for (auto& t: this->stations)
        ofs << t;

    for (auto& t: this->pipes)
        ofs << t;

    return 0;
}


int System::importFromFile(ifstream& ifs) {
    if (!ifs.is_open())
        return 1;

    this->stations.clear();
    this->pipes.clear();

    size_t st_num, pp_num;
    ifs >> st_num >> pp_num;

    for (size_t i = 0; i < st_num; i++) {
        Station t;
        if (ifs >> t) {
            stations.push_back(t);
        } else {
            cerr << ">! Error reading stations!" << endl;
            stations.clear();
            return 1;
        }
    }

    for (size_t i = 0; i < pp_num; i++) {
        Pipe t;
        if (ifs >> t) {
            pipes.push_back(t);
        } else {
            cerr << ">! Error reading pipes!" << endl;
            pipes.clear();
            return 2;
        }
    }

    return 0;
}
