#include <iostream>
#include "new_menu.h"
#include "func.h"
#include "gt_system.h"

using namespace std;

/*
 * _TODO:
 * [X] edit
 * [ ] delete
 * [X] filer find
 * [ ] package changing
 */


int main() {

    NewMenu menu;
    menu.auto_size();

    GTSystem gt_sys;

    menu_id next = START;

    while (next != NONE) {
        menu.set_page(next);
        next = menu.wait_solution();

        switch (next) {

        case M_PRINT:
            cout << "\n - - - - - | Print Info | - - - - -\n" << endl;
            gt_sys.print(cout);
            break;

        case M_FILTER_FIND:
            cout << "\n - - - - - | Filter Find | - - - - -\n" << endl;
            filterFind(gt_sys);
            break;

        case M_SAVE:
            cout << "\n - - - - - | Save Data | - - - - -\n" << endl;
            save(gt_sys);
            break;

        case M_IMPORT:
            cout << "\n - - - - - | Import Data | - - - - -\n" << endl;
            load(gt_sys);
            break;

        case M_ADD_PIPE:
            cout << "\n - - - - - | Add pipe | - - - - -\n" << endl;
            addPipe(gt_sys);
            break;

        case M_ADD_CS:
            cout << "\n - - - - - | Add station | - - - - -\n" << endl;
            addStation(gt_sys);
            break;

        case M_EDIT_PIPE:
            cout << "\n - - - - - | Edit pipe | - - - - -\n" << endl;
            editPipe(gt_sys);
            break;

        case M_EDIT_CS:
            cout << "\n - - - - - | Edit station | - - - - -\n" << endl;
            //editStation(gt_sys); // TODO:
            break;

        default:
            break;
        }

        waitEnter();
    }

    cout << "Goodbye!" << endl;

    return 0;
}
