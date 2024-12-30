#include "geometry.h"
#include "triangle.h"

// the coordinates of point p as a ratio between sub traingle and whole triangle
Vec3f getBarycentricCoords(Vec2i *pts, Vec2i P) {
  Vec3f u = Vec3f(pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x) ^
            Vec3f(pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y);

  if (std::abs(u.z) < 1)
    return Vec3f(-1, 1, 1);

  return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

Vec3f crossProduct(const Vec3f &v1, const Vec3f &v2) {
  return Vec3f{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
               v1.x * v2.y - v1.y * v2.x};
}

Vec3f getBarycentricCoords(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
  Vec3f s[2];
  for (int i = 2; i--;) {
    s[i].x = C[i] - A[i];
    s[i].y = B[i] - A[i];
    s[i].z = A[i] - P[i];
  }

  Vec3f u = crossProduct(s[0], s[1]);
  if (std::abs(u.z) > 1e-2) // ABC is degenerate
    return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
  return Vec3f(-1, 1, 1);
}

Vec3f getBarycentricCoords(Trianglef triangle, Vec3f P) {
  Vec3f s[2];
  for (int i = 2; i--;) {
    s[i].x = triangle[2][i] - triangle[0][i];
    s[i].y = triangle[1][i] - triangle[0][i];
    s[i].z = triangle[0][i] - P[i];
  }

  Vec3f u = crossProduct(s[0], s[1]);
  if (std::abs(u.z) > 1e-2)
    return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
  return Vec3f(-1, 1, 1);
}
