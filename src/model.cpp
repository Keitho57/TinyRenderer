#include "model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Model::Model(const char *filename) : verts_(), faces_(), uv_() {
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
      verts_.push_back(v);
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vec2f uvCoords;
      for (int i = 0; i < 2; i++)
        iss >> uvCoords[i];
      uv_.push_back(uvCoords);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<Vec3i> f;
      Vec3i tmp;
      iss >> trash;
      while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
        for (int i = 0; i < 3; i++)
          tmp[i]--; // in wavefront obj all indices start at 1, not zero
        f.push_back(tmp);
      }
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << " uv# "
            << uv_.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() { return (int)verts_.size(); }

int Model::nfaces() { return (int)faces_.size(); }

std::vector<int> Model::face(int idx) {
  std::vector<int> face;
  for (int i = 0; i < (int)faces_[idx].size(); i++)
    face.push_back(faces_[idx][i].raw[0]);
  return face;
}

Vec2f Model::getUvCoords(int index, int vertex) {
  int uvIndex = faces_[index][vertex].raw[1];
  Vec2f uvCoords = uv_[uvIndex];
  return uvCoords;
}

Vec3f Model::vert(int i) { return verts_[i]; }