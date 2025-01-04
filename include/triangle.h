#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "geometry.h"
#include "line.h"
#include "model.h"

template <class t> struct Triangle {
  Vec2f uvCoords[3];
  Vec3f vertexNormals[3];
  Vec3<t> points[3];

  Triangle() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec3<t>();
      uvCoords[i] = Vec2f();
      vertexNormals[i] = Vec3f();
    }
  }

  Triangle(Vec3<t> _points[3], Vec2f _uvCoords[3], Vec3f _vertexNormals[3]) {
    setPoints(_points[0], _points[1], _points[2]);
    setCoords(_uvCoords[0], _uvCoords[1], _uvCoords[2]);
    setNormals(_vertexNormals[0], _vertexNormals[1], _vertexNormals[2]);
  }

  Vec3<t> &operator[](const int i) {
    if (i <= 0)
      return points[0];
    else if (i == 1)
      return points[1];
    else
      return points[2];
  }

private:
  void setPoints(Vec3<t> point1, Vec3<t> point2, Vec3<t> point3) {
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
  }

  void setCoords(Vec2f uvCoord1, Vec2f uvCoord2, Vec2f uvCoord3) {
    uvCoords[0] = uvCoord1;
    uvCoords[1] = uvCoord2;
    uvCoords[2] = uvCoord3;
  }

  void setNormals(Vec3f vertexNormal1, Vec3f vertexNormal2,
                  Vec3f vertexNormal3) {
    vertexNormals[0] = vertexNormal1;
    vertexNormals[1] = vertexNormal2;
    vertexNormals[2] = vertexNormal3;
  }
};

typedef Triangle<float> Trianglef;
typedef Triangle<int> Trianglei;

void drawTriangleOutline(Trianglef trianglePoints, TGAColor color);

void drawTriangleFillScanline(Trianglei triangle, float *zBuffer,
                              float luminosity);

void drawTriangleFillBarycentricCoords(Trianglef triangle, float *zBuffer,
                                       TGAColor color);

#endif // __TRIANGLE_H__
