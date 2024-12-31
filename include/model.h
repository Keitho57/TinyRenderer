#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"
#include "tgaimage.h"
#include <vector>

class Model {
private:
  std::vector<Vec3f> vertexs_;
  std::vector<std::vector<Vec3i>> triangles_;
  std::vector<Vec2f> uvCoords_;
  TGAImage diffusemap_;
  void loadTexture(std::string filename, const char *suffix, TGAImage &img);

public:
  Model(const char *filename);
  ~Model();
  int nVertexs();
  int nTriangles();
  Vec3f getVertex(int i);
  std::vector<int> getTriangle(int idx);
  Vec2f getUvCoords(int index, int vertex);
  TGAColor diffuse(Vec2i uv);
};

#endif //__MODEL_H__