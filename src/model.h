#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tgaimage.h"
#include "vector.h"

namespace sren {

class Model {
 private:
  std::vector<Vector3> vertexs_{};  // array of vertices
  std::vector<Color> colors_{};     // array of colors
  std::vector<Vector2> uvs_{};      // array of tex coords
  std::vector<Vector3> normals_{};  // array of normal vectors

  // indices in the above arrays per triangle
  std::vector<int> facet_vrt_{};
  std::vector<int> facet_tex_{};
  std::vector<int> facet_nrm_{};

  TGAImage diffusemap_{};   // diffuse color texture
  TGAImage normalmap_{};    // normal map texture
  TGAImage specularmap_{};  // specular map texture

  void LoadData(std::string const &filename);
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
  Vector3 Vertex(int iface, int nthvert) const;
  Vector2 UV(int iface, int nthvert) const;
  Color Diffuse(Vector2 const &uv) const;
  double Specular(Vector2 const &uv) const;

  std::array<int, 3> VertexIndexs(int iface) const;
  int VertexIndex(int iface, int nthvert) const;
  std::array<int, 3> VertexUVIndexs(int iface) const;
  int VertexUVIndex(int iface, int nthvert) const;
  std::array<int, 3> VertexNormalIndexs(int iface) const;
  int VertexNormalIndex(int iface, int nthvert) const;

  std::vector<Vector3> &vertexs() { return vertexs_; }
  std::vector<Vector3> const &vertexs() const { return vertexs_; }
  std::vector<Color> &colors() { return colors_; }
  std::vector<Color> const &colors() const { return colors_; }
  std::vector<Vector2> &uvs() { return uvs_; }
  std::vector<Vector2> const &uvs() const { return uvs_; }
  std::vector<Vector3> &normals() { return normals_; }
  std::vector<Vector3> const &normals() const { return normals_; }

  TGAImage &diffuse_map() { return diffusemap_; };
  TGAImage const &diffuse_map() const { return diffusemap_; };
  TGAImage &normal_map() { return normalmap_; };
  TGAImage const &normal_map() const { return normalmap_; };
  TGAImage &specular_map() { return specularmap_; };
  TGAImage const &specular_map() const { return specularmap_; };
};

}  // namespace sren
