#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include "gt_system.h"

using namespace std;


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


template <typename T>
void print_vector(ostream& out, vector<T> arr) {
    for (int i = 0; i < arr.size(); i++) {
        out << " " << arr[i] << '\n';
    }
    out << endl;
}


void waitEnter();

void save(System& gt_sys);
void load(System& gt_sys);
void addPipe(System& gt_sys);
void addStation(System& gt_sys);
void editPipe(System& gt_sys);
void editStation(System& gt_sys);


#endif // FUNC_H
