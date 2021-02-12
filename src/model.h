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
  std::vector<Vector3> verts_;  // array of vertices
  std::vector<Vector2> uv_;     // array of tex coords
  std::vector<Vector3> norms_;  // array of normal vectors
  std::vector<int> facet_vrt_;
  std::vector<int> facet_tex_;  // indices in the above arrays per triangle
  std::vector<int> facet_nrm_;
  TGAImage diffusemap_;   // diffuse color texture
  TGAImage normalmap_;    // normal map texture
  TGAImage specularmap_;  // specular map texture
  void load_texture(const std::string filename, const std::string suffix,
                    TGAImage &img);

 public:
  Model(const std::string filename);
  int nverts() const;
  int nfaces() const;
  // per triangle corner normal vertex
  Vector3 normal(const int iface, const int nthvert) const;
  // fetch the normal vector from the normal map texture
  Vector3 normal(const Vector2 &uv) const;
  Vector3 vert(const int i) const;
  Vector3 vert(const int iface, const int nthvert) const;
  Vector2 uv(const int iface, const int nthvert) const;
  Color diffuse(const Vector2 &uv) const;
  double specular(const Vector2 &uv) const;
};

}  // namespace sren
