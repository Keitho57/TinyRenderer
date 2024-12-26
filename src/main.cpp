#include "geometry.h"
#include "line.h"
#include "model.h"
#include "tgaimage.h"
#include "triangle.h"

#include <chrono>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

const char *objPath = "assets/african_head.obj";

Model *model = NULL;

const int width = 800;
const int height = 800;

int main(int argc, char **argv) {
  TGAImage image(width, height, TGAImage::RGB);

  // Vec2i P(400, 400);
  // Vec2i A(100, 100);
  // Vec2i B(400, 700);
  // Vec2i C(700, 101);

  // Triangle triangley(A, B, C);
  // drawTriangleOutline(triangley, image, blue);

  // float u = A.x * (C.y - A.y) + (P.y - A.y) * (C.x - A.x) - P.x * (C.y -
  // A.y); u /= (B.y - A.y) * (C.x - A.x) - (B.x - A.x) * (C.y - A.y);

  // float v = P.y - A.y - u * (B.y - A.y);
  // v /= C.y - A.y;

  // TGAColor pColor;

  // if (u >= 0.0 && v >= 0.0 && u + v <= 1.0) {
  //   pColor = green;
  // } else {
  //   pColor = red;
  // }
  // line(A, P, image, pColor);
  // line(B, P, image, pColor);
  // line(C, P, image, pColor);

  // TGAColor colors[3] = {red, green, blue};
  // for (int i = 0; i < width; i += 10) {
  //   Triangle trianglex(Vec2i(0 + i, 100), Vec2i(100 + i, 300),
  //                      Vec2i(200 + i, 200));
  //   drawTriangleFill(trianglex, image, colors[i % 3]);
  // }
  // i want to have the origin at the left bottom corner of the image

  model = new Model(objPath);

  for (int i = 0; i < model->nfaces(); i++) {
    std::vector<int> face = model->face(i);
    Vec2i screen_coords[3];
    for (int j = 0; j < 3; j++) {
      Vec3f world_coords = model->vert(face[j]);
      screen_coords[j] = Vec2i((world_coords.x + 1.) * width / 2.,
                               (world_coords.y + 1.) * height / 2.);
    }

    drawTriangleFill(screen_coords, image,
                     TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
