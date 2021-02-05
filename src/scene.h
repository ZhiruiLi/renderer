#pragma once

#include <array>
#include <vector>

#include "matrix.h"
#include "object.h"
#include "point.h"
#include "vector.h"

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
  Camera(Point4 const &pos, Vector4 const &dir, Point4 const &target,
         float near_clip_z, float far_clip_z, float viewport_width,
         float viewport_height)
      : pos_{pos},
        dir_{dir},
        near_clip_z_{near_clip_z},
        far_clip_z_{far_clip_z},
        viewport_width_{viewport_width},
        viewport_height_{viewport_height},
        aspect_ratio_{viewport_width / viewport_height},
        view_port_center_{(viewport_width - 1) / 2, (viewport_height - 1) / 2},
        viewplane_width_{2.0f},
        viewplane_height_{2.0f * viewport_height / viewport_width} {}

  // 水平方向和垂直方向的视野，定死 90 度
  static constexpr float fov() { return 90.0f; }

  void TransfromUVN(Object *obj) {}

  Matrix4x4 TransformMatrix() const {
    return Matrix4x4{{{
        {u_.x(), v_.x(), n_.x(), 0.0f},
        {u_.x(), v_.x(), n_.x(), 0.0f},
        {u_.x(), v_.x(), n_.x(), 0.0f},
        {-pos_.x(), -pos_.y(), -pos_.z(), 1.0f},
    }}};
  }

 private:
  // 相机在世界坐标系中的位置
  Point4 pos_{};

  // UVN
  Vector4 u_{};
  Vector4 v_{};
  Vector4 n_{};
  // UVN 模型的注视方向
  Vector4 dir_{};
  // UVN 模型的目标位置
  Point4 target_{};

  // 水平视距
  float view_dist_h_{};
  // 垂直视距
  float view_dist_v_{};

  // 近裁剪面
  float near_clip_z_{};
  // 远裁剪面
  float far_clip_z_{};
  // TODO: 略去上下左右裁剪面

  // 视口宽度
  float viewport_width_{};
  // 视口高度
  float viewport_height_{};
  // 视口中心
  Point2 view_port_center_{};
  // 视口宽高比
  float aspect_ratio_{};
  // 视平面的宽度
  float viewplane_width_{};
  // 视平面的高度
  float viewplane_height_{};
};

class Scene {
 public:
 private:
  std::vector<Object> objects_{};
};

}  // namespace sren
