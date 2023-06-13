#ifndef H_VEC2
#define H_VEC2

class Vec2 {
private:
    float x, y;
public:
    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& rhs);
    Vec2 operator-(const Vec2& rhs);
    Vec2 operator*(float rhs);
};

#endif