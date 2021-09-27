#include "../Headers/objects.h"
#include "../Headers/draw.h"

bool Collidable::CheckCollision(Collidable c) {
    return (this->m_pos.x >= c.m_pos.x &&
            this->m_pos.x + this->m_size.x <= c.m_pos.x + c.m_size.x &&
            this->m_pos.y >= c.m_pos.y &&
            this->m_pos.y + this->m_size.y <= c.m_pos.y + c.m_size.y);
}

Wall::Wall(vec2d start, vec2d size) {
    m_pos.set(start);
    m_size.set(size);
}

void Wall::Draw() {
    int showX = (int)(this->m_pos.x / scale);
    int showY = (int)(this->m_pos.y / scale);
    int showW = (int)(this->m_size.x / scale);
    int showH = (int)(this->m_size.y / scale);
    Rect(showX, showY, showW, showH);
}

void Wall::Update() {
    m_pos.sub(speedCap, 0);
}

Bird::Bird(vec2d start) {
    m_pos.set(start);
    m_size.set(scale, scale);
    m_vel.set(0.0, 0.0);
}

void Bird::Flap() {
    m_vel.set(0, -speedCap);
}

void Bird::Draw() {
    int showX = (int)(this->m_pos.x / scale);
    int showY = (int)(this->m_pos.y / scale);
    Point(showX, showY, '>');
}

void Bird::Update() {
    vec2d gravity(0, 0.3);
    m_vel.add(gravity);
    m_vel.limit(speedCap);

    m_pos.add(m_vel);
}
