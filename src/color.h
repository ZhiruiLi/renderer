#pragma once

#include <cstddef>
#include <cstdint>

namespace sren {

class Color {
 private:
  static uint32_t ColorR(uint32_t c) { return (c >> 16) & 0xFF; }
  static uint32_t ShiftR(uint32_t r) { return (r & 0xFF) << 16; }
  static uint32_t ColorG(uint32_t c) { return (c >> 8) & 0xFF; }
  static uint32_t ShiftG(uint32_t g) { return (g & 0xFF) << 8; }
  static uint32_t ColorB(uint32_t c) { return (c >> 0) & 0xFF; }
  static uint32_t ShiftB(uint32_t b) { return (b << 8) & 0xFF; }

 public:
  uint32_t rgb{};

  Color() = default;
  Color(uint32_t vrgb) : rgb(vrgb) {}
  Color(uint32_t r, uint32_t g, uint32_t b)
      : Color(ShiftR(r) | ShiftG(g) | ShiftB(b)) {}

  uint32_t r() const { return ColorR(rgb); }
  uint32_t g() const { return ColorG(rgb); }
  uint32_t b() const { return ColorB(rgb); }
};

}  // namespace sren
