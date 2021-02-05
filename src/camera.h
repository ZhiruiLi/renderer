#pragma once

#include "matrix.h"
#include "point.h"
#include "vector.h"

namespace sren {

class Camera {
 public:
  Camera() = default;
  ~Camera() {}

  Camera& SetLookAt(Point3 const& pos, Point3 const& target,
                    Vector3 const& up = {0, 1, 0}) {
    pos_ = pos;
    target_ = target;
    up_ = up;
    view_dirty_ = true;
    transform_dirty_ = true;
    return *this;
  }

  Camera& SetPerspective(float fov_radian, float aspect) {
    return SetPerspective(fov_radian, aspect, near_clip(), far_clip());
  }

  Camera& SetPerspective(float fov_radian, float aspect, float near_clip,
                         float far_clip) {
    fov_radian_ = fov_radian;
    aspect_ = aspect;
    near_clip_ = near_clip;
    far_clip_ = far_clip;
    view_dirty_ = true;
    projection_dirty_ = true;
    return *this;
  }

  Matrix4x4 const& view_matrix() const {
    if (view_dirty_) {
      view_matrix_ = CalcViewMatrix();
      view_dirty_ = false;
    }
    return view_matrix_;
  }

  Matrix4x4 const& projection_matrix() const {
    if (projection_dirty_) {
      projection_matrix_ = {};  // TODO: impl projection matrix calc
      projection_dirty_ = false;
    }
    return projection_matrix_;
  }

  Matrix4x4 const& transform_matrix() const {
    if (transform_dirty_) {
      transform_matrix_ = view_matrix() * projection_matrix();
      transform_dirty_ = false;
    }
    return transform_matrix_;
  }

  float near_clip() const { return near_clip_; }

  float far_clip() const { return far_clip_; }

 private:
  Vector3 CalcViewDirection() const { return (target_ - pos_).Normalize(); }

  Matrix4x4 CalcViewMatrix() const {
    Vector3 const n = (target_ - pos_).Normalize();
    Vector3 const u = (n ^ up_).Normalize();
    Vector3 const v = u ^ n;
    auto const posv = pos_ - Point3::Zero();
    return Matrix4x4({{
        {u.x(), v.x(), n.x(), 0.0f},
        {u.y(), v.y(), n.y(), 0.0f},
        {u.z(), v.z(), n.z(), 0.0f},
        {-(posv * u), -(posv * v), -(posv * n), 1.0f},
    }});
  }

  Matrix4x4 CalcProjectionMatrix() const {
    Vector3 const n = CalcViewDirection();
    Vector3 const u = (n ^ up_).Normalize();
    Vector3 const v = u ^ n;
    auto const posv = pos_ - Point3::Zero();
    return Matrix4x4({{
        {u.x(), v.x(), n.x(), 0.0f},
        {u.y(), v.y(), n.y(), 0.0f},
        {u.z(), v.z(), n.z(), 0.0f},
        {-(posv * u), -(posv * v), -(posv * n), 1.0f},
    }});
  }

  Point3 pos_{0, 0, 1};
  Point3 target_{0, 0, 0};
  Vector3 up_{0, 1, 0};
  float fov_radian_{90.0f};
  float aspect_ = 1.0f;
  float near_clip_{0.1f};
  float far_clip_{10000.0f};
  mutable bool view_dirty_ = true;
  mutable bool projection_dirty_ = true;
  mutable bool transform_dirty_ = true;
  mutable Matrix4x4 view_matrix_{};
  mutable Matrix4x4 projection_matrix_{};
  mutable Matrix4x4 transform_matrix_{};
};

}  // namespace sren
