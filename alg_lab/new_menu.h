#ifndef NEW_MENU_H
#define NEW_MENU_H

#include <iostream>
#include <math.h>
#include <cstdint>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <vector>
#include <limits>
#include "res.pages"


int print_centered(FILE *stream, const char *s, unsigned int width);
uint8_t max_str_len(std::vector<Button>);
enum Direction {
    DOWN,
    UP,
    ENTER,
    NO_INP
};
Direction check_key();

class NewMenu {

private:

    Page EmptyPage = {
        .id = NONE,
        .title = "Empty page"
    };

    Page curr_page = EmptyPage;
    struct winsize w = {0, 0, 0, 0};

public:
    NewMenu() {}

    void auto_size() {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    }

    bool set_page(menu_id uid) {
        for (uint8_t i = 0; i < book.pages.size(); i++) {
            if (book.pages[i].id == uid) {
                curr_page = book.pages[i];
                return false;
            }
        }
        return true;
    }

    void show(uint8_t sel_row) {
        system("clear");

        // Calc box size
        uint8_t max_len = 0;
        if (curr_page.id == EmptyPage.id) {
            max_len = 12;
        } else {
            max_len = std::max((int)max_str_len(curr_page.btn), 12);
        }


        // - - - - - BOX - - - - -
        // Spacer
        for(size_t i = 0; i < w.ws_row/10; i++)
            printf("\n");

        // Head
        std::string t = "/ <" + curr_page.title + "> " + std::string(max_len-curr_page.title.length()+4, '-') + "\\";
        print_centered(stdout, t.c_str(), w.ws_col);
        std::cout << std::endl;

        // Body
        if (curr_page.btn.empty()) {
            t = "| " + std::string(max_len+6, ' ') + " |";
            print_centered(stdout, t.c_str(), w.ws_col);
            std::cout << std::endl;
        }
        for (uint8_t i = 0; i < curr_page.btn.size(); i++) {
            t =
                "|" +
                std::string(">", sel_row == i) +
                std::string(" ", sel_row != i) +
                curr_page.btn[i].data +
                std::string(max_len+6 - curr_page.btn[i].data.length(), ' ') +
                std::string("<", sel_row == i) +
                std::string(" ", sel_row != i) +
                "|";
            print_centered(stdout, t.c_str(), w.ws_col);
            std::cout << std::endl;
        }

        // Footer
        t = "\\" + std::string(max_len+8, '_') + "/";
        print_centered(stdout, t.c_str(), w.ws_col);
        std::cout << std::endl;
        // - - - - - BOX - - - - -

    }

    menu_id wait_solution() {
        // - - - - TYC TYC - - - -
        uint8_t sel_row = 0;
        bool redraw = true;
        do {
            if (redraw) show(sel_row);
            redraw = false;
            Direction dir = check_key();
            if(dir == UP && sel_row > 0)
                sel_row--;
            if(dir == DOWN && sel_row < curr_page.btn.size() - 1)
                sel_row++;
            if(dir == ENTER)
                break;
            if(dir != NO_INP)
                redraw = true;
        } while (true);
        return curr_page.btn[sel_row].next;
        // - - - - TYC TYC - - - -
    }

};

#endif // NEW_MENU_H




//        int item_num = -1;
//        while(true) {
//            std::cout << " Enter num: ";
//            std::cin >> item_num;
//            if (!std::cin.good() || item_num <= 0 || (unsigned)item_num > curr_page.btn.size()) {
//                if (std::cin.eof()) {
//                    return NONE;
//                }
//                std::cout << "Incorrect" << std::endl;
//                std::cin.clear();
//                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                continue;
//            } else {
//                break;
//            }
//        }
