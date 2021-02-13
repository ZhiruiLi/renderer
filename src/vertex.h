#pragma once

#include "color.h"
#include "vector.h"

namespace sren {

class Vertex {
 public:
  Vertex() = default;
  Vertex(Vector4 const &pos, Vector2 const &uv, Vector3 const &norm,
         Color const &color)
      : pos_(pos), uv_(uv), norm_(norm), color_(color) {}

  Vector4 &pos() { return pos_; }
  Vector4 const &pos() const { return pos_; }
  Vector2 &uv() { return uv_; }
  Vector2 const &uv() const { return uv_; }
  Vector3 &norm() { return norm_; }
  Vector3 const &norm() const { return norm_; }
  Color &color() { return color_; }
  Color const &color() const { return color_; }

  Vertex &operator+=(Vertex const &rhs) {
    pos_ += rhs.pos();
    uv_ += rhs.uv();
    norm_ += rhs.norm();
    color_ += rhs.color();
    return *this;
  }

  friend Vertex operator+(Vertex lhs, Vertex const &rhs) {
    lhs.pos() += rhs.pos();
    lhs.uv() += rhs.uv();
    lhs.norm() += rhs.norm();
    lhs.color() += rhs.color();
    return lhs;
  }

  Vertex &operator-=(Vertex const &rhs) {
    pos_ -= rhs.pos();
    uv_ -= rhs.uv();
    norm_ -= rhs.norm();
    color_ -= rhs.color();
    return *this;
  }

  friend Vertex operator-(Vertex lhs, Vertex const &rhs) {
    lhs.pos() -= rhs.pos();
    lhs.uv() -= rhs.uv();
    lhs.norm() -= rhs.norm();
    lhs.color() -= rhs.color();
    return lhs;
  }

  Vertex &operator*=(float s) {
    pos_ *= s;
    uv_ *= s;
    norm_ *= s;
    color_ *= s;
    return *this;
  }

  friend Vertex operator*(Vertex v, float s) {
    v.pos() *= s;
    v.uv() *= s;
    v.norm() *= s;
    v.color() *= s;
    return v;
  }

  Vertex &operator/=(float s) {
    pos_ /= s;
    uv_ /= s;
    norm_ /= s;
    color_ /= s;
    return *this;
  }

  friend Vertex operator/(Vertex v, float s) {
    v.pos() /= s;
    v.uv() /= s;
    v.norm() /= s;
    v.color() /= s;
    return v;
  }

 private:
  Vector4 pos_{};
  Vector2 uv_{};
  Vector3 norm_{};
  Color color_{};
};

}  // namespace sren
