#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& rhs) {
    Vec2 result(this->x + rhs.x, this->y + rhs.y);
    return result;
}

Vec2 Vec2::operator-(const Vec2& rhs) {
    Vec2 result(this->x - rhs.x, this->y - rhs.y);
    return result;
}

Vec2 Vec2::operator*(float rhs) {
    Vec2 result(this->x * rhs, this->y + rhs);
    return result;
}