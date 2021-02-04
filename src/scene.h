#pragma once

#include <vector>

#include "matrix.h"
#include "object.h"
#include "point.h"

namespace sren {

class Transform {
 public:
  Transform() = default;

  void ApplyTo(Object *obj) const {
    assert(updated_);
    assert(obj->vertexs().size() == obj->trans_vertexs().size());
    for (auto i = 0; i < obj->vertexs().size(); i++) {
      obj->trans_vertexs()[i] = obj->vertexs()[i] * full_transform_;
    }
  }

  void Update() {
    full_transform_ = world_transform_;
    full_transform_ *= view_transform_;
    full_transform_ *= projection_transform_;
    updated_ = true;
  }

  Matrix4x4 world_transform() const { return world_transform_; }
  void set_world_transform(Matrix4x4 const &m) {
    updated_ = false;
    world_transform_ = m;
  }

  Matrix4x4 view_transform() const { return view_transform_; }
  void set_view_transform(Matrix4x4 const &m) {
    updated_ = false;
    view_transform_ = m;
  }

  Matrix4x4 projection_transform() const { return projection_transform_; }
  void set_projection_transform(Matrix4x4 const &m) {
    updated_ = false;
    projection_transform_ = m;
  }

 private:
  bool updated_{};
  Matrix4x4 world_transform_{};
  Matrix4x4 view_transform_{};
  Matrix4x4 projection_transform_{};
  Matrix4x4 full_transform_{};
};

class Camera {
 public:
 private:
  Point4 world_pos_{};
  float ang_x_{};
  float ang_y_{};
  float ang_z_{};
};

class Scene {
 public:
 private:
  std::vector<Object> objects_{};
};

}  // namespace sren
