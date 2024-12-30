#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"
#include <vector>

class Model {
private:
  std::vector<Vec3f> vertexs_;
  std::vector<std::vector<Vec3i>> triangles_;
  std::vector<Vec2f> uvCoords_;

public:
  Model(const char *filename);
  ~Model();
  int nVertexs();
  int nTriangles();
  Vec3f getVertex(int i);
  std::vector<int> getTriangle(int idx);
  Vec2f getUvCoords(int index, int vertex);
};

#endif //__MODEL_H__