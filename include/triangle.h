#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "geometry.h"
#include "line.h"

template <class t> struct Triangle2d {
  t totalHeight;
  t bottomHeight;
  t topHeight;

  union {
    struct {
      Vec2<t> bottomPoint, midPoint, topPoint;
    };

    Vec2<t> points[3];
  };

  Triangle2d() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec2<t>();
    }
  }

  Triangle2d(Vec2<t> _points[3]) {
    setPoints(_points[0], _points[1], _points[2]);
  }

  Triangle2d(Vec2<t> point1, Vec2<t> point2, Vec2<t> point3) {
    setPoints(point1, point2, point3);
  }

  Triangle2d(Vec3<t> triangle3d[3]) {
    Vec2<t> p1(triangle3d[0].x, triangle3d[0].y);
    Vec2<t> p2(triangle3d[1].x, triangle3d[1].y);
    Vec2<t> p3(triangle3d[2].x, triangle3d[2].y);

    setPoints(p1, p2, p3);
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

typedef Triangle2d<float> Triangle2df;
typedef Triangle2d<int> Triangle2di;

template <class t> struct Triangle3d {
  union {
    struct {
      Vec3<t> p1, p2, p3;
    };

    Vec3<t> points[3];
  };

  Triangle3d() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec3<t>();
    }
  }

  Triangle3d(Vec3<t> _points[3]) {
    setPoints(_points[0], _points[1], _points[2]);
  }

  Triangle3d(Vec3<t> point1, Vec3<t> point2, Vec3<t> point3) {
    setPoints(point1, point2, point3);
  }

private:
  void setPoints(Vec3<t> point1, Vec3<t> point2, Vec3<t> point3) {
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
  }
};

typedef Triangle3d<float> Triangle3df;
typedef Triangle3d<int> Triangle3di;

void drawTriangleOutline(Triangle2di trianglePoints, TGAImage &image,
                         TGAColor color);

void drawTriangleFillScanline(Triangle2di trianglePoints, TGAImage &image,
                              TGAColor color);

void drawTriangleFillBarycentricCoords(Triangle3df triangle, float *zBuffer,
                                       TGAImage &image, TGAColor color);

#endif // __TRIANGLE_H__
