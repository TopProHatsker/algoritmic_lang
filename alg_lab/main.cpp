#include <iostream>
#include "new_menu.h"
#include "func.h"
#include "gt_system.h"

using namespace std;

/*
 * _TODO:
 * [ ] добавить возможность соединения труб и КС в газотранспортную сеть;
 * [ ] реализовать топологическую сортировку полученного графа.
 *
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
            gt_sys.addPipe(cin);
            break;

        case M_ADD_CS:
            cout << "\n - - - - - | Add station | - - - - -\n" << endl;
            gt_sys.addStation(cin);
            break;

        case M_EDIT_PIPE:
            cout << "\n - - - - - | Edit pipe | - - - - -\n" << endl;
            editPipe(gt_sys);
            break;

        case M_EDIT_CS:
            cout << "\n - - - - - | Edit station | - - - - -\n" << endl;
            editStation(gt_sys);
            break;

        case M_DELETE_PIPE:
            cout << "\n - - - - - | Delete pipe | - - - - -\n" << endl;
            gt_sys.deletePipe(cin, cout);
            break;

        case M_DELETE_CS:
            cout << "\n - - - - - | Delete station | - - - - -\n" << endl;
            gt_sys.deleteStation(cin, cout);
            break;

        default:
            break;
        }

        waitEnter();
    }

    cout << "Goodbye!" << endl;

    return 0;
}
