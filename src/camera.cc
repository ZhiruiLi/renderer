#include "camera.h"

#include "matrix.h"

namespace sren {

Camera& Camera::SetLookAt(Vector3 const& pos, Vector3 const& target,
                          Vector3 const& up) {
  pos_ = pos;
  target_ = target;
  up_ = up;
  view_matrix_cache_.mark_dirty();
  transform_matrix_cache_.mark_dirty();
  return *this;
}

Camera& Camera::SetPerspective(float fov_radian_v, float aspect,
                               float near_clip, float far_clip) {
  fov_radian_v_ = fov_radian_v;
  aspect_ = aspect;
  near_clip_ = near_clip;
  far_clip_ = far_clip;
  projection_matrix_cache_.mark_dirty();
  transform_matrix_cache_.mark_dirty();
  return *this;
}

Matrix4x4 const& Camera::view_matrix() const {
  if (view_matrix_cache_.is_dirty()) {
    view_matrix_cache_.set_data(matrixs::ViewTransform(pos_, target_));
  }
  return view_matrix_cache_.data();
}

Matrix4x4 const& Camera::projection_matrix() const {
  if (projection_matrix_cache_.is_dirty()) {
    projection_matrix_cache_.set_data(matrixs::ProjectionTransform(
        aspect_, fov_radian_v_, near_clip_, far_clip_));
  }
  return projection_matrix_cache_.data();
}

Matrix4x4 const& Camera::transform_matrix() const {
  if (transform_matrix_cache_.is_dirty()) {
    transform_matrix_cache_.set_data(view_matrix() * projection_matrix());
  }
  return transform_matrix_cache_.data();
}

}  // namespace sren
