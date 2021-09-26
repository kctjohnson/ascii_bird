#pragma once

#include "vec.h"

extern const double scale;
extern const double speed_cap;

class Collidable {
public:
    vec2d m_pos, m_size;

    // Returns true for collide, false if not
    bool CheckCollision(Collidable c);

    void Draw() {}
    void Update() {}
};

class Wall : public Collidable {
public:
    Wall(vec2d start, vec2d size);

    void Draw();
    void Update();
};

class Bird : public Collidable {
public:
    vec2d m_vel;

    Bird(vec2d start);

    void Flap();

    void Draw();
    void Update();
};
