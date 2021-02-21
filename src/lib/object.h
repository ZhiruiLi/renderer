#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "material.h"
#include "model.h"
#include "polygon.h"
#include "render_style.h"
#include "transform.h"
#include "vector.h"

namespace sren {

class Object {
 public:
  Object() = default;
  Object(int id, std::string name, bool is_alpha)
      : id_(id), name_(std::move(name)), is_alpha_(is_alpha) {}

  int state() const { return state_; };
  void set_state(int state) { state_ = state; }

  int id() const { return id_; }
  std::string const &name() const { return name_; }
  bool is_alpha() const { return is_alpha_; }

  void ResetWorldVertexs() {
    vectors::CopyFrom3To4(model_.vertexs(), &world_vertexs_);
  }
  void ResetTransVertexs() {
    vectors::CopyFrom3To4(model_.vertexs(), &trans_vertexs_);
  }
  void ResetTransNormals() {
    vectors::CopyFrom3To4(model_.normals(), &trans_normals_);
  }

  std::vector<Vector4> &world_vertexs() { return world_vertexs_; }
  std::vector<Vector4> const &world_vertexs() const { return world_vertexs_; }
  std::vector<Vector4> &trans_vertexs() { return trans_vertexs_; }
  std::vector<Vector4> const &trans_vertexs() const { return trans_vertexs_; }
  std::vector<Vector4> &trans_normals() { return trans_normals_; }
  std::vector<Vector4> const &trans_normals() const { return trans_normals_; }
  std::vector<Polygon> &polygons() { return polygons_; };
  std::vector<Polygon> const &polygons() const { return polygons_; };

  void set_model(Model model) {
    model_ = std::move(model);
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

  void set_render_style(unsigned int s) { render_style_ = s; }
  unsigned int render_style() const { return render_style_; }

 private:
  int id_{};
  std::string name_{};
  bool is_alpha_{};
  int state_{};

  // 物体的位置旋转等信息
  Transform transform_{};
  // 物体的材质信息
  Material material_{};
  // 物体的模型信息
  Model model_{};
  // 世界坐标下物体的位置
  std::vector<Vector4> world_vertexs_{};
  // 变换后物体的顶点
  std::vector<Vector4> trans_vertexs_{};
  // 变换后物体顶点的法线
  std::vector<Vector4> trans_normals_{};
  // 物体的面
  std::vector<Polygon> polygons_{};
  // 渲染风格
  unsigned int render_style_{kRenderTexture};
};

}  // namespace sren
