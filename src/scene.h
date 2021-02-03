#pragma once

#include "matrix.h"

namespace sren {

struct Scene {
 private:
  Matrix4x4 world_transform_;
  Matrix4x4 view_transform_;
  Matrix4x4 projection_transform_;
  Matrix4x4 full_transform_;
};

}  // namespace sren
