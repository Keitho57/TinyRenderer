#include <geometry.h>

// the coordinates of point p as a ratio between sub traingle and whole triangle
Vec3f getBarycentricCoords(Vec2i *pts, Vec2i P) {
  Vec3f u = Vec3f(pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x) ^
            Vec3f(pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y);

  if (std::abs(u.z) < 1)
    return Vec3f(-1, 1, 1);

  return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}