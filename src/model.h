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
  void LoadTexture(std::string const &filename, std::string const &suffix,
                   TGAImage &img);

 public:
  Model(std::string const &filename);
  int nverts() const;
  int nfaces() const;
  // per triangle corner normal vertex
  Vector3 VertexNormal(int iface, int nthvert) const;
  // fetch the normal vector from the normal map texture
  Vector3 TextureNormal(Vector2 const &uv) const;
  int VertIndex(int iface, int nthvert) const;
  Vector3 Vert(int iface, int nthvert) const;
  Vector2 UV(int iface, int nthvert) const;
  Color Diffuse(Vector2 const &uv) const;
  double Specular(Vector2 const &uv) const;

  std::vector<Vector3> &verts() { return verts_; }
  std::vector<Vector3> const &verts() const { return verts_; }
  std::vector<Vector2> &uvs() { return uv_; }
  std::vector<Vector2> const &uvs() const { return uv_; }
};

}  // namespace sren
