#include "triangle.h"
#include "barycentric.h"
#include "geometry.h"
#include "lerp.h"
#include "line.h"
#include <iostream>

void drawTriangleOutline(Triangle2di triangle, TGAImage &image,
                         TGAColor color) {
  Vec2i bottomPoint = triangle.bottomPoint;
  Vec2i midPoint = triangle.midPoint;
  Vec2i topPoint = triangle.topPoint;

  line(bottomPoint, midPoint, image, color);
  line(midPoint, topPoint, image, color);
  line(topPoint, bottomPoint, image, color);
};

// Using scanline algo
void drawTriangleFillScanline(Triangle2di triangle, TGAImage &image,
                              TGAColor color) {
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
}

// From that vid: to get m subtract x component of e1 from e1
// to get the x component you say e1 dot e2 but since e2 isnt a unit vector
// make it a unit vector by e2/length of e2,
// since there would be 2 e2s in the calc its e2 norm squared
// i.e e1 - ((e1 dot e2) * e2/(length of e2 squared))

// Using barycentric coords algo
void drawTriangleFillBarycentricCoords(Triangle3df triangle, float *zBuffer,
                                       TGAImage &image, TGAColor color) {
  Vec2f boundingBoxMin(image.get_width() - 1, image.get_height() - 1);
  Vec2f boundingBoxMax(0, 0);
  Vec2f clamp(image.get_width() - 1, image.get_height() - 1);

  // get max x, y coords to draw bounding box
  for (int i = 0; i < 3; i++) {
    boundingBoxMin.x =
        std::max(0.f, std::min(boundingBoxMin.x, triangle.points[i].x));
    boundingBoxMin.y =
        std::max(0.f, std::min(boundingBoxMin.y, triangle.points[i].y));

    boundingBoxMax.x =
        std::min(clamp.x, std::max(boundingBoxMax.x, triangle.points[i].x));
    boundingBoxMax.y =
        std::min(clamp.y, std::max(boundingBoxMax.y, triangle.points[i].y));
  }

  Vec3f P;
  for (P.x = boundingBoxMin.x; P.x <= boundingBoxMax.x; P.x++) {
    for (P.y = boundingBoxMin.y; P.y <= boundingBoxMax.y; P.y++) {
      Vec3f barycentricCoords = getBarycentricCoords(
          triangle.points[0], triangle.points[1], triangle.points[2], P);

      // if point is outside triangle, skip
      if (barycentricCoords.x < 0 || barycentricCoords.y < 0 ||
          barycentricCoords.z < 0)
        continue;

      P.z = 0;
      for (int i = 0; i < 3; i++)
        P.z += triangle.points[i].z *
               barycentricCoords.raw[i]; // interpolate depth

      if (zBuffer[int(P.x + P.y * image.get_width())] < P.z) {
        zBuffer[int(P.x + P.y * image.get_width())] = P.z;
        image.set(P.x, P.y, color);
      }
    }
  }
}
