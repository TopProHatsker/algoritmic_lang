#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include "gt_system.h"

using namespace std;


template <typename T>
T check_input(T min, T max);


// template <typename T>
// void print_vector(ostream& out, vector<T> arr);


void waitEnter();

void save(System& gt_sys);
void load(System& gt_sys);
void addPipe(System& gt_sys);
void addStation(System& gt_sys);
void editPipe(System& gt_sys);
void editStation(System& gt_sys);


#endif // FUNC_H
