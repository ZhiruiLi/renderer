#pragma once

#include "cache.h"
#include "matrix.h"
#include "vector.h"

namespace sren {

class Camera {
 public:
  Camera() = default;
  ~Camera() {}

  void SetLookAt(Vector3 const& pos, Vector3 const& target) {
    SetLookAt(pos, target, {0, 1, 0});
  }

  void SetLookAt(Vector3 const& pos, Vector3 const& target, Vector3 const& up);

  void SetPerspective(float fov_radian_v, float aspect) {
    SetPerspective(fov_radian_v, aspect, near_clip(), far_clip());
  }

  void SetPerspective(float fov_radian_v, float aspect, float near_clip,
                      float far_clip);

  Matrix4x4 const& view_matrix() const;
  Matrix4x4 const& projection_matrix() const;
  Matrix4x4 const& transform_matrix() const;
  float near_clip() const { return near_clip_; }
  float far_clip() const { return far_clip_; }
  float fov_radian_v() const { return fov_radian_v_; }
  float fov_radian_h() const { return fov_radian_v_ * aspect_; }
  Vector3 direction() const { return (target_ - pos_).Normalize(); }
  Vector3 const& pos() const { return pos_; }
  Vector3 const& target() const { return target_; }

 private:
  Vector3 pos_{0, 0, 1};
  Vector3 target_{0, 0, 0};
  Vector3 up_{0, 1, 0};
  float fov_radian_v_{90.0f};
  float aspect_ = 1.0f;
  float near_clip_{0.1f};
  float far_clip_{10000.0f};
  mutable Cache<Matrix4x4> view_matrix_cache_{};
  mutable Cache<Matrix4x4> projection_matrix_cache_{};
  mutable Cache<Matrix4x4> transform_matrix_cache_{};
};

}  // namespace sren
