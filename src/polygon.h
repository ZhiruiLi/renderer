#pragma once

#include <array>

#include "vector.h"

namespace sren {

enum class PolygonState {
  kUnknown = 0x0,
  kActive = 0x1,
  kClipped = 0x2,
  kBackface = 0x4,
};

class Object;

class Polygon {
 public:
  Polygon() = default;
  Polygon(Object *object, std::array<int, 3> vertex_indexs,
          std::array<int, 3> uv_indexs, std::array<int, 3> norm_indexs)
      : object_(object),
        vertex_indexs_(vertex_indexs),
        uv_indexs_(uv_indexs),
        norm_indexs_(norm_indexs) {}

  PolygonState state() const { return state_; };
  void set_state(PolygonState state) { state_ = state; };

  Vector4 const &Vertex(int i) const;
  Vector2 const &UV(int i) const;
  Vector4 const &Norm(int i) const;

 private:
  PolygonState state_{};
  std::array<int, 3> vertex_indexs_{};
  std::array<int, 3> uv_indexs_{};
  std::array<int, 3> norm_indexs_{};
  Object *object_{};
};

}  // namespace sren
