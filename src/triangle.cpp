#include "triangle.h"
#include "geometry.h"
#include "line.h"
#include <iostream>

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

void drawTriangleOutline(Triangle triangle, TGAImage &image, TGAColor color) {
  Vec2i point1 = triangle.points[0];
  Vec2i point2 = triangle.points[1];
  Vec2i point3 = triangle.points[2];

  if (point1.y > point2.y)
    std::swap(point1, point2);
  if (point1.y > point3.y)
    std::swap(point1, point3);
  if (point2.y > point3.y)
    std::swap(point2, point3);

  // Point1 ends up as lowpoint, 2 is mid, 3 high
  // line(point1.x, point1.y, point2.x, point2.y, image, green);
  // line(point2.x, point2.y, point3.x, point3.y, image, green);
  // line(point3.x, point3.y, point1.x, point1.y, image, red);

  int total_height = point3.y - point1.y;
  int segment_height = point2.y - point1.y + 1;

  for (int y = point1.y; y <= point2.y; y++) {
    // Alpha and beta the same point along different scales
    // i.e. v dist from p1 to p3 = total height
    // and v dist from p1 to p2 = seg height
    float alpha = (float)(y - point1.y) / total_height;
    float beta = (float)(y - point1.y) / segment_height;

    // distance of line p1 to p3 * how far along they are according to scales
    // add p1 as point isnt starting from 0,0
    Vec2i A = point1 + (point3 - point1) * alpha;
    Vec2i B = point1 + (point2 - point1) * beta;
    image.set(A.x, y, red);
    image.set(B.x, y, green);
  }
};

void drawTriangleFill(Triangle triangle, TGAImage &image, TGAColor color) {
  drawTriangleOutline(triangle, image, color);
};

// for (int i = 0; i < image.get_height(); i++) {
//     std::vector<std::vector<std::vector<int>>> pointsOnBoundary;
//     std::vector<std::vector<int>> pointsOnRow;
//     for (int j = 0; j < image.get_width(); j++) {
//       TGAColor x = image.get(j, i);
//       if (x.val == 16711680) {
//         pointsOnRow.push_back({j, i});
//       }
//     }
//     pointsOnBoundary.push_back(pointsOnRow);
//   }

// void drawTriangleFill(Triangle triangle, TGAImage &image, TGAColor color) {
//   drawTriangleOutline(triangle, image, color);
//   int xMappepToY[image.get_height()];

//   for (int i = 0; i < image.get_height(); i++) {
//     std::vector<std::vector<int>> pointsOnRow;
//     for (int j = 0; j < image.get_width(); j++) {
//       TGAColor x = image.get(j, i);
//       if (x.val != 0) {
//         pointsOnRow.push_back({j, i});
//       }
//     }

//     if (pointsOnRow.size() % 2 != 0) {
//       pointsOnRow.push_back({pointsOnRow[0][0], pointsOnRow[0][1]});
//     }

//     if (pointsOnRow.size() > 0) {
//       for (int k = 0; k < pointsOnRow.size() - 1; k += 2) {
//         int x1 = pointsOnRow[k][0];
//         int y1 = pointsOnRow[k][1];
//         int x2 = pointsOnRow[k + 1][0];
//         int y2 = pointsOnRow[k + 1][1];
//         TGAColor color = colorsArray[i % 3];
//         line(x1, y1, x2, y2, image, color);
//       }
//     }
//   }
// };