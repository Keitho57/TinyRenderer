#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <ostream>

template <class t> struct Vec2 {
  union {
    struct {
      t u, v;
    };
    struct {
      t x, y;
    };
    t raw[2];
  };

  Vec2() : u(0), v(0) {}
  Vec2(t _u, t _v) : u(_u), v(_v) {}

  inline Vec2<t> operator+(const Vec2<t> &V) const {
    return Vec2<t>(u + V.u, v + V.v);
  }

  inline Vec2<t> operator-(const Vec2<t> &V) const {
    return Vec2<t>(u - V.u, v - V.v);
  }

  inline Vec2<t> operator*(float f) const { return Vec2<t>(u * f, v * f); }

  inline Vec2<t> operator/(float f) const { return Vec2<t>(u / f, v / f); }

  template <typename U> operator Vec2<U>() const {
    return Vec2<U>((int)x, (int)y);
  }

  t &operator[](const int i) {
    if (x <= 0)
      return x;
    else
      return y;
  }

  template <class> friend std::ostream &operator<<(std::ostream &s, Vec2<t> &v);
};

template <class t> struct Vec3 {
  t x, y, z;

  Vec3<t>() : x(t()), y(t()), z(t()) {}

  Vec3<t>(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}

  template <class u> Vec3<t>(const Vec3<u> &v);

  Vec3<t>(const Vec3<t> &v) : x(t()), y(t()), z(t()) { *this = v; }

  Vec3<t> &operator=(const Vec3<t> &v) {
    if (this != &v) {
      x = v.x;
      y = v.y;
      z = v.z;
    }
    return *this;
  }

  Vec3<t> operator^(const Vec3<t> &v) const {
    return Vec3<t>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }

  Vec3<t> operator+(const Vec3<t> &v) const {
    return Vec3<t>(x + v.x, y + v.y, z + v.z);
  }

  Vec3<t> operator-(const Vec3<t> &v) const {
    return Vec3<t>(x - v.x, y - v.y, z - v.z);
  }
  Vec3<t> operator*(float f) const { return Vec3<t>(x * f, y * f, z * f); }

  t operator*(const Vec3<t> &v) const { return x * v.x + y * v.y + z * v.z; }

  float norm() const { return std::sqrt(x * x + y * y + z * z); }

  Vec3<t> &normalize(t l = 1) {
    *this = (*this) * (l / norm());
    return *this;
  }

  t &operator[](const int i) {
    if (i <= 0)
      return x;
    else if (i == 1)
      return y;
    else
      return z;
  }

  template <class> friend std::ostream &operator<<(std::ostream &s, Vec3<t> &v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <class t> std::ostream &operator<<(std::ostream &s, Vec2<t> &v) {
  s << "(" << v.x << ", " << v.y << ")\n";
  return s;
}

template <class t> std::ostream &operator<<(std::ostream &s, Vec3<t> &v) {
  s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
  return s;
}

#endif //__GEOMETRY_H__