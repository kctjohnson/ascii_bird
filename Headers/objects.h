#pragma once

#include "vec.h"

class Collidable {
public:
    vec2d m_pos, m_size;

    // Returns true for collide, false if not
    bool CheckCollision(Collidable c);

    virtual void Draw();
    virtual void Update();
};

class Wall : Collidable {
public:
    void Draw();
    void Update();
};

class Bird : Collidable {
public:
    vec2d m_vel;

    Bird(vec2d start);

    void Flap();

    void Draw();
    void Update();
};
