#include "geometry.h"
#include "line.h"
#include "model.h"
#include "tgaimage.h"
#include "triangle.h"

#include <chrono>
#include <iostream>
#include <luminosity.h>
#include <rasterize.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

const char *objPath = "assets/african_head.obj";

Model *model = NULL;

const int width = 800;
const int height = 800;

int main(int argc, char **argv) {
  TGAImage scene(width, height, TGAImage::RGB);

  model = new Model(objPath);

  for (int i = 0; i < model->nfaces(); i++) {
    std::vector<int> face = model->face(i);
    Vec2i screen_coords[3];
    for (int j = 0; j < 3; j++) {
      Vec3f world_coords = model->vert(face[j]);
      screen_coords[j] = Vec2i((world_coords.x + 1.) * width / 2.,
                               (world_coords.y + 1.) * height / 2.);
    }
    drawTriangleFillBarycentricCoords(
        screen_coords, scene,
        TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
  }

  scene.flip_vertically();
  scene.write_tga_file("output.tga");

  return 0;
}
