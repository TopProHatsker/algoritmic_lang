#include <iostream>
#include "new_menu.h"
#include "func.h"
#include "gt_system.h"
#include "graph.h"

using namespace std;

/*
 * _TODO:
 * [ ] реализовать расчет максимального потока в сети;
 * [ ] реализовать расчет кратчайшего пути между заданными КС.
 *
 * [X] Удаление станций
 * [ ] Сохранять в матрицу кратчайший путь при 2 подключниях
 * [ ] Перенести пакетное радактирование в GTSystem
 * [X] выбор станций в пакетном редактировании из найденных
 */


int main() {

    // FIXME
    // - - - - - - - - - - - - - - - - - -

    // // строим graph из заданных ребер
    Graph graph;

    // - - - - - - - - - - - - - - - - - -

    NewMenu menu;
    menu.auto_size();

    GTSystem gt_sys;

    // - - - - - - - - - - - -
    ifstream ifs;
    ifs.open("rus2");
    gt_sys.importFromFile(ifs);
    ifs.close();
    // - - - - - - - - - - - -


    menu_id next = START;

    while (next != NONE) {
        menu.set_page(next);
        next = menu.wait_solution();

        switch (next) {

        case M_PRINT:
            cout << "\n - - - - - | Print Info | - - - - -\n" << endl;
            gt_sys.print(cout);
            waitEnter();
            break;

        case M_FILTER_FIND:
            cout << "\n - - - - - | Filter Find | - - - - -\n" << endl;
            filterFind(gt_sys);
            waitEnter();
            break;

        case M_SAVE:
            cout << "\n - - - - - | Save Data | - - - - -\n" << endl;
            save(gt_sys);
            waitEnter();
            break;

        case M_IMPORT:
            cout << "\n - - - - - | Import Data | - - - - -\n" << endl;
            load(gt_sys);
            waitEnter();
            break;

        case PP_ADD:
            cout << "\n - - - - - | Add pipe | - - - - -\n" << endl;
            gt_sys.addPipe(cin);
            waitEnter();
            break;

        case CS_ADD:
            cout << "\n - - - - - | Add station | - - - - -\n" << endl;
            gt_sys.addStation(cin);
            waitEnter();
            break;

        case PP_EDIT:
            cout << "\n - - - - - | Edit pipe | - - - - -\n" << endl;
            editPipe(gt_sys);
            waitEnter();
            break;

        case CS_EDIT:
            cout << "\n - - - - - | Edit station | - - - - -\n" << endl;
            editStation(gt_sys);
            waitEnter();
            break;

        case PP_DELETE:
            cout << "\n - - - - - | Delete pipe | - - - - -\n" << endl;
            gt_sys.deletePipe(cin, cout);
            waitEnter();
            break;

        case CS_DELETE:
            cout << "\n - - - - - | Delete station | - - - - -\n" << endl;
            gt_sys.deleteStation(cin, cout);
            waitEnter();
            break;

        case GP_PRINT:
            cout << "\n - - - - - | Print Graph | - - - - -\n" << endl;
            graph.loadMatrix(gt_sys.getMaxtrix());
            graph.printMatrix(cout);
            graph.printTopolog(cout);
            waitEnter();
            break;

        case GP_ADDEDGE:
            cout << "\n - - - - - | Add edge in Graph | - - - - -\n" << endl;
            gt_sys.connectPipe(cin, cout);
            waitEnter();
            break;

        case GP_REMOVE_EDGE:
            cout << "\n - - - - - | Remove edge from Graph | - - - - -\n" << endl;
            gt_sys.disconnectPipe(cin, cout);
            waitEnter();
            break;

        default:
            //waitEnter();
            break;
        }

    }

    cout << "Goodbye!" << endl;

    return 0;
}
