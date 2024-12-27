#ifndef __RASTERIZE_H__
#define __RASTERIZE_H__

#include "geometry.h"
#include "tgaimage.h"

void rasterize(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color,
               int ybuffer[]);

#endif //__RASTERIZE_H__