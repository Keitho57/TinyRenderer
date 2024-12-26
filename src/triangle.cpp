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
  Vec2i bottomPoint = triangle.bottomPoint;
  Vec2i midPoint = triangle.midPoint;
  Vec2i topPoint = triangle.topPoint;

  line(bottomPoint, midPoint, image, purple);
  line(midPoint, topPoint, image, purple);
  line(topPoint, bottomPoint, image, purple);
};

void drawTriangleFill(Triangle triangle, TGAImage &image, TGAColor color) {
  Vec2i bottomPoint = triangle.bottomPoint;
  Vec2i midPoint = triangle.midPoint;
  Vec2i topPoint = triangle.topPoint;

  int totalHeight = triangle.totalHeight;
  int bottomHeight = triangle.bottomHeight + 1;
  int topHeight = triangle.topHeight + 1;

  for (int y = 0; y < totalHeight; y++) {
    int isBottomHalf = y < bottomHeight;

    Vec2i A = lerp(bottomPoint, topPoint, y);
    Vec2i B = isBottomHalf ? lerp(bottomPoint, midPoint, y)
                           : lerp(midPoint, topPoint, y - bottomHeight);

    if (A.x > B.x)
      std::swap(A, B);

    line(A.x, y + bottomPoint.y, B.x, y + bottomPoint.y, image, color);
  }
};
