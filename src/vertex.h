#pragma once

#include "color.h"
#include "vector.h"

namespace sren {

class Vertex {
 public:
  Vertex() = default;
  Vertex(Vector4 const &pos, Color const &color, Vector2 const &uv,
         Vector4 const &normal)
      : pos_{pos}, color_{color}, uv_{uv}, normal_{normal} {}

  Vector4 const &pos() const { return pos_; }
  Vector4 &pos() { return pos_; }
  Color const &color() const { return color_; }
  Color &color() { return color_; }
  Vector2 const &uv() const { return uv_; }
  Vector2 &uv() { return uv_; }
  Vector4 const &normal() const { return normal_; }
  Vector4 &normal() { return normal_; }

 private:
  Vector4 pos_{};
  Color color_{};
  Vector2 uv_{};
  Vector4 normal_{};
};

}  // namespace sren