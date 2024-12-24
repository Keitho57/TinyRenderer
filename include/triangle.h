#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "geometry.h"
#include "line.h"

struct Triangle {
  Vec2i points[3];

  Triangle() {
    for (int i = 0; i < 3; ++i) {
      points[i] = Vec2i();
    }
  }

  Triangle(Vec2i _points[3]) {
    for (int i = 0; i < 3; ++i) {
      points[i] = _points[i];
    }
  }
};

void drawTriangleOutline(Triangle trianglePoints, TGAImage &image,
                         TGAColor color);

void drawTriangleFill(Triangle trianglePoints, TGAImage &image, TGAColor color);

#endif // __TRIANGLE_H__
