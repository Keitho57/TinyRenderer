#include "model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Model::Model(const char *filename) : vertexs_(), triangles_(), uvCoords_() {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail())
    return;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash; // Trash "v "
      Vec3f v;
      for (int i = 0; i < 3; i++)
        iss >> v.raw[i];
      vertexs_.push_back(v);
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vec2f uvCoords;
      for (int i = 0; i < 2; i++)
        iss >> uvCoords[i];
      uvCoords_.push_back(uvCoords);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<Vec3i> f;
      Vec3i tmp;
      iss >> trash;
      while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
        for (int i = 0; i < 3; i++)
          tmp[i]--; // in wavefront obj all indices start at 1, not zero
        f.push_back(tmp);
      }
      triangles_.push_back(f);
    }
  }
  std::cerr << "# v# " << vertexs_.size() << " f# " << triangles_.size()
            << " uv# " << uvCoords_.size() << std::endl;
}

Model::~Model() {}

int Model::nVertexs() { return (int)vertexs_.size(); }

int Model::nTriangles() { return (int)triangles_.size(); }

std::vector<int> Model::getTriangle(int i) {
  std::vector<int> face;
  for (int j = 0; j < (int)triangles_[i].size(); j++)
    face.push_back(triangles_[i][j][0]);
  return face;
}

Vec2f Model::getUvCoords(int index, int vertex) {
  int uvIndex = triangles_[index][vertex][1];
  Vec2f uvCoords = uvCoords_[uvIndex];
  return uvCoords;
}

Vec3f Model::getVertex(int i) { return vertexs_[i]; }