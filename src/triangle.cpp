#include "triangle.h"
#include "barycentric.h"
#include "geometry.h"
#include "global.h"
#include "line.h"
#include "model.h"

#include <iostream>

void drawTriangleOutline(Trianglef triangle, TGAColor color) {
  if (triangle[0].y == triangle[1].y && triangle[0].y == triangle[2].y)
    return; // i dont care about degenerate triangles

  if (triangle[0].y > triangle[1].y) {
    std::swap(triangle[0], triangle[1]);
  }
  if (triangle[0].y > triangle[2].y) {
    std::swap(triangle[0], triangle[2]);
  }
  if (triangle[1].y > triangle[2].y) {
    std::swap(triangle[1], triangle[2]);
  }

  Vec2i bottomPoint = Vec2i(triangle[0].x, triangle[0].y);
  Vec2i midPoint = Vec2i(triangle[1].x, triangle[1].y);
  Vec2i topPoint = Vec2i(triangle[2].x, triangle[2].y);

  line(bottomPoint, midPoint, color);
  line(midPoint, topPoint, color);
  line(topPoint, bottomPoint, color);
};

// Using scanline algo
void drawTriangleFillScanline(Trianglei triangle, float *zBuffer,
                              float luminosity) {
  Vec2f *uvCoords = triangle.uvCoords;

  if (triangle[0].y == triangle[1].y && triangle[0].y == triangle[2].y)
    return; // i dont care about degenerate triangles

  if (triangle[0].y > triangle[1].y) {
    std::swap(triangle[0], triangle[1]);
    std::swap(uvCoords[0], uvCoords[1]);
  }
  if (triangle[0].y > triangle[2].y) {
    std::swap(triangle[0], triangle[2]);
    std::swap(uvCoords[0], uvCoords[2]);
  }
  if (triangle[1].y > triangle[2].y) {
    std::swap(triangle[1], triangle[2]);
    std::swap(uvCoords[1], uvCoords[2]);
  }

  int totalHeight = triangle[2].y - triangle[0].y;
  int bottomHeight = triangle[1].y - triangle[0].y;
  int topHeight = triangle[2].y - triangle[1].y;

  Vec3f bottomPoint = triangle[0];
  Vec3f midPoint = triangle[1];
  Vec3f topPoint = triangle[2];

  for (int y = 0; y < totalHeight; y++) {
    int isBottomHalf = y < bottomHeight;
    int segmentHeight = isBottomHalf ? bottomHeight : topHeight;

    float distanceAlongTotalHeight = (float)y / (topPoint.y - bottomPoint.y);
    float distanceAlongSegmentHeight =
        (float)(isBottomHalf ? y : y - bottomHeight) / segmentHeight;

    // point along total height line
    Vec3f A = bottomPoint + (topPoint - bottomPoint) * distanceAlongTotalHeight;

    // point along segment height line
    Vec3f B = isBottomHalf ? bottomPoint + (midPoint - bottomPoint) *
                                               distanceAlongSegmentHeight
                           : midPoint + (topPoint - midPoint) *
                                            distanceAlongSegmentHeight;

    Vec2f uvA =
        uvCoords[0] + (uvCoords[2] - uvCoords[0]) * distanceAlongTotalHeight;

    Vec2f uvB = isBottomHalf ? uvCoords[0] + (uvCoords[1] - uvCoords[0]) *
                                                 distanceAlongSegmentHeight
                             : uvCoords[1] + (uvCoords[2] - uvCoords[1]) *
                                                 distanceAlongSegmentHeight;

    if (A.x > B.x) {
      std::swap(A, B);
      std::swap(uvA, uvB);
    }

    for (int x = A.x; x <= B.x; x++) {
      float distanceAlongAtoB =
          B.x == A.x ? 1. : (float)(x - A.x) / (B.x - A.x);

      Vec3f C = A + (B - A) * distanceAlongAtoB;
      Vec2f uvC = uvA + (uvB - uvA) * distanceAlongAtoB;

      int idx = C.x + (C.y * image->get_width());

      if (zBuffer[idx] < C.z) {
        zBuffer[idx] = C.z;
        TGAColor color = model->diffuse(uvC);
        image->set(C.x, C.y,
                   TGAColor(color.r * luminosity, color.g * luminosity,
                            color.b * luminosity));
      }
    }
  }
}

// Using barycentric coords algo
void drawTriangleFillBarycentricCoords(Trianglef triangle, float *zBuffer,
                                       TGAColor color) {
  Vec2f boundingBoxMin(image->get_width() - 1, image->get_height() - 1);
  Vec2f boundingBoxMax(0, 0);
  Vec2f clamp(image->get_width() - 1, image->get_height() - 1);

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
      Vec3f barycentricCoords = getBarycentricCoords(triangle, P);

      // if point is outside triangle, skip
      if (barycentricCoords.x < 0 || barycentricCoords.y < 0 ||
          barycentricCoords.z < 0)
        continue;

      P.z = 0;
      for (int i = 0; i < 3; i++)
        P.z += triangle[i].z * barycentricCoords[i]; // interpolate depth

      if (zBuffer[int(P.x + P.y * image->get_width())] < P.z) {
        zBuffer[int(P.x + P.y * image->get_width())] = P.z;
        image->set(P.x, P.y, color);
      }
    }
  }
}
