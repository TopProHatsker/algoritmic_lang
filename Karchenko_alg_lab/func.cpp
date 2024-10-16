#include "func.h"

#include <limits>


template <typename T>
T check_input(T min, T max)
{
    T x;
    while ((cin >> x).fail() || (cin).peek() != '\n' || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n!> Enter the correct data (" << min << " - " << max << ") ";
    }
    return x;
}


// template <typename T>
// void print_vector(ostream& out, vector<T> arr) {
//     for (int i = 0; i < arr.size(); i++) {
//         out << " " << i << ") " << arr[i] << '\n';
//     }
//     out << endl;
// }


void waitEnter() {
    cout << "\n < Press Enter to continue >" << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}




void save(System& gt_sys) {
    cout << "Enter filename to save: ";
    string fname;
    cin >> fname;

    ofstream ofs;

    ofs.open(fname);
    int res = gt_sys.saveToFile(ofs);
    ofs.close();

    if (res) {
        cout << "> Error while saving!" << endl;
    } else {
        cout << "> Saved successfully" << endl;
    }

    cin.ignore();
}


void load(System& gt_sys) {
    cout << "Enter filename: ";
    string fname;
    cin >> fname;

    ifstream ifs;

    ifs.open(fname);
    int res = gt_sys.importFromFile(ifs);
    ifs.close();

    if (res) {
        cout << "> Error while reading!" << endl;
    } else {
        cout << "> Loaded successfully" << endl;
    }

    cin.ignore();
}


void addPipe(System& gt_sys) {
    Pipe p;
    cin >> p;
    gt_sys.add(p);
    cin.ignore();
}


