#include "geometry.h"

Vec2i lerp(Vec2i p1, Vec2i p2, int y, int scale) {
  // How far along the scale is y (-p1.y to make it relative to 0)
  float distanceAlongScale = (float)(y - p1.y) / scale;

  // p2 - p1 to get the distance between points,
  // * distanceAlongScale to see how far along line y is
  // +p1 to make it relative to p1 instead of 0
  return p1 + (p2 - p1) * distanceAlongScale;
}