#include "gt_system.h"

#include "func.h"



void GTSystem::print(ostream& out){

    out << "Stations:\n";
    if (stations.empty())
        out << " Empty" << endl;
    else {
        //out << " ID\t"; out << "Name "; out << "Total\tWork WS\tEfficiency" << endl;
        printf("  ID|          Name| Total|  Work|Efficiency\n");
        printf("----+--------------+------+------+----------\n");
        print_arr(out, stations);
    }
    out << "\nPipes:\n";
    if (pipes.empty())
        out << " Empty" << endl;
    else {
        //out << " ID\t"; out << "Name "; out << "Diam\tLength\tOnRepair" << endl;
        printf("  ID|          Name|  Diam|Length|OnRepair\n");
        printf("----+--------------+------+------+---------\n");
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
