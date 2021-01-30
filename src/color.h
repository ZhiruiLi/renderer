#pragma once

#include <cstddef>

namespace sren {

class Color {
 public:
  int r{};
  int g{};
  int b{};
  int a{};
  Color() = default;
  Color(int _r, int _g, int _b) : r{_r}, g{_g}, b{_b}, a{255} {}
  Color(int _r, int _g, int _b, int _a) : r{_r}, g{_g}, b{_b}, a{_a} {}
};

}  // namespace sren
