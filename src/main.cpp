#include "line.h"
#include "model.h"
#include "tgaimage.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

const char *objPath = "assets/african_head.obj";

Model *model = NULL;

const int width = 800;
const int height = 800;

int main(int argc, char **argv) {
  TGAImage image(width, height, TGAImage::RGB);

  model = new Model(objPath);
  for (int i = 0; i < model->nfaces(); i++) {
    std::vector<int> face = model->face(i);
    for (int j = 0; j < 3; j++) {
      Vec3f v0 = model->vert(face[j]);
      Vec3f v1 = model->vert(face[(j + 1) % 3]);

      int x0 = (v0.x + 1.) * width / 2.;
      int y0 = (v0.y + 1.) * height / 2.;
      int x1 = (v1.x + 1.) * width / 2.;
      int y1 = (v1.y + 1.) * height / 2.;

      lineFast(x0, y0, x1, y1, image, white);
    }
  }

  // i want to have the origin at the left bottom corner of the image
  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}