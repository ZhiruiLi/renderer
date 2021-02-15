#pragma once

#include "color.h"
#include "vector.h"

namespace sren {

struct DirLight {
  Vector3 direction{};
  Color ambient{};
  Color diffuse{};
  Color specular{};
};

struct PointLight {
  Vector3 position{};
  float constant{};
  float linear{};
  float quadratic{};
  Color ambient{};
  Color diffuse{};
  Color specular{};
};

}  // namespace sren
