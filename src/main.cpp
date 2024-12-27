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
  int ybuffer[width];
  for (int i = 0; i < width; i++) {
    ybuffer[i] = std::numeric_limits<int>::min();
  }

  // scene "2d mesh"
  rasterize(Vec2i(20, 34), Vec2i(744, 400), scene, red, ybuffer);
  rasterize(Vec2i(120, 434), Vec2i(444, 400), scene, green, ybuffer);
  rasterize(Vec2i(330, 463), Vec2i(594, 200), scene, blue, ybuffer);

  // screen line
  rasterize(Vec2i(10, 10), Vec2i(790, 10), scene, white, ybuffer);

  scene.flip_vertically();
  scene.write_tga_file("output.tga");

  return 0;
}
