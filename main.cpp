#include <curses.h>
#include <vector>

#include "Headers/clock.h"
#include "Headers/draw.h"
#include "Headers/vec.h"
#include "Headers/objects.h"

const double fps_cap = 60;
const double scale = 20;
const double speed_cap = 10;

double screenWidth;
double screenHeight;

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

void AddWall(std::vector<Wall>& walls) {
    // Add one if the last wall is past a certain point
    if (walls[walls.size() - 1].m_pos.x < (screenWidth / 5.0 * 4)) {
        walls.push_back(Wall(vec2d(screenWidth, 0), vec2d(screenWidth / 20, screenHeight)));
    }
}

bool BirdColliding(Bird b, std::vector<Wall> walls) {
    for (auto wall : walls) {
        if (b.CheckCollision(wall)) {
            return true;
        }
    }

    return false;
}

int main() {
    // Initialize all of the needed bits for curses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);

    // Set up the screen info
    screenWidth = COLS * scale;
    screenHeight = LINES * scale;

    // No pesky cursor randomly showing up!
    curs_set(0);

    // Our sweet new bird object
    Bird b(vec2d(screenWidth / 100, screenHeight / 2));
    b.Flap();

    std::vector<Wall> walls;
    walls.push_back(Wall(vec2d(screenWidth, 0), vec2d(screenWidth / 20, screenHeight)));

    // Small clock object to cap the fps
    Clock timer;
    timer.Start();

    while (HandleInput(b)) {
        // Clear the beginning screen
        clear();

        // Update the bird and draw it
        b.Update();
        b.Draw();

        AddWall(walls);

        // Update all of the walls and draw them
        for (int i = 0; i < walls.size(); i++) {
            walls[i].Draw();
            walls[i].Update();

            if (walls[i].m_pos.x + walls[i].m_size.x <= 0) {
                walls.erase(walls.begin() + i);
            }
        }

        // Debug info
        mvprintw(0, 15, "Walls: %d", walls.size());
        mvprintw(1, 15, "Colliding: %s", BirdColliding(b, walls) ? "true" : "false");
        // Write the changes to the console
        refresh();

        // Cap the framerate so the speed is consistent
        timer.CapFPS(fps_cap);
    }

    // Pause for input before cleaning up and exiting
    endwin();

    return 0;
}
