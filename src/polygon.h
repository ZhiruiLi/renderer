#pragma once

#include <array>

#include "vertex.h"

namespace sren {

class Object;

enum class PolygonState {
  kUnknown = 0x0,
  kActive = 0x1,
  kClipped = 0x2,
  kBackface = 0x4,
};

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

  Vertex Vertex(int i) const;
  Color TextureDiffuse(Vector2 const &uv) const;
  Vector3 TextureNormal(Vector2 const &uv) const;

  Polygon &SetLight(int i, Color const &c);
  Color const &Light(int i) const;

 private:
  PolygonState state_{};
  std::array<int, 3> vertex_indexs_{};
  std::array<int, 3> uv_indexs_{};
  std::array<int, 3> norm_indexs_{};
  std::array<Color, 3> lights_{};
  Object *object_{};
};

}  // namespace sren
