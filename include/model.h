#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"
#include <vector>

class Model {
private:
  std::vector<Vec3f> verts_;
  std::vector<std::vector<Vec3i>> faces_;
  std::vector<Vec2f> uv_;

public:
  Model(const char *filename);
  ~Model();
  int nverts();
  int nfaces();
  Vec3f vert(int i);
  std::vector<int> face(int idx);
  Vec2f getUvCoords(int index, int vertex);
};

#endif //__MODEL_H__