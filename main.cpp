#include <curses.h>
#include <vector>

#include "Headers/clock.h"
#include "Headers/draw.h"
#include "Headers/vec.h"
#include "Headers/objects.h"

const double fpsCap = 60;
const double scale = 20;
const double speedCap = 10;

double screenWidth;
double screenHeight;

double holeSize;
double lastWallHole;

int score = 0;

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
        walls.push_back(Wall(vec2d(screenWidth, 0), vec2d(screenWidth / 20, lastWallHole)));
        walls.push_back(Wall(vec2d(screenWidth, lastWallHole + holeSize), vec2d(screenWidth / 20, screenHeight - (lastWallHole + holeSize))));

        if (rand() % 2 == 0) {
            // Increase the last hole position
            lastWallHole -= holeSize;
            if (lastWallHole < 0) lastWallHole = 0;
        } else {
            // Decrease the last hole position
            lastWallHole += holeSize;
            if (lastWallHole > screenHeight - holeSize) lastWallHole = screenHeight - holeSize;
        }
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
    // Seed random for the wall positions
    srand(time(NULL));

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

    // Set the last wall hole position and make a new set of walls
    holeSize = screenHeight / 5;
    lastWallHole = screenHeight / 2 - holeSize / 2;

    std::vector<Wall> walls;
    walls.push_back(Wall(vec2d(screenWidth, 0), vec2d(screenWidth / 20, lastWallHole)));
    walls.push_back(Wall(vec2d(screenWidth, lastWallHole + holeSize), vec2d(screenWidth / 20, screenHeight - (lastWallHole + holeSize))));

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

        mvprintw(0, 0, "Score: %d", score / 2);

        // Update all of the walls and draw them
        for (int i = 0; i < (int)walls.size(); i++) {
            walls[i].Draw();
            walls[i].Update();

            if (walls[i].m_pos.x + walls[i].m_size.x <= 0) {
                walls.erase(walls.begin() + i);
                score++;
            }
        }

        // Write the changes to the console
        refresh();

        // Cap the framerate so the speed is consistent
        timer.CapFPS(fpsCap);

        if (BirdColliding(b, walls) || b.m_pos.y > screenHeight) break;
    }

    // Pause for input before cleaning up and exiting
    mvprintw(0, 0, "Score: %d", score / 2);
    mvprintw(LINES / 2, COLS / 2, "GAME OVER | PRESS Q TO EXIT");
    while (getch() != 'q') {}
    endwin();

    return 0;
}
