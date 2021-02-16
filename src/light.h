#pragma once

#include "color.h"
#include "vector.h"

namespace sren {

class DirLight {
 public:
  DirLight() = default;
  DirLight(Vector3 const &direction, Color const &ambient, Color const &diffuse,
           Color const &specular)
      : direction_(direction),
        ambient_(ambient),
        diffuse_(diffuse),
        specular_(specular) {}

  Vector3 &direction() { return direction_; }
  Vector3 const &direction() const { return direction_; }
  Color &ambient() { return ambient_; }
  Color const &ambient() const { return ambient_; }
  Color &diffuse() { return diffuse_; }
  Color const &diffuse() const { return diffuse_; }
  Color &specular() { return specular_; }
  Color const &specular() const { return specular_; }

 private:
  Vector3 direction_{};
  Color ambient_{};
  Color diffuse_{};
  Color specular_{};
};

struct PointLight {
  Vector3 position{};
  float constant{};
  float linear{};
  float quadratic{};
  Color ambient{};
  Color diffuse{};
  Color specular{};

  Color Illuminate(Color const &color);
};

}  // namespace sren
