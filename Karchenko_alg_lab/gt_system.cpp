#include "gt_system.h"

#include "func.h"


template <typename T>
void print_vector(ostream& out, vector<T> arr) {
    for (int i = 0; i < arr.size(); i++) {
        out << " " << i + 1 << ") " << arr[i] << '\n';
    }
    out << endl;
}



void System::print(ostream& out){

    out << "Stations:\n";
    if (stations.empty())
        out << " Empty" << endl;
    else {
        out << "    Name\tTotal\tWork WS\tEfficiency" << endl;
        print_vector(out, stations);
    }
    out << "\nPipes:\n";
    if (pipes.empty())
        out << " Empty" << endl;
    else {
        out << "    Name\tDiam\tLength\tOnRepair" << endl;
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
            //cerr << "ST" << endl;
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
            //cerr << "PP" << endl;
            pipes.push_back(t);
        } else {
            cerr << ">! Error reading pipes!" << endl;
            pipes.clear();
            return 2;
        }
    }

    return 0;
}
