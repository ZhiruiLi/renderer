#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "color.h"
#include "data2d.h"
#include "vector.h"

namespace sren {

struct FaceDataIndex {
  FaceDataIndex() = default;
  FaceDataIndex(int v, int u, int n) : vertex(v), uv(u), normal(n) {}

  int vertex{};
  int uv{};
  int normal{};
};

class Model {
 public:
  Model() = default;

  int nverts() const;
  int nfaces() const;

  Vector3 vertex(int iface, int nthvert) const;
  Vector2 uv(int iface, int nthvert) const;
  Vector3 normal(int iface, int nthvert) const;

  FaceDataIndex const &face_index(int iface, int nthvert) const;
  std::array<int, 3> vertex_indexs(int iface) const;
  std::array<int, 3> uv_indexs(int iface) const;
  std::array<int, 3> normal_indexs(int iface) const;

  std::vector<Vector3> &vertexs() { return vertexs_; }
  std::vector<Vector3> const &vertexs() const { return vertexs_; }
  std::vector<Vector2> &uvs() { return uvs_; }
  std::vector<Vector2> const &uvs() const { return uvs_; }
  std::vector<Vector3> &normals() { return normals_; }
  std::vector<Vector3> const &normals() const { return normals_; }
  std::vector<Color> &colors() { return colors_; }
  std::vector<Color> const &colors() const { return colors_; }
  std::vector<FaceDataIndex> &face_indexs() { return face_indexs_; }
  std::vector<FaceDataIndex> const &face_indexs() const { return face_indexs_; }

 private:
  std::vector<Vector3> vertexs_{};
  std::vector<Vector2> uvs_{};
  std::vector<Vector3> normals_{};
  std::vector<Color> colors_{};

  std::vector<FaceDataIndex> face_indexs_{};
};

}  // namespace sren
