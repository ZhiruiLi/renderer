#pragma once

#include "cache.h"
#include "matrix.h"
#include "vector.h"

namespace sren {

class Transform {
 public:
  Transform() = default;

  void set_world_pos(Vector3 const &pos) {
    world_pos_ = pos;
    world_matrix_cache_.mark_dirty();
    model_matrix_cache_.mark_dirty();
  }

  Vector3 const &world_pos() const { return world_pos_; }

  void set_rotation(Vector3 const &rotation) {
    rotation_ = rotation;
    rotate_matrix_cache_.mark_dirty();
    model_matrix_cache_.mark_dirty();
  }

  Vector3 const &rotation() const { return rotation_; }

  Matrix4x4 const &rotate_matrix() const {
    if (rotate_matrix_cache_.is_dirty()) {
      rotate_matrix_cache_.set_data(matrixs::RotateTransform(rotation_));
    }
    return rotate_matrix_cache_.data();
  }

  Matrix4x4 const &world_matrix() const {
    if (world_matrix_cache_.is_dirty()) {
      world_matrix_cache_.set_data(matrixs::WorldTransform(world_pos_));
    }
    return world_matrix_cache_.data();
  }

  Matrix4x4 const &model_matrix() const {
    if (model_matrix_cache_.is_dirty()) {
      model_matrix_cache_.set_data(world_matrix() * rotate_matrix());
    }
    return model_matrix_cache_.data();
  }

 private:
  // 物体在世界坐标系中的位置
  Vector3 world_pos_{0.0f, 0.0f, 0.0f};
  // 物体在局部坐标系下的旋转角度
  Vector3 rotation_{0.0f, 0.0f, 0.0f};

  mutable Cache<Matrix4x4> rotate_matrix_cache_{};
  mutable Cache<Matrix4x4> world_matrix_cache_{};
  mutable Cache<Matrix4x4> model_matrix_cache_{};
};

}  // namespace sren
