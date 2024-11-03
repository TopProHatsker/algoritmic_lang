#include "gt_system.h"

#include "func.h"




void GTSystem::print(ostream& out){

    out << "Stations:\n";
    if (stations.empty())
        out << " Empty" << endl;
    else {
        ST_HEADER
        print_arr(out, stations);
    }

    out << "\nPipes:\n";
    if (pipes.empty())
        out << " Empty" << endl;
    else {
        PP_HEADER
        print_arr(out, pipes);
    }

}


int GTSystem::saveToFile(ofstream& ofs) {
    if (!ofs.is_open())
        return 1;

    ofs << this->stations.size()
        << ' '
        << this->pipes.size()
        << '\n';

    for (auto& t: this->stations)
        ofs << t.second;

    for (auto& t: this->pipes)
        ofs << t.second;

    return 0;
}


int GTSystem::importFromFile(ifstream& ifs) {
    if (!ifs.is_open())
        return 1;

    this->clear();

    size_t st_num, pp_num;
    ifs >> st_num >> pp_num;

    for (size_t i = 0; i < st_num; i++) {
        Station t;
        if (ifs >> t) {
            stations.insert({t.getId(), t});
        } else {
            cerr << "!> Error reading stations!" << endl;
            stations.clear();
            return 1;
        }
    }

    for (size_t i = 0; i < pp_num; i++) {
        Pipe t;
        if (ifs >> t) {
            pipes.insert({t.getId(), t});
        } else {
            cerr << "!> Error reading pipes!" << endl;
            pipes.clear();
            return 2;
        }
    }

    return 0;
}


void GTSystem::editPipe(const uint id) {
    Pipe& p = this->pipes.at(id);

    p.print();

    cout << "> Enter new repair status (1 - on repair | 0 - not): ";
    bool new_repair_st = check_input(0, 1);
    p.setRepairStatus(new_repair_st);

    cout << "New pipe: " << endl;
    p.print();

}


void GTSystem::editStation(const uint id) {
    Station& s = this->stations.at(id);

    s.print();

    cout << "> Enter new working WS number: ";
    uint wwsn = check_input((uint)0, s.getTotalWS());
    s.setWorkWS(wwsn);

    cout << "New station: " << endl;
    s.print();

}
