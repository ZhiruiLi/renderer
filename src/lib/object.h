#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "material.h"
#include "model.h"
#include "polygon.h"
#include "transform.h"
#include "vector.h"

namespace sren {

class Object {
 public:
  Object() = default;
  Object(int id, std::string name) : id_{id}, name_{std::move(name)} {}

  int id() const { return id_; }
  void set_id(int id) { id_ = id; }

  std::string const &name() const { return name_; }
  void set_name(std::string name) { name_ = std::move(name); }
  int state() const { return state_; };
  void set_state(int state) { state_ = state; }
  int attribute() const { return attribute_; }
  void set_attribute(int attribute) { attribute_ = attribute; }

  void ResetTransVertexs() {
    vectors::CopyFrom3To4(model_.vertexs(), &trans_vertexs_);
  }
  void ResetTransNormals() {
    vectors::CopyFrom3To4(model_.normals(), &trans_normals_);
  }

  std::vector<Vector4> &trans_vertexs() { return trans_vertexs_; }
  std::vector<Vector4> const &trans_vertexs() const { return trans_vertexs_; }
  std::vector<Vector4> &trans_normals() { return trans_normals_; }
  std::vector<Vector4> const &trans_normals() const { return trans_normals_; }
  std::vector<Polygon> &polygons() { return polygons_; };
  std::vector<Polygon> const &polygons() const { return polygons_; };

  void set_model(Model const &model) {
    model_ = model;
    polygons_.clear();
    for (int i = 0; i < model_.nfaces(); i++) {
      polygons_.emplace_back(this, std::array<FaceDataIndex, 3>{
                                       model_.face_index(i, 0),
                                       model_.face_index(i, 1),
                                       model_.face_index(i, 2),
                                   });
    }
  }

  Model const &model() const { return model_; }

  Material &material() { return material_; }

  Material const &material() const { return material_; }

  Transform &transform() { return transform_; }

  Transform const &transform() const { return transform_; }

 private:
  int id_{};
  std::string name_{};
  int state_{};
  int attribute_{};

  // 物体的位置旋转等信息
  Transform transform_{};
  // 物体的材质信息
  Material material_{};
  // 物体的模型信息
  Model model_{};
  // 变换后物体的顶点
  std::vector<Vector4> trans_vertexs_{};
  // 变换后物体顶点的法线
  std::vector<Vector4> trans_normals_{};
  // 物体的面
  std::vector<Polygon> polygons_{};
};

}  // namespace sren
