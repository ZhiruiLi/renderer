#pragma once

#include <string_view>
#include <vector>

#include "vector.h"

namespace sren {

class Model {
 private:
  std::vector<Vector3> verts_;
  std::vector<std::vector<int> > faces_;

 public:
  Model(std::string_view filename);
  ~Model() = default;

  int nverts() const;
  int nfaces() const;

  Vector3 const &vert(int i) const;
  Vector3 &vert(int i);
  std::vector<int> const &face(int i) const;
  std::vector<int> &face(int i);
};

}  // namespace sren
