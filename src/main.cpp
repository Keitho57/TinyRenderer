#include "geometry.h"
#include "global.h"
#include "line.h"
#include "luminosity.h"
#include "matrix.h"
#include "model.h"
#include "perspective.h"
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

int width;
int height;
int depth;

Vec3f *lightVector = nullptr;
Vec3f *camera = nullptr;
TGAImage *image = nullptr;
Model *model = nullptr;

int main(int argc, char **argv) {
  width = 800;
  height = 800;
  depth = 100;

  image = new TGAImage(width, height, TGAImage::RGB);
  model = new Model(objPath);
  lightVector = new Vec3f(0, 0, -1);
  camera = new Vec3f(0, 0, 3);

  // "Depth"
  float *zBuffer = new float[width * height];
  for (int i = 0; i < width * height; i++) {
    zBuffer[i] = -std::numeric_limits<float>::max();
  }

  for (int i = 0; i < model->nTriangles(); i++) {
    std::vector<int> triangleData = model->getTriangle(i);

    Vec2f uvPointsOfTriangle[3];
    Vec3f worldCoords[3];
    Vec3i screenCoords[3];

    for (int j = 0; j < 3; j++) {
      uvPointsOfTriangle[j] = model->getUvCoords(i, j);
      worldCoords[j] = model->getVertex(triangleData[j]);
      Vec3f v = convertPointToPerspective(model->getVertex(triangleData[j]));
      screenCoords[j] = v;
    }

    float luminosity = calculateLuminosity(worldCoords);
    if (luminosity > 0) {
      drawTriangleFillScanline(Trianglei(screenCoords, uvPointsOfTriangle),
                               zBuffer, luminosity);
    }
  }

  image->flip_vertically(); // Bottom left origin
  image->write_tga_file("output.tga");
  delete model;

  return 0;
}
