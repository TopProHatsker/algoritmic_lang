#include "gt_system.h"
#include "func.h"
#include <cmath>


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

    this->pipes[pipe_id].disconnect();

    is.ignore();
}

void GTSystem::clear() {
    this->stations.clear();
    this->pipes.clear();
}

uint GTSystem::getPipesNum() const { return this->pipes.size(); }

uint GTSystem::getStationsNum() const { return this->stations.size(); }

void GTSystem::addPipe(istream &is) {
    Pipe p;
    is >> p;
    is.ignore();
    pipes.emplace(p.getId(), p);
}

void GTSystem::addStation(istream &is) {
    Station s;
    is >> s;
    is.ignore();
    stations.emplace(s.getId(), s);
}

unordered_map<uint, Pipe> GTSystem::getPipes() {
    return this->pipes;
}

unordered_map<uint, Station> GTSystem::getStations() {
    return this->stations;
}

Pipe GTSystem::getPipe(const uint key) const {
    return this->pipes.find(key)->second;
}

const Station &GTSystem::getStation(const uint key) const {
    return this->stations.find(key)->second;
}

int GTSystem::editPipeStatus(const uint id, const uint status) {
    auto t = this->pipes.find(id);
    if (t != this->pipes.end()) {
        t->second.setRepairStatus(status);
        return 0;
    }
    return 1;
}

int GTSystem::editStationEff(const uint id, const float eff) {
    auto t = this->stations.find(id);
    if (t != this->stations.end()) {
        t->second.setEfficiency(eff);
        return 0;
    }
    return 1;
}


void GTSystem::deleteStation(istream &is, ostream &os) {
    os << "> Enter id: ";
    uint station_id;
    cin >> station_id;
    is.ignore();

    auto iter = this->stations.find(station_id);
    if (iter == this->stations.end()) {
        os << " Not found." << endl;
        return;
    } else {
        os << "> Founded" << endl;
    }

    os << "> Station status: ";
    vector<uint> pipe_id;
    for (const auto &t : this->pipes)
        if (t.second.getSTid().first == station_id ||
            t.second.getSTid().second == station_id)
            pipe_id.push_back(t.first);

    if (pipe_id.empty()) {
        os << "Not connected" << endl;
    } else {
        os << "connected to (";
        for (auto t : pipe_id) {
            os << " " << this->pipes[t].getName() << ";";
        }
        os << ")" << endl;

        os << "> Want to delete station anyway [N/y]: ";
        string res;
        getline(is, res);
        if (res[0] == 'y') {

        } else {
            return;
        }
    }

    for (auto id : pipe_id)
        this->pipes[id].disconnect();

    this->stations.erase(iter);
    os << "> Deleted" << endl;
}


void GTSystem::deletePipe(istream &is, ostream &os) {
    os << "> Enter id: ";
    uint id;
    cin >> id;
    is.ignore();

    auto iter = pipes.find(id);
    if (iter == this->pipes.end()) {
        os << " Not found." << endl;
        return;
    } else {
        os << "> Founded" << endl;
    }

    os << "> Pipe status: ";
    if (iter->second.isConnected()) {
        os << "Connected" << endl;

        os << "> Want to delete pipe anyway [N/y]: ";
        string res;
        getline(is, res);
        if (res[0] == 'y') {
            // this->pipes.erase(iter);
            // os << "> Deleted" << endl;
        } else {
            return;
        }

    } else {
        os << "Not Connected" << endl;
    }

    this->pipes.erase(iter);
    os << "> Deleted" << endl;
}

bool GTSystem::isStation(uint key) const {
    return this->stations.find(key) != this->stations.end();
}

bool GTSystem::isPipe(uint key) const {
    return this->pipes.find(key) != this->pipes.end();
}


std::vector<vector<uint>> GTSystem::getMaxtrix() {
    vector<uint> row = {0};
    row.resize(this->getStationsNum());
    vector<vector<uint>> mtr;
    for (uint i = 0; i < this->getStationsNum(); i++)
        mtr.push_back(row);

    for (auto &t : this->pipes) {
        pair<uint, uint> ids = t.second.getSTid();
        if (ids.first > 0 && ids.second > 0) {
            if (
              t.second.getLength() < mtr[ids.first - 1][ids.second - 1] ||
              mtr[ids.first - 1][ids.second - 1] == 0
            )
                mtr[ids.first - 1][ids.second - 1] = t.second.getLength();
        }
    }

    return mtr;
}


vector<vector<float>> GTSystem::getEffMaxtrix() {
    vector<float> row = {0};
    row.resize(this->getStationsNum());
    vector<vector<float>> mtr;
    for (uint i = 0; i < this->getStationsNum(); i++)
        mtr.push_back(row);

    for (auto &t : this->pipes) {
        auto p = t.second;
        pair<uint, uint> ids = p.getSTid();

        if (ids.first > 0 && ids.second > 0) {
            float eff = 10 * sqrt( pow(p.getDiam()/1000, 5) / p.getLength() );
            mtr[ids.first - 1][ids.second - 1] += eff;
        }
    }

    return mtr;
}
