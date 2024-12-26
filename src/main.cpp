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

  model = new Model(objPath);

  Vec3f light_dir(0, 0, -1);

  for (int i = 0; i < model->nfaces(); i++) {
    std::vector<int> face = model->face(i);
    Vec2i screen_coords[3];
    Vec3f world_coords[3];
    for (int j = 0; j < 3; j++) {
      Vec3f v = model->vert(face[j]);
      screen_coords[j] =
          Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
      world_coords[j] = v;
    }
    Vec3f n = (world_coords[2] - world_coords[0]) ^
              (world_coords[1] - world_coords[0]);

    n.normalize();
    float intensity = n * light_dir;
    if (intensity > 0)
      drawTriangleFill(
          screen_coords, image,
          TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
  }

  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
