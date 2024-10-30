#include "func.h"
#include <cstdint>
#include <vector>
#include <limits>


void waitEnter() {
    cout << "\n < Press Enter to continue >" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void save(GTSystem& gt_sys) {
    cout << "Enter filename to save: ";
    string fname;
    getline(cin, fname);
    //cin >> fname;

    ofstream ofs;

    ofs.open(fname);
    if (!ofs.is_open()) {
        cout << "!> Error openning!" << endl;
        cin.ignore();
        return;
    }
    int res = gt_sys.saveToFile(ofs);
    ofs.close();

    if (res) {
        cout << "!> Error while saving!" << endl;
    } else {
        cout << "> Saved successfully" << endl;
    }

    //cin.ignore();
}


void load(GTSystem& gt_sys) {
    cout << "Enter filename: ";
    string fname;
    //cin >> fname;
    getline(cin, fname);

    ifstream ifs;

    ifs.open(fname);
    if (!ifs.is_open()) {
        cout << "!> Error openning!" << endl;
        cin.ignore();
        return;
    }
    int res = gt_sys.importFromFile(ifs);
    ifs.close();

    if (res) {
        cout << "!> Error while reading!" << endl;
    } else {
        cout << "> Loaded successfully" << endl;
    }

    //cin.ignore();
}


// void addPipe(GTSystem& gt_sys) {
//     Pipe p;
//     cin >> p;
//     gt_sys.add(p);
//     cin.ignore();
// }


// void addStation(GTSystem& gt_sys) {
//     Station s;
//     cin >> s;
//     gt_sys.add(s);
//     cin.ignore();
// }

/*
void editPipe(GTSystem& gt_sys) {
    cout << "Pipes:" << endl;
    auto pipes = gt_sys.getPipes();
    print_vector(cout, pipes);

    if (!pipes.size())
        return;

    cout << "Enter num to edit: ";
    uint num = check_input(1, (int)pipes.size());
    num--;
    //gts.editPipe(num, state);
    //Pipe* pipe = &(*pipes)[num];
    pipes[num].setRepairStatus(true);
    pipes[num].print();
    Pipe& yaPipe = &(*pipes->begin()) + sizeof(Pipe)*num;
    yaPipe->print();
    pipe->print();

    cout << "\nEnter new repair status (1 - on repair | 0 - not): ";
    bool new_repair_st = check_input(0, 1);
    pipe->setRepairStatus(new_repair_st);

    cout << "\nNew pipe: " << endl;
    pipe->print();

    cin.ignore();
}
*/

/*
void editStation(GTSystem& gt_sys) {
    cout << "Stations:" << endl;
    auto stations = gt_sys.getStations();
    print_vector(cout, *stations);

    if (!stations->size())
        return;

    cout << "Enter num to edit: ";
    uint num = check_input(1, (int)stations->size());
    num--;

    Station* station = &(*stations)[num];
    station->print();

    cout << "Enter new work WS number: ";
    uint new_WS_num = check_input(0, (int)station->getTotalWS());
    station->setWorkWS(new_WS_num);

    cout << "\nNew station: " << endl;
    station->print();

    cin.ignore();
}
*/

bool CheckPPName(const Pipe& p, const void * name) {
    return p.getName() == *(string*)name;
}

bool CheckOnRepair(const Pipe& p, const void * on_repair) {
    return p.isRepair() == *(bool*)on_repair;
}

bool CheckSTName(const Station& s, const void * name) {
    return s.getName() == *(string*)name;
}

bool CheckPercent(const Station& s, const void * perc) {
    return s.getUnUsagePerc() >= *(float*)perc;
}

vector<uint> selectStations(GTSystem& gt_sys) {
    cout <<
        "> Select filter "
        "(by Name - 1, The % of unused WS - 2): ";
    int res_filt = check_input(1, 2);

    auto filter = CheckPercent;
    void * param;
    string name;
    float perc;

    if (res_filt == 1) {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        param = &name;
        filter = CheckSTName;
    } else {
        cout << "Enter perc: ";
        cin >> perc;
        cin.ignore();
        param = &perc;
    }

    cout << endl;
    ST_HEADER

    vector<uint> res;
    for(auto& t: gt_sys.getStations()) {
        if (filter(t.second, param)) {
            res.push_back(t.second.getId());
            cout << " " << t.second << '\n';
        }
    }
    cout << endl;

    return res;
}


vector<uint> selectPipes(GTSystem& gt_sys) {
    cout <<
        "> Select filter "
        "(by Name - 1, OnRepair - 2): ";
    int res_filt = check_input(1, 2);

    auto filter = CheckOnRepair;
    void * param;
    string name;
    bool on_repair;

    if (res_filt == 1) {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        param = &name;
        filter = CheckPPName;
    } else {
        cout << "Enter on_repair: ";
        on_repair = check_input(false, true);
        cin.ignore();
        param = &on_repair;
    }

    cout << endl;
    PP_HEADER

    vector<uint> res;
    for(auto& t: gt_sys.getPipes()) {
        if (filter(t.second, param)) {
            res.push_back(t.second.getId());
            cout << " " << t.second << '\n';
        }
    }
    cout << endl;

    return res;
}


void filterFind(GTSystem& gt_sys) {
    cout << "> Select type (Station - 1, Pipe - 2): ";
    int res_obj = check_input(1, 2);

    if (res_obj == 1) {
        selectStations(gt_sys);
        // TODO: print here
    } else {
        selectPipes(gt_sys);
        // TODO:
    }
}


void editPipe(GTSystem& gt_sys) {
    if (gt_sys.getPipesNum() == 0) {
        cout << " Empty" << endl;
        return;
    }

    cout << "> Edit (by Index - 1, By Filter - 2): ";
    int res = check_input(1, 2);

    if (res == 1) {

        Pipe p;
        try {
            cout << "Enter ID: ";
            uint id = check_input(0, numeric_limits<int32_t>::max());
            gt_sys.editPipe(id);

        } catch (...) {
            std::cout << "Error" << std::endl;
        }

    } else {

        vector<uint> selc_id = selectPipes(gt_sys);
        if (selc_id.empty()) {
            cout << " Empty" << endl;
            return;
        }

        cout << "\nEdit:\n\n";
        for (auto id: selc_id) {
            gt_sys.editPipe(id);
            cout << "\n\n";
        }

    }

    cin.ignore();
}



void editStation(GTSystem& gt_sys) {
    if (gt_sys.getStationsNum() == 0) {
        cout << " Empty" << endl;
        return;
    }

    cout << "> Edit (by Index - 1, By Filter - 2): ";
    int res = check_input(1, 2);

    if (res == 1) {

        Station s;
        try {
            cout << "Enter ID: ";
            uint id = check_input(0, numeric_limits<int32_t>::max());
            gt_sys.editStation(id);

        } catch (...) {
            std::cout << "Error" << std::endl;
        }

    } else {

        vector<uint> selc_id = selectStations(gt_sys);
        if (selc_id.empty()) {
            cout << " Empty" << endl;
            return;
        }

        cout << "\nEdit:\n\n";
        for (auto id: selc_id) {
            gt_sys.editStation(id);
            cout << "\n\n";
        }

    }

    cin.ignore();
}
