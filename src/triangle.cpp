#include "triangle.h"
#include "geometry.h"
#include "lerp.h"
#include "line.h"
#include <iostream>

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);

void drawTriangleOutline(Triangle triangle, TGAImage &image, TGAColor color) {
  Vec2i point1 = triangle.points[0];
  Vec2i point2 = triangle.points[1];
  Vec2i point3 = triangle.points[2];

  // Point1 ends up as lowpoint, 2 is mid, 3 high
  if (point1.y > point2.y)
    std::swap(point1, point2);
  if (point1.y > point3.y)
    std::swap(point1, point3);
  if (point2.y > point3.y)
    std::swap(point2, point3);

  int vDistFromBottomToTop = point3.y - point1.y;
  int vDistFromBottomToMid = point2.y - point1.y + 1;

  for (int y = point1.y; y <= point2.y; y++) {
    Vec2i A = lerp(point1, point3, y, vDistFromBottomToTop);
    Vec2i B = lerp(point1, point2, y, vDistFromBottomToMid);

    line(A.x, y, B.x, y, image, white);

    image.set(A.x, y, blue);
    image.set(B.x, y, blue);
  }
};

void drawTriangleFill(Triangle triangle, TGAImage &image, TGAColor color) {
  drawTriangleOutline(triangle, image, color);
};
