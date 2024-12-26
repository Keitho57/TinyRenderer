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

  Triangle trianglex(Vec2i(100, 300), Vec2i(200, 500), Vec2i(500, 600));

  drawTriangleFill(trianglex, image, green);

  // i want to have the origin at the left bottom corner of the image
  image.flip_vertically();
  image.write_tga_file("output.tga");

  return 0;
}
