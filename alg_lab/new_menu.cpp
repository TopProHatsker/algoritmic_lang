#include "new_menu.h"

int print_centered(FILE *stream, const char *s, unsigned int width) {
    const size_t len = strlen(s);
    if (len >= width)
        return fprintf(stream, "%s\n", s);
    const unsigned int p = (len >= width) ? 0 : (width - len) / 2;
    return fprintf(stream, "%*.*s%s%*.*s", p, p, " ", s, p, p, " ");
}


uint8_t max_str_len(std::vector<Button> vec) {
    uint8_t max = 0;
    for (uint8_t i = 0; i < vec.size(); i++) {
        (vec[i].data.length() > max) ? max = vec[i].data.length() : max;
    }
    return max;
}


#include <termios.h>

bool kbhit()
{
    struct termios term;
    tcgetattr(0, &term);

    struct termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}


int mygetch( ) {
    struct termios oldt,
        newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


Direction check_key() {
    Direction dir = NO_INP;
    if (kbhit()) {
        if (mygetch() == 10) return ENTER;
        if (mygetch() == 10) return ENTER;
        switch (mygetch()) {
        case 65: dir = UP; break;
        case 66: dir = DOWN; break;
        case 10: dir = ENTER; break;
        default:  break;
        }
    }
    return dir;
}
