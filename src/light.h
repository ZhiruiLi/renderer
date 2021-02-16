#pragma once

#include "color.h"
#include "src/polygon.h"
#include "vector.h"

namespace sren {

struct LightCoefficient {
  float ambient{};
  float diffuse{};
  float specular{};
};

class DirLight {
 public:
  DirLight() = default;
  DirLight(Vector4 const &direction, Color const &ambient, Color const &diffuse,
           Color const &specular)
      : direction_(direction),
        ambient_(ambient),
        diffuse_(diffuse),
        specular_(specular) {}

  Vector4 &direction() { return direction_; }
  Vector4 const &direction() const { return direction_; }
  Color &ambient() { return ambient_; }
  Color const &ambient() const { return ambient_; }
  Color &diffuse() { return diffuse_; }
  Color const &diffuse() const { return diffuse_; }
  Color &specular() { return specular_; }
  Color const &specular() const { return specular_; }

  Color IlluminateOne(Vertex const &v, LightCoefficient const &coeff,
                      Polygon *poly) const {
    Vector4 light_dir = -direction_.Normalize();
    float const diffuse_str = std::max(v.normal() * light_dir, 0.0f);
    Color const ambient = ambient_ * coeff.ambient;
    Color const diffuse = diffuse_ * diffuse_str * coeff.diffuse;
    return ambient + diffuse;
  }

  void Illuminate(LightCoefficient const &coeff, Polygon *poly) const {
    for (int i = 0; i < 3; i++) {
      poly->SetLight(i, IlluminateOne(poly->Vertex(i), coeff, poly));
    }
  }

 private:
  Vector4 direction_{};
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
