#ifndef __LINE_H__
#define __LINE_H__
#include "geometry.h"
#include "tgaimage.h"

void line(Vec2i a, Vec2i b, TGAColor color);
void line(int x0, int y0, int x1, int y1, TGAColor color);
void line(Vec2f a, Vec2f b, TGAColor color);

void lineSlow(int x0, int y0, int x1, int y1, TGAColor color);

#endif // __LINE_H__