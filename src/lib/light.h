#pragma once

#include <algorithm>
#include <cmath>

#include "color.h"
#include "material.h"
#include "polygon.h"
#include "vector.h"

namespace sren {

struct LightCoefficient {
  float ambient{};
  float diffuse{};
  float specular{};
};

namespace details {

inline Vector3 Reflect(Vector3 const &light, Vector3 const &norm) {
  return light - 2 * light * norm * norm;
}

inline Vector3 Normal(Vertex const &v) {
  auto normal = v.normal() / v.normal().w();
  return {normal.x(), normal.y(), normal.z()};
}

inline Vector3 Position(Vertex v) {
  auto world_pos = v.world_pos() / v.world_pos().w();
  return {world_pos.x(), world_pos.y(), world_pos.z()};
}

}  // namespace details

class DirLight {
 public:
  DirLight() = default;
  DirLight(Vector3 const &direction, Color const &color,
           LightCoefficient const &coeff)
      : direction_(direction), color_(color), coefficient_(coeff) {
    UpdateColors();
  }

  Color const &color() { return color_; }
  void set_color(Color const &color) {
    color_ = color;
    UpdateColors();
  }

  LightCoefficient const &coefficient() { return coefficient_; }
  void set_coefficient(LightCoefficient const &coeff) {
    coefficient_ = coeff;
    UpdateColors();
  }

  Vector3 &direction() { return direction_; }
  Vector3 const &direction() const { return direction_; }

  Color const &ambient() const { return ambient_; }
  Color const &diffuse() const { return diffuse_; }
  Color const &specular() const { return specular_; }

  Color IlluminateAmbient() const { return ambient_; }

  Color IlluminateDiffuse(Vector3 const &normal) const {
    Vector3 const light_dir = -direction_.Normalize();
    float const diffuse_str = std::max(normal * light_dir, 0.0f);
    return diffuse_ * diffuse_str;
  }

  Color IlluminateSpecular(Vector3 const &obj_pos, Vector3 const &normal,
                           float shininess, Vector3 const &camera_pos) const {
    Vector3 const light_dir = direction_.Normalize();
    Vector3 const reflect_dir = details::Reflect(light_dir, normal);
    Vector3 const view_dir = (camera_pos - obj_pos).Normalize();
    float const specular_str = std::max(view_dir * reflect_dir, 0.0f);
    float const specular_str1 = std::pow(specular_str, shininess);
    return specular_str1 * specular_;
  }

 private:
  void UpdateColors() {
    ambient_ = color_ * coefficient_.ambient;
    diffuse_ = color_ * coefficient_.diffuse;
    specular_ = color_ * coefficient_.specular;
  }

  Vector3 direction_{};
  Color ambient_{};
  Color diffuse_{};
  Color specular_{};
  Color color_{};
  LightCoefficient coefficient_{};
};

class Lights {
 public:
  Lights() = default;

  std::vector<DirLight> &dir_lights() { return dir_lights_; }
  std::vector<DirLight> const &dir_lights() const { return dir_lights_; }

  Color IlluminateOne(Vertex const &vertex, Color const &color,
                      Vector3 const &camera_pos, DirLight const &light) const {
    auto const normal = details::Normal(vertex);
    auto const pos = details::Position(vertex);
    auto const c1 = color * light.IlluminateAmbient();
    auto const c2 = color * light.IlluminateDiffuse(normal);
    return c1 + c2;
  }

  Color IlluminateOne(Vertex const &vertex, Material const &material,
                      Vector3 const &camera_pos, DirLight const &light) const {
    auto const &diffuse = material.Diffuse(vertex.uv());
    auto const &specular = material.Specular(vertex.uv());
    auto const shininess = material.shininess();
    auto const norm = details::Normal(vertex);
    auto const pos = details::Position(vertex);
    auto const c1 = diffuse * light.IlluminateAmbient();
    auto const c2 = diffuse * light.IlluminateDiffuse(norm);
    auto const c3 =
        specular * light.IlluminateSpecular(pos, norm, shininess, camera_pos);
    return c1 + c2 + c3;
  }

  Color Illuminate(Vertex const &vertex, Material const &material,
                   Vector3 const &camera_pos) const {
    if (dir_lights_.empty()) {
      return Color{};
    }
    Color c = IlluminateOne(vertex, material, camera_pos, dir_lights_[0]);
    for (int i = 1; i < dir_lights_.size(); i++) {
      c *= IlluminateOne(vertex, material, camera_pos, dir_lights_[i]);
    }
    return c;
  }

  Color Illuminate(Vertex const &vertex, Color const &color,
                   Vector3 const &camera_pos) const {
    if (dir_lights_.empty()) {
      return Color{};
    }
    Color c = IlluminateOne(vertex, color, camera_pos, dir_lights_[0]);
    for (int i = 1; i < dir_lights_.size(); i++) {
      c *= IlluminateOne(vertex, color, camera_pos, dir_lights_[i]);
    }
    return c;
  }

 private:
  std::vector<DirLight> dir_lights_{};
};

}  // namespace sren
