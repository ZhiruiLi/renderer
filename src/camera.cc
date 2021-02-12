#include "camera.h"

namespace sren {

Camera& Camera::SetLookAt(Vector3 const& pos, Vector3 const& target,
                          Vector3 const& up) {
  pos_ = pos;
  target_ = target;
  up_ = up;
  view_dirty_ = true;
  transform_dirty_ = true;
  return *this;
}

Camera& Camera::SetPerspective(float fov_radian_v, float aspect,
                               float near_clip, float far_clip) {
  fov_radian_v_ = fov_radian_v;
  aspect_ = aspect;
  near_clip_ = near_clip;
  far_clip_ = far_clip;
  view_dirty_ = true;
  projection_dirty_ = true;
  return *this;
}

Matrix4x4 const& Camera::view_matrix() const {
  if (view_dirty_) {
    view_matrix_ = CalcViewMatrix();
    view_dirty_ = false;
  }
  return view_matrix_;
}

Matrix4x4 const& Camera::projection_matrix() const {
  if (projection_dirty_) {
    projection_matrix_ = {};  // TODO: impl projection matrix calc
    projection_dirty_ = false;
  }
  return projection_matrix_;
}

Matrix4x4 const& Camera::transform_matrix() const {
  if (transform_dirty_) {
    transform_matrix_ = view_matrix() * projection_matrix();
    transform_dirty_ = false;
  }
  return transform_matrix_;
}

Matrix4x4 Camera::CalcViewMatrix() const {
  Vector3 const n = (target_ - pos_).Normalize();
  Vector3 const u = (n ^ up_).Normalize();
  Vector3 const v = u ^ n;
  auto const posv = pos_ - Vector3::Zero();
  return Matrix4x4({{
      {u.x(), v.x(), n.x(), 0.0f},
      {u.y(), v.y(), n.y(), 0.0f},
      {u.z(), v.z(), n.z(), 0.0f},
      {-(posv * u), -(posv * v), -(posv * n), 1.0f},
  }});
}

Matrix4x4 Camera::CalcProjectionMatrix() const {
  auto const n = near_clip();
  auto const f = far_clip();
  auto const fov_h = fov_radian_v_;  // theta
  auto const fov_v = fov_h * aspect_;
  return Matrix4x4({{
      {1 / tan(fov_h / 2), 0.0f, 0.0f, 0.0f},
      {0.0f, 1 / tan(fov_v / 2), 0.0f, 0.0f},
      {0.0f, 0.0f, f / (f - n), 1.0f},
      {0.0f, 0.0f, f * n / (n - f), 0.0f},
  }});
}

}  // namespace sren
