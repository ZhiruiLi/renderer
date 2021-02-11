#pragma once

#include <vector>

#include "vector.h"

namespace sren {

class Model {
 private:
  std::vector<Vector3> verts_;
  std::vector<std::vector<int> > faces_;

 public:
  Model(const char *filename);
  ~Model();
  int nverts();
  int nfaces();
  Vector3 vert(int i);
  std::vector<int> face(int idx);
};

}  // namespace sren
