#include "func.h"
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


void addPipe(GTSystem& gt_sys) {
    Pipe p;
    cin >> p;
    gt_sys.add(p);
    cin.ignore();
}


void addStation(GTSystem& gt_sys) {
    Station s;
    cin >> s;
    gt_sys.add(s);
    cin.ignore();
}

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
template<typename T>
using Filter = bool(*)(const Pipe & p, T param);

bool CheckOnRepair(const Pipe& p, bool on_repair) {
    return p.isRepair() == on_repair;
}


void filterFind(GTSystem& gt_sys) {
    cout << "> Select type (Station - 1, Pipe - 2): ";
    int res1 = check_input(1, 2);

    bool (*filter) (const Pipe&, T );

    if (res1 == 1){    // Station
        cerr << "TODO:"; // TODO:
    } else {            // Pipe
        cout << "> Select filter (by Name - 1, OnRepair - 2): ";
        int res = check_input(1, 2);

        if (res == 1){
            cerr << "TODO:"; // TODO:
        } else {
            filter = CheckOnRepair;
        }
    }

    cin.ignore();
}