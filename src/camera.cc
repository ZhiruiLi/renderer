#include "camera.h"

#include "matrix.h"

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
    view_matrix_ = matrixs::ViewTransform(pos_, target_);
    view_dirty_ = false;
  }
  return view_matrix_;
}

Matrix4x4 const& Camera::projection_matrix() const {
  if (projection_dirty_) {
    projection_matrix_ = matrixs::ProjectionTransform(aspect_, fov_radian_v_,
                                                      near_clip_, far_clip_);
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

}  // namespace sren
