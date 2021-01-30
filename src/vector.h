#pragma once

#include <cstddef>

namespace sren {

class Vector2i {
 public:
  int x{};
  int y{};
  Vector2i() = default;
  Vector2i(int _x, int _y) : x{_x}, y{_y} {}
};

class Vector4i {
 public:
  int x{};
  int y{};
  int z{};
  int w{};
  Vector4i() = default;
  Vector4i(int _x, int _y, int _z, int _w) : x{_x}, y{_y}, z{_z}, w{_w} {}
};

}  // namespace sren
