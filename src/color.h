#pragma once

#include <cstddef>
#include <cstdint>

namespace sren {

class Color {
 private:
  static uint32_t ColorR(uint32_t c) { return (c >> 24) & 0xFF; }
  static uint32_t ShiftR(uint32_t r) { return (r & 0xFF) << 24; }

  static uint32_t ColorG(uint32_t c) { return (c >> 16) & 0xFF; }
  static uint32_t ShiftG(uint32_t g) { return (g & 0xFF) << 16; }

  static uint32_t ColorB(uint32_t c) { return (c >> 8) & 0xFF; }
  static uint32_t ShiftB(uint32_t b) { return (b & 0xFF) << 8; }

  static uint32_t ColorA(uint32_t c) { return (c >> 0) & 0xFF; }
  static uint32_t ShiftA(uint32_t a) { return (a & 0xFF) << 0; }

 public:
  Color() = default;
  explicit Color(uint32_t vhex) : hex_(vhex) {}
  Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a = 255)
      : Color(ShiftR(r) | ShiftG(g) | ShiftB(b) | ShiftA(a)) {}

  uint32_t r() const { return ColorR(hex_); }
  uint32_t g() const { return ColorG(hex_); }
  uint32_t b() const { return ColorB(hex_); }
  uint32_t a() const { return ColorA(hex_); }
  uint32_t hex() const { return hex_; }

 private:
  uint32_t hex_{};
};

}  // namespace sren
