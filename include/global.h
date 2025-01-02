#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "model.h"

// Declare the global object
extern Model *model;

extern TGAImage *image;

extern Vec3f *lightVector;
extern Vec3f *camera;

extern int width;
extern int height;
extern int depth;

#endif // __GLOBAL_H__
