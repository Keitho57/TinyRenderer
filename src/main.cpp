#include "line.h"
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

int main(int argc, char **argv) {
  TGAImage image(100, 100, TGAImage::RGB);

  lineFast(13, 20, 80, 40, image, white);
  lineFast(20, 13, 40, 80, image, red);
  lineFast(80, 40, 13, 20, image, red);

  // i want to have the origin at the left bottom  corner of the image
  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}