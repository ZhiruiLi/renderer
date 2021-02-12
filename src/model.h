#pragma once

#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "tgaimage.h"
#include "vector.h"

namespace sren {

class Model {
 private:
  std::vector<Vector3> verts_;
  // attention, this Vector3 means vertex/uv/normal
  std::vector<std::vector<Vector3> > faces_;
  std::vector<Vector3> norms_;
  std::vector<Vector2> uv_;
  TGAImage diffusemap_;
  void load_texture(std::string filename, const char *suffix, TGAImage &img);

 public:
  Model(const char *filename);
  ~Model();
  int nverts() const;
  int nfaces() const;
  Vector3 vert(int i) const;
  Vector2 uv(int iface, int nvert) const;
  Color diffuse(Vector2 uv) const;
  std::vector<int> face(int idx) const;
};

}  // namespace sren
