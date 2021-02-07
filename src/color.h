#pragma once

#include <cstddef>
#include <cstdint>

namespace sren {

class Color {
 private:
  static float Normalize(uint32_t c);
  static uint32_t Unnormalize(float c);
  static uint32_t Shift(uint32_t c, uint32_t n) { return (c >> n) & 0xFF; }
  static uint32_t Unshift(uint32_t c, uint32_t n) { return (c & 0xFF) << n; }

 public:
  Color() = default;
  Color(float r, float g, float b, float a = 1.0f)
      : r_(r), g_(g), b_(b), a_(a) {}

  static Color RGB(uint32_t hex_color) {
    return Color(Normalize(Shift(hex_color, 16)),
                 Normalize(Shift(hex_color, 8)),
                 Normalize(Shift(hex_color, 0)));
  }

  static Color RGBA(uint32_t hex_color) {
    return Color(
        Normalize(Shift(hex_color, 24)), Normalize(Shift(hex_color, 16)),
        Normalize(Shift(hex_color, 8)), Normalize(Shift(hex_color, 0)));
  }

  float r() const { return r_; }
  void set_r(float r) { r_ = r; }
  float g() const { return g_; }
  void set_g(float g) { g_ = g; }
  float b() const { return b_; }
  void set_b(float b) { b_ = b; }
  float a() const { return a_; }
  void set_a(float a) { a_ = a; }

  uint32_t rgb_hex() const {
    return Unshift(Unnormalize(r_), 16) | Unshift(Unnormalize(g_), 8) |
           Unshift(Unnormalize(b_), 0);
  }

  uint32_t rgba_hex() const {
    return Unshift(Unnormalize(r_), 24) | Unshift(Unnormalize(g_), 16) |
           Unshift(Unnormalize(b_), 8) | Unshift(Unnormalize(a_), 0);
  }

 private:
  float r_{};
  float g_{};
  float b_{};
  float a_{};
};

}  // namespace sren
