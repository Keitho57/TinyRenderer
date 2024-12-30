#ifndef __BARYCENTRIC_H__
#define __BARYCENTRIC_H__

#include "geometry.h"
#include "triangle.h"

Vec3f getBarycentricCoords(Vec2i *pts, Vec2i P);

Vec3f getBarycentricCoords(Vec3f A, Vec3f B, Vec3f C, Vec3f P);

Vec3f getBarycentricCoords(Trianglef t, Vec3f P);

#endif //__BARYCENTRIC_H__