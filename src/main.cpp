#include "geometry.h"
#include "global.h"
#include "line.h"
#include "luminosity.h"
#include "model.h"
#include "rasterize.h"
#include "tgaimage.h"
#include "triangle.h"

#include <chrono>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

const char *objPath = "assets/african_head.obj";

const int width = 800;
const int height = 800;

Vec3f lightVector(0, 0, -1);

TGAImage *image = nullptr;
Model *model = nullptr;

// convert x and y to screen width, height(same depth)
Vec3f mapWorld2screen(Vec3f v) {
  return Vec3f(int((v.x + 1.) * width / 2. + .5),
               int((v.y + 1.) * height / 2. + .5), v.z);
}

int main(int argc, char **argv) {
  image = new TGAImage(width, height, TGAImage::RGB);
  model = new Model(objPath);

  // "Depth"
  float *zBuffer = new float[width * height];
  for (int i = 0; i < width * height; i++) {
    zBuffer[i] = -std::numeric_limits<float>::max();
  }

  for (int i = 0; i < model->nTriangles(); i++) {
    std::vector<int> triangleData = model->getTriangle(i);

    Vec3f ptsOfTriangle[3];
    Vec2f uvPointsOfTriangle[3];
    Vec3f worldCoords[3];

    for (int j = 0; j < 3; j++) {
      ptsOfTriangle[j] = mapWorld2screen(model->getVertex(triangleData[j]));
      uvPointsOfTriangle[j] = model->getUvCoords(i, j);
      worldCoords[j] = model->getVertex(triangleData[j]);
    }
    Trianglef t(ptsOfTriangle, uvPointsOfTriangle);

    float intensity = calculateLuminosity(worldCoords, lightVector);
    if (intensity > 0) {
      drawTriangleFillScanline(t, zBuffer, intensity);
    }
  }

  image->flip_vertically(); // Bottom left origin
  image->write_tga_file("output.tga");
  delete model;

  return 0;
}
