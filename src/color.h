#pragma once

#include <cstddef>

namespace sren {

class Color {
 public:
  float r{};
  float g{};
  float b{};
  float a{};
  Color() = default;
  Color(float _r, float _g, float _b) : r{_r}, g{_g}, b{_b}, a{255} {}
  Color(float _r, float _g, float _b, float _a) : r{_r}, g{_g}, b{_b}, a{_a} {}
};

}  // namespace sren
