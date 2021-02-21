#pragma once

#include <array>

#include "lib/render_style.h"
#include "material.h"
#include "model.h"
#include "vertex.h"

namespace sren {

class Object;

enum class PolygonState {
  kActive = 0x0,
  kClipped = 0x1,
  kBackface = 0x3,
};

class Polygon {
 public:
  Polygon() = default;
  Polygon(Object *object, std::array<FaceDataIndex, 3> face_indexs)
      : object_(object), face_indexs_(face_indexs) {}

  PolygonState state() const { return state_; };
  void set_state(PolygonState state) { state_ = state; };
  Vertex vertex(int i) const;
  Material const &material() const;
  unsigned int render_style() const;
  bool is_alpha() const;

  Vector3 normal() const { return direction().Normalize(); }

 private:
  Vector3 direction() const {
    return (vertex(1).pos().AsVector3() - vertex(0).pos().AsVector3()) ^
           (vertex(2).pos().AsVector3() - vertex(0).pos().AsVector3());
  }

  PolygonState state_{};
  std::array<FaceDataIndex, 3> face_indexs_{};
  Object *object_{};
};

}  // namespace sren
