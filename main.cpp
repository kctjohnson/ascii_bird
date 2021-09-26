#include <curses.h>

#include "Headers/clock.h"
#include "Headers/draw.h"
#include "Headers/vec.h"
#include "Headers/objects.h"

const double fps_cap = 60;
const double scale = 20;
const double speed_cap = 10;

bool HandleInput(Bird& b) {
    char c = getch();
    switch (c) {
        case 'q':
            return false;

        case ' ':
            b.Flap();
            break;
    }
    return true;
}

int main() {
    // Initialize all of the needed bits for curses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);

    // No pesky cursor randomly showing up!
    curs_set(0);

    // Our sweet new bird object
    Bird b(vec2d(100, 50));
    Wall w(vec2d(300, 0), vec2d(10, 100));

    // Small clock object to cap the fps
    Clock timer;
    timer.Start();

    while (HandleInput(b)) {
        // Clear the beginning screen
        clear();

        w.Update();
        w.Draw();

        b.Update();
        b.Draw();

        // Write the changes to the console
        refresh();

        // Cap the framerate so the speed is consistent
        timer.CapFPS(fps_cap);
    }

    // Pause for input before cleaning up and exiting
    endwin();

    return 0;
}
