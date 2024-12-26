#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "geometry.h"
#include "line.h"

struct Triangle {
  int totalHeight;
  int bottomHeight;
  int topHeight;

  int normal;
  union {
    struct {
      Vec2i bottomPoint, midPoint, topPoint;
    };

    Vec2i points[3];
  };

  Triangle() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec2i();
    }
  }

  Triangle(Vec2i _points[3]) { setPoints(_points[0], _points[1], _points[2]); }

  Triangle(Vec2i point1, Vec2i point2, Vec2i point3) {
    setPoints(point1, point2, point3);
  }

private:
  // Helper function to set points and compute heights
  void setPoints(Vec2i point1, Vec2i point2, Vec2i point3) {
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;

    // Point 0 ends up as bottom point, 1 is mid, 2 high
    sortPoints();

    setHeights();
  }

  void sortPoints() {
    if (bottomPoint.y > midPoint.y)
      std::swap(bottomPoint, midPoint);
    if (bottomPoint.y > topPoint.y)
      std::swap(bottomPoint, topPoint);
    if (midPoint.y > topPoint.y)
      std::swap(midPoint, topPoint);
  }

  void setHeights() {
    totalHeight = points[2].y - points[0].y;
    bottomHeight = points[1].y - points[0].y;
    topHeight = points[2].y - points[1].y;
  }
};

void drawTriangleOutline(Triangle trianglePoints, TGAImage &image,
                         TGAColor color);

void drawTriangleFill(Triangle trianglePoints, TGAImage &image, TGAColor color);

#endif // __TRIANGLE_H__
