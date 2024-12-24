#ifndef LINE_H
#define LINE_H
#include "tgaimage.h"

void lineFast(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

#endif // LINE_H