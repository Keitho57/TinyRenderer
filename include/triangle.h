#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "geometry.h"
#include "line.h"

template <class t> struct Triangle {
  t totalHeight;
  t bottomHeight;
  t topHeight;

  union {
    struct {
      Vec2<t> bottomPoint, midPoint, topPoint;
    };

    Vec2<t> points[3];
  };

  Triangle() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec2<t>();
    }
  }

  Triangle(Vec2<t> _points[3]) {
    setPoints(_points[0], _points[1], _points[2]);
  }

  Triangle(Vec2<t> point1, Vec2<t> point2, Vec2<t> point3) {
    setPoints(point1, point2, point3);
  }

private:
  void setPoints(Vec2<t> point1, Vec2<t> point2, Vec2<t> point3) {
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    sortPoints();
    setHeights();
  }

  void sortPoints() {
    // Point 0 ends up as bottom point, 1 is mid, 2 high
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

typedef Triangle<float> Trianglef;
typedef Triangle<int> Trianglei;

void drawTriangleOutline(Trianglei trianglePoints, TGAImage &image,
                         TGAColor color);

void drawTriangleFillScanline(Trianglei trianglePoints, TGAImage &image,
                              TGAColor color);

void drawTriangleFillBarycentricCoords(Vec3f ptsOfTriangle[3], float zBuffer[],
                                       TGAImage &image, TGAColor color);

#endif // __TRIANGLE_H__
