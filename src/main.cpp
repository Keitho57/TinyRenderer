#include "geometry.h"
#include "line.h"
#include "model.h"
#include "tgaimage.h"
#include "triangle.h"

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
  TGAColor colorsArray[3] = {red, green, blue};

  Vec2i triangle[3] = {Vec2i(100, 300), Vec2i(200, 500), Vec2i(500, 600)};
  Vec2i triangle2[3] = {Vec2i(500, 200), Vec2i(600, 500), Vec2i(700, 400)};

  drawTriangleFill(triangle, image, blue);
  drawTriangleFill(triangle2, image, red);

  // i want to have the origin at the left bottom corner of the image
  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}

// model = new Model(objPath);
// for (int i = 0; i < model->nfaces(); i++) {
//   std::vector<int> face = model->face(i);
//   for (int j = 0; j < 3; j++) {
//     Vec3f v0 = model->vert(face[j]);
//     Vec3f v1 = model->vert(face[(j + 1) % 3]);

//     int x0 = (v0.x + 1.) * width / 2.;
//     int y0 = (v0.y + 1.) * height / 2.;
//     int x1 = (v1.x + 1.) * width / 2.;
//     int y1 = (v1.y + 1.) * height / 2.;

//     line(x0, y0, x1, y1, image, white);
//   }
// }