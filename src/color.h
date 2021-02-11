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

  static Color RGB(uint32_t rgb_hex) {
    return Color(Normalize(Shift(rgb_hex, 16)), Normalize(Shift(rgb_hex, 8)),
                 Normalize(Shift(rgb_hex, 0)));
  }

  static Color RGB(uint32_t r, uint32_t g, uint32_t b) {
    return Color(Normalize(r), Normalize(g), Normalize(b));
  }

  static Color RGBA(uint32_t rgba_hex) {
    return Color(Normalize(Shift(rgba_hex, 24)), Normalize(Shift(rgba_hex, 16)),
                 Normalize(Shift(rgba_hex, 8)), Normalize(Shift(rgba_hex, 0)));
  }

  static Color RGBA(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
    return Color(Normalize(r), Normalize(g), Normalize(b), Normalize(a));
  }

  float r() const { return r_; }
  void set_r(float r) { r_ = r; }
  float g() const { return g_; }
  void set_g(float g) { g_ = g; }
  float b() const { return b_; }
  void set_b(float b) { b_ = b; }
  float a() const { return a_; }
  void set_a(float a) { a_ = a; }

  float r_hex() const { return Unnormalize(r_); }
  void set_r_hex(uint32_t r_hex) { r_ = Normalize(r_hex); }
  float g_hex() const { return Unnormalize(g_); }
  void set_g_hex(uint32_t g_hex) { g_ = Normalize(g_hex); }
  float b_hex() const { return Unnormalize(b_); }
  void set_b_hex(uint32_t b_hex) { b_ = Normalize(b_hex); }
  float a_hex() const { return Unnormalize(a_); }
  void set_a_hex(uint32_t a_hex) { a_ = Normalize(a_hex); }

  uint32_t rgb_hex() const {
    return Unshift(r_hex(), 16) | Unshift(g_hex(), 8) | Unshift(b_hex(), 0);
  }

  uint32_t rgba_hex() const {
    return Unshift(r_hex(), 24) | Unshift(g_hex(), 16) | Unshift(b_hex(), 8) |
           Unshift(a_hex(), 0);
  }

 private:
  float r_{};
  float g_{};
  float b_{};
  float a_{};
};

}  // namespace sren
