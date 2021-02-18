#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sren {

int Model::nverts() const { return vertexs_.size(); }
int Model::nfaces() const { return face_indexs_.size() / 3; }

std::array<int, 3> Model::vertex_indexs(int iface) const {
  return {
      face_index(iface, 0).vertex,
      face_index(iface, 1).vertex,
      face_index(iface, 2).vertex,
  };
}

std::array<int, 3> Model::uv_indexs(int iface) const {
  return {
      face_index(iface, 0).uv,
      face_index(iface, 1).uv,
      face_index(iface, 2).uv,
  };
}

std::array<int, 3> Model::normal_indexs(int iface) const {
  return {
      face_index(iface, 0).normal,
      face_index(iface, 1).normal,
      face_index(iface, 2).normal,
  };
}

FaceDataIndex const &Model::face_index(int iface, int nthvert) const {
  return face_indexs_[iface * 3 + nthvert];
}

Vector3 Model::vertex(int iface, int nthvert) const {
  return vertexs_[face_index(iface, nthvert).vertex];
}

Vector2 Model::uv(int iface, int nthvert) const {
  return uvs_[face_index(iface, nthvert).uv];
}

Vector3 Model::normal(int iface, int nthvert) const {
  return normals_[face_index(iface, nthvert).normal];
}

}  // namespace sren
