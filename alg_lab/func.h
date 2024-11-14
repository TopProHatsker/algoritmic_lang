#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include "cstdio"
#include "gt_system.h"

using namespace std;
// TODO:

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
void print_arr(ostream& out, unordered_map<uint, T> arr) {
    for (auto& t : arr) {
        out << " " << t.second << '\n';
    }
    out << endl;
}


void waitEnter();

void save(GTSystem& gt_sys);
void load(GTSystem& gt_sys);
void addPipe(GTSystem& gt_sys);
void addStation(GTSystem& gt_sys);
void editPipe(GTSystem& gt_sys);
void editStation(GTSystem& gt_sys);

void filterFind(GTSystem& gt_sys);



#define ST_HEADER \
    printf("  ID|                 Name| Total|  Work|Efficiency\n"); \
    printf("----+---------------------+------+------+----------\n");

#define PP_HEADER \
    printf("  ID|S_ID|D_ID|                 Name|  Diam|Length|OnRepair\n"); \
    printf("----+----+----+---------------------+------+------+---------\n");


bool CheckPPDiamAndFree(const Pipe& p, const void * diam);
bool CheckPPConnected(const Pipe& p, const void * is_connected);


#endif // FUNC_H
