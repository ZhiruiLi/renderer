#pragma once

#include "color.h"
#include "vector.h"

namespace sren {

class Vertex {
 public:
  Vertex() = default;
  Vertex(Vector4 const &pos) : pos_(pos) {}
  Vertex(Vector4 const &pos, Color const &color, Vector2 const &uv,
         Vector4 const &normal)
      : pos_(pos), color_(color), uv_(uv), normal_(normal) {}

  Vector4 const &pos() const { return pos_; }
  Vector4 &pos() { return pos_; }
  Color const &color() const { return color_; }
  Color &color() { return color_; }
  Vector2 const &uv() const { return uv_; }
  Vector2 &uv() { return uv_; }
  Vector4 const &normal() const { return normal_; }
  Vector4 &normal() { return normal_; }

  friend bool operator==(Vertex const &lhs, Vertex const &rhs) {
    return lhs.pos() == rhs.pos() && lhs.color() == rhs.color() &&
           lhs.uv() == rhs.uv() && lhs.normal() == rhs.normal();
  }

  friend bool operator!=(Vertex const &lhs, Vertex const &rhs) {
    return !(lhs == rhs);
  }

  Vertex &operator+=(Vertex const &rhs) {
    pos_ += rhs.pos();
    color_ += rhs.color();
    uv_ += rhs.uv();
    normal_ += rhs.normal();
    return *this;
  }

  friend Vertex operator+(Vertex lhs, Vertex const &rhs) {
    lhs += rhs;
    return lhs;
  }

  Vertex &operator-=(Vertex const &rhs) {
    pos_ -= rhs.pos();
    color_ -= rhs.color();
    uv_ -= rhs.uv();
    normal_ -= rhs.normal();
    return *this;
  }

  friend Vertex operator-(Vertex lhs, Vertex const &rhs) {
    lhs -= rhs;
    return lhs;
  }

  Vertex &operator*=(float s) {
    pos_ *= s;
    color_ *= s;
    uv_ *= s;
    normal_ *= s;
    return *this;
  }

  friend Vertex operator*(Vertex v, float s) {
    v *= s;
    return v;
  }

  Vertex &operator/=(float s) {
    pos_ /= s;
    color_ /= s;
    uv_ /= s;
    normal_ /= s;
    return *this;
  }

  friend Vertex operator/(Vertex v, float s) {
    v /= s;
    return v;
  }

 private:
  Vector4 pos_{};
  Color color_{};
  Vector2 uv_{};
  Vector4 normal_{};
};

}  // namespace sren
