#pragma once

#include <algorithm>
#include <cmath>

#include "color.h"
#include "polygon.h"
#include "vector.h"

namespace sren {

struct LightCoefficient {
  float ambient{};
  float diffuse{};
  float specular{};
  float shininess{};
};

namespace details {

inline Vector4 Reflect(Vector4 const &light, Vector4 const &norm) {
  return light - 2 * light * norm * norm;
}

}  // namespace details

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

  Color IlluminateAmbient(LightCoefficient const &coeff) const {
    return ambient_ * coeff.ambient;
  }

  Color IlluminateDiffuse(Vertex const &vertex,
                          LightCoefficient const &coeff) const {
    Vector4 const light_dir = -direction_.Normalize();
    float const diffuse_str = std::max(vertex.normal() * light_dir, 0.0f);
    return diffuse_ * diffuse_str * coeff.diffuse;
  }

  Color IlluminateSpecular(Vertex const &vertex, Vector4 const &camera_pos,
                           LightCoefficient const &coeff) const {
    Vector4 const light_dir = direction_.Normalize();
    Vector4 const reflect_dir = details::Reflect(light_dir, vertex.normal());
    Vector4 const view_dir = (camera_pos - vertex.pos()).Normalize();
    float const specular_str = std::max(view_dir * reflect_dir, 0.0f);
    auto const specular_str1 = std::pow(specular_str, coeff.shininess);
    return coeff.specular * specular_str1 * specular_;
  }

  Color IlluminateOne(Vertex const &vertex, Vector4 const &camera_pos,
                      LightCoefficient const &coeff) const {
    return IlluminateAmbient(coeff) + IlluminateDiffuse(vertex, coeff) +
           IlluminateSpecular(vertex, camera_pos, coeff);
  }

  void Illuminate(Vector4 camera_pos, LightCoefficient const &coeff,
                  Polygon *poly) const {
    for (int i = 0; i < 3; i++) {
      poly->SetLight(i, IlluminateOne(poly->Vertex(i), camera_pos, coeff));
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
