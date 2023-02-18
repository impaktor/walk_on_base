#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <iostream>

template <typename T>
class vector2 {
public:
  T x, y;

  vector2() :
    x(0.0f),
    y(0.0f) {}

  vector2(T _x, T _y) :
    x(_x),
    y(_y) {}

  bool operator == (const vector2& coordinates){
    return (x == coordinates.x && y == coordinates.y);
  }
  vector2 operator+(const vector2 &v) const { return vector2(x + v.x, y + v.y); }
  vector2 operator-(const vector2 &v) const { return vector2(x - v.x, y - v.y); }
  vector2 operator-() const { return vector2(-x, -y); }
  vector2 &operator+=(const vector2 &v)
  {
    x += v.x;
    y += v.y;
    return *this;
  }
  vector2 &operator-=(const vector2 &v)
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }
  vector2 &operator*=(const T &a)
  {
    x *= a;
    y *= a;
    return *this;
  }
  friend vector2 operator*(const vector2 &v, const T &a) { return vector2(v.x * a, v.y * a); }
  friend vector2 operator/(const vector2 &v, const T &a) { return vector2(v.x / a, v.y / a); }
  friend vector2 operator/(const vector2 &va, const vector2 &vb) { return vector2(va.x / vb.x, va.y / vb.y); }

  friend std::ostream& operator<<(std::ostream& stream, const vector2& v){
    stream << "(" << v.x << "," << v.y << ")";
    return stream;
  }

};

using vec = vector2<int>;

#endif
