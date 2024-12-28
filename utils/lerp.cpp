#include "geometry.h"
#include "triangle.h"

Vec2i lerp(Vec2i p1, Vec2i p2, int y) {
  int scale = p2.y - p1.y;

  // How far along the scale is y
  float distanceAlongScale = (float)(y) / scale;

  // [Sidenote] this is == (1 - distanceAlongScale)*P1 + distanceAlongScale*P2
  return p1 + (p2 - p1) * distanceAlongScale;
}
