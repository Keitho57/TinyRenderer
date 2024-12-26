#include "triangle.h"
#include "geometry.h"
#include "lerp.h"
#include "line.h"
#include <iostream>

void drawTriangleOutline(Triangle triangle, TGAImage &image, TGAColor color) {
  Vec2i bottomPoint = triangle.bottomPoint;
  Vec2i midPoint = triangle.midPoint;
  Vec2i topPoint = triangle.topPoint;

  line(bottomPoint, midPoint, image, color);
  line(midPoint, topPoint, image, color);
  line(topPoint, bottomPoint, image, color);
};

// Using scanline algo
void drawTriangleFill(Triangle triangle, TGAImage &image, TGAColor color) {
  Vec2i bottomPoint = triangle.bottomPoint;
  Vec2i midPoint = triangle.midPoint;
  Vec2i topPoint = triangle.topPoint;

  if (bottomPoint.y == midPoint.y && bottomPoint.y == topPoint.y)
    return;

  int totalHeight = triangle.totalHeight;
  int bottomHeight = triangle.bottomHeight;

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
