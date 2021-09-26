#include <curses.h>

#include "Headers/clock.h"

const double fps_cap = 60;

int main() {
    // Initialize all of the needed bits for curses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);

    // No pesky cursor randomly showing up!
    curs_set(0);

    // Small clock object to cap the fps
    Clock timer;
    timer.Start();

    while (true) {
        // Clear the beginning screen
        clear();

        // Write the changes to the console
        refresh();

        // Cap the framerate so the speed is consistent
        timer.CapFPS(fps_cap);
    }

    // Pause for input before cleaning up and exiting
    getch();
    endwin();

    return 0;
}
