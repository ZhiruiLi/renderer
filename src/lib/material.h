#pragma once

#include "color.h"
#include "data2d.h"

namespace sren {

class Material {
 public:
  Material() = default;
  Material(Data2D diffuse, Data2D specular, Data2D normal)
      : diffuse_map_(std::move(diffuse)),
        specular_map_(std::move(specular)),
        normal_map_(std::move(normal)) {}

  Data2D &diffuse_map() { return diffuse_map_; }
  Data2D const &diffuse_map() const { return diffuse_map_; }
  Data2D &specular_map() { return specular_map_; }
  Data2D const &specular_map() const { return specular_map_; }
  Data2D &normal_map() { return normal_map_; }
  Data2D const &normal_map() const { return normal_map_; }
  void set_shininess(float shininess) { shininess_ = shininess; }
  float shininess() const { return shininess_; }

  Color Diffuse(Vector2 const &uv) const {
    return colors::GetFromData2D(diffuse_map_, uv);
  }

  float Specular(Vector2 const &uv) const {
    return colors::GetFromData2D(specular_map_, uv)[0];
  }

  Vector3 Normal(Vector2 const &uv) const {
    return vectors::GetFromData2D(normal_map_, uv);
  }

 private:
  Data2D diffuse_map_{};
  Data2D specular_map_{};
  Data2D normal_map_{};
  float shininess_{32};
};

};  // namespace sren
