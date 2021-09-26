#include "../Headers/objects.h"
#include "../Headers/draw.h"

extern double scale;
extern double speed_cap;

bool Collidable::CheckCollision(Collidable c) {
    return (c.m_pos.x >= this->m_pos.x &&
            c.m_pos.x <= this->m_pos.x + this->m_size.x &&
            c.m_pos.y >= this->m_pos.y &&
            c.m_pos.y <= this->m_pos.y + this->m_size.y);
}

void Wall::Draw() {

}

void Wall::Update() {

}

Bird::Bird(vec2d start) {
    m_pos.set(start);
    m_vel.set(0.0, 0.0);
}

void Bird::Flap() {
    m_vel.set(0, speed_cap);
}

void Bird::Draw() {
    int showX = (int)(this->m_pos.x / scale);
    int showY = (int)(this->m_pos.y / scale);
    Point(showX, showY, '>');
}

void Bird::Update() {
    vec2d gravity(0, -1);
    m_vel.add(gravity);
    m_vel.limit(speed_cap);

    m_pos.add(m_vel);
}
