#include "gt_system.h"
#include "func.h"


void GTSystem::print(ostream& out){
    this->printStations(out);
    this->printPipes(out);
}


void GTSystem::printStations(ostream& out){

    out << "Stations:\n";
    if (stations.empty())
        out << " Empty" << endl;
    else {
        ST_HEADER
            print_arr(out, stations);
    }

}

void GTSystem::printPipes(ostream& out){

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


uint getSTidDialog(istream& is, ostream& os, const GTSystem& gt_sys) {
    uint id = check_input(1, INT_MAX);
    os << "> Station: ";
    if (gt_sys.isStation(id)) {
        os << gt_sys.getStation(id).getName() << endl;
        return id;
    } else {
        //os << "!> Not found" << endl;
        return 0;
    }
}

uint getPPidDialog(istream& is, ostream& os, const GTSystem& gt_sys) {
    uint id = check_input(1, INT_MAX);
    os << "> Pipe: ";
    if (gt_sys.isPipe(id)) {
        os << gt_sys.getPipe(id).getName() << endl;
        return id;
    } else {
        //os << "!> Not found" << endl;
        return 0;
    }
}


vector<uint> GTSystem::getPipes(bool (*filter) (const Pipe& p, const void * diam), void * param) {
    vector<uint> arr;
    for(auto& t: this->pipes) {
        if (filter(t.second, param)) {
            arr.push_back(t.second.getId());
        }
    }
    return arr;
}


void GTSystem::connectPipe(istream& is, ostream& os) {
    this->printStations(os);

    if (getStationsNum() == 0)
        return;

    os << "\n> Enter stations IDs:\n";

    os << " Source ID: ";
    uint src_id = getSTidDialog(is, os, *this);
    os << " Destination ID: ";
    uint dest_id = getSTidDialog(is, os, *this);
    os << endl;

    if (!(src_id * dest_id)) {
        os << "!> Error (ID not found)" << endl;
        is.ignore();
        return;
    }

    if (src_id == dest_id) {
        os << "!> Error (Source id equals Destination)" << endl;
        is.ignore();
        return;
    }

    os << "> Enter pipe diameter (500, 700, 1000, 1400): ";
    uint diam = check_input(500, 1400);

    os << "\nPipes:";
    vector<uint> pipes_arr = getPipes(CheckPPDiamAndFree, &diam);

    os << endl;
    PP_HEADER
    for (auto& t: pipes_arr) {
        cout << ' ' << this->pipes[t] << endl;
    }
    os << endl;

    is.ignore();
    bool need_redraw = false;
    if (pipes_arr.empty()) {
        os << "Add:\n";
        this->addPipe(is);
        need_redraw = true;
    } else {
        os << "> Want add new pipe? [N/y]: ";
        string res;
        getline(is, res);
        if (res[0] == 'y') {
            os << "Add:\n";
            this->addPipe(is);
            need_redraw = true;
        }
    }

    if (need_redraw) {
        pipes_arr = getPipes(CheckPPDiamAndFree, &diam);

        os << "\nPipes:\n";
        PP_HEADER
        for (auto& t: pipes_arr) {
            cout << ' ' << this->pipes[t] << endl;
        }
    }

    os << "\n> Enter pipe ID: ";
    uint pipe_id = getPPidDialog(is, os, *this);

    bool founded = false;
    for (auto t: pipes_arr) {
        if (pipe_id == t) {
            founded = true;
            break;
        }
    }

    if (!founded) {
        os << "!> Error" << endl;
        is.ignore();
        return;
    }

    this->pipes[pipe_id].connect(src_id, dest_id);

    is.ignore();
}


void GTSystem::disconnectPipe(istream& is, ostream& os) {

    os << "Connected pipes:\n";
    bool status = true;
    vector<uint> pipes_arr = getPipes(CheckPPConnected, &status);

    if (pipes_arr.empty()) {
        os << "> Empty" << endl;
        return;
    }

    PP_HEADER
    for (auto& t: pipes_arr) {
        cout << ' ' << this->pipes[t] << '\n';
    }
    os << endl;

    os << "\n> Enter pipe ID: ";
    uint pipe_id = getPPidDialog(is, os, *this);

    bool founded = false;
    for (const auto &t: pipes_arr) {
        if (pipe_id == t) {
            founded = true;
            break;
        }
    }

    if (!founded) {
        os << "!> Error (Not in list)" << endl;
        is.ignore();
        return;
    }

    // os << "\nFounded:\n";
    // PP_HEADER
    // os << ' ' << this->pipes[pipe_id] << endl;

    this->pipes[pipe_id].disconnect();


    is.ignore();
}
