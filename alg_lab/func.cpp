#include "func.h"
#include <cstdint>
#include <vector>
#include <limits>
#include <sstream>
#include <algorithm>

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


// bool CheckPPDiamAndFree(const Pipe& p, const void * diam) {
//     return (p.getDiam() == *(uint*)diam) && (p.isConnected() == 0);
// }

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

bool CheckPPDiamAndFree(const Pipe& p, const void * diam) {
    return (p.getDiam() == *(uint*)diam) && (p.isConnected() == 0);
}

bool CheckPPConnected(const Pipe& p, const void * is_connected) {
    return p.isConnected() == *(bool*)is_connected;
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

    //cout << endl;
    //ST_HEADER

    vector<uint> res;
    for(auto& t: gt_sys.getStations()) {
        if (filter(t.second, param)) {
            res.push_back(t.second.getId());
            //cout << " " << t.second << '\n';
        }
    }
    //cout << endl;

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

    //cout << endl;
    //PP_HEADER

    vector<uint> res;
    for(auto& t: gt_sys.getPipes()) {
        if (filter(t.second, param)) {
            res.push_back(t.second.getId());
            //cout << " " << t.second << '\n';
        }
    }
    //cout << endl;

    return res;
}


void filterFind(GTSystem& gt_sys) {
    cout << "> Select type (Station - 1, Pipe - 2): ";
    int res_obj = check_input(1, 2);

    if (res_obj == 1) {
        auto arr = selectStations(gt_sys);

        cout << endl;
        ST_HEADER
        for(auto& id: arr) {
            Station t = gt_sys.getStation(id);
            cout << " " << t << '\n';
        }

        cout << endl;

    } else {
        auto arr = selectPipes(gt_sys);

        cout << endl;
        PP_HEADER
        for(auto& id: arr) {
            Pipe t = gt_sys.getPipe(id);
            cout << " " << t << '\n';
        }

        cout << endl;
    }
}


void enterNewRepairStatus(GTSystem& gt_sys, vector<uint> id) {
    cout << "\n Enter new repair status: ";
    bool status = check_input(false, true);
    for (auto t: id) {
        gt_sys.editPipeStatus(t, status);
    }
}


void enterNewEfficiency(GTSystem& gt_sys, vector<uint> id) {
    cout << "\n Enter new efficiency: ";
    float eff = check_input(0., 10.);
    for (auto t: id) {
        gt_sys.editStationEff(t, eff);
    }
}


vector<uint> readNumbers() {
    vector<uint> numbers;
    string line;

    // Считываем всю строку
    cin.ignore();
    getline(cin, line);
    istringstream iss(line);
    uint number;

    // Извлекаем числа из строки
    while (iss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

vector<uint> selectSertain(vector<uint> Numbers) {

    cout << "\n Enter IDs to edit (1 2 5...): ";
    vector<uint> userNumbers = readNumbers();

    // Вектор для хранения совпадающих чисел
    vector<uint> matchingNum;

    // Находим совпадающие числа
    for (uint t : userNumbers) {
        if (
            find(
                Numbers.begin(),
                Numbers.end(),
                t
            ) != Numbers.end()

        ) {
            matchingNum.push_back(t);
        }
    }

    return matchingNum;
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

        cout << "\n";
        PP_HEADER
        for(auto& id: selc_id) {
            Pipe t = gt_sys.getPipe(id);
            cout << " " << t << '\n';
        }
        cout << endl;

        cout << "> Edit (All - 1, Certain - 2): ";
        uint res2 = check_input(1, 2);

        if (res2 == 1) {
            enterNewRepairStatus(gt_sys, selc_id);
        } else {
            vector<uint> ids = selectSertain(selc_id);

            // // Выводим совпадающие числа
            // if (!ids.empty()) {
            //     std::cout << "Совпадающие числа: ";
            //     for (int num : ids) {
            //         std::cout << num << " ";
            //     }
            //     std::cout << std::endl;
            // } else {
            //     std::cout << "Совпадений не найдено." << std::endl;
            // }

            enterNewRepairStatus(gt_sys, ids);
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

        cout << "\n";
        ST_HEADER
            for(auto& id: selc_id) {
            Station t = gt_sys.getStation(id);
            cout << " " << t << '\n';
        }
        cout << endl;

        cout << "> Edit (All - 1, Certain - 2): ";
        uint res2 = check_input(1, 2);

        if (res2 == 1) {
            enterNewEfficiency(gt_sys, selc_id);
        } else {
            vector<uint> ids = selectSertain(selc_id);
            enterNewEfficiency(gt_sys, ids);
        }

        // cout << "\nEdit:\n\n";
        // for (auto id: selc_id) {
        //     gt_sys.editStation(id);
        //     cout << "\n\n";
        // }

    }

    cin.ignore();
}
