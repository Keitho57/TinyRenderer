#include <geometry.h>
#include <tgaimage.h>

// map some point to a pixel on screen
void rasterize(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color,
               int ybuffer[]) {
  if (p0.x > p1.x) {
    std::swap(p0, p1);
  }

  // find y for a given x
  for (int x = p0.x; x <= p1.x; x++) {
    float t = (x - p0.x) / (float)(p1.x - p0.x);
    int y = p0.y * (1. - t) + p1.y * t; // lerping regrouped
    if (ybuffer[x] < y) {
      ybuffer[x] = y; // "at x the height is y"
      image.set(x, 0, color);
    }
  }
}
