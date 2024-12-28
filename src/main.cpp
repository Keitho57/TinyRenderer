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

  Triangle t(Vec2i(100, 100), Vec2i(400, 700), Vec2i(700, 100));
  Triangle t1(Vec2i(400, 110), Vec2i(550, 400), Vec2i(600, 150));
  drawTriangleFillBarycentricCoords(t, scene, red);
  drawTriangleFillBarycentricCoords(t1, scene, blue);

  scene.flip_vertically();
  scene.write_tga_file("output.tga");

  return 0;
}
