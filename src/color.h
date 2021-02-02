#pragma once

#include <cstddef>
#include <cstdint>

namespace sren {

class Color {
 private:
  static float ColorR(uint32_t c) { return (c >> 24) & 0xFF; }
  static float ColorG(uint32_t c) { return (c >> 16) & 0xFF; }
  static float ColorB(uint32_t c) { return (c >> 8) & 0xFF; }
  static float ColorA(uint32_t c) { return (c >> 0) & 0xFF; }

 public:
  float r{};
  float g{};
  float b{};
  float a{};
  Color() = default;
  Color(uint32_t c) : Color(ColorR(c), ColorG(c), ColorB(c), ColorA(c)) {}
  Color(float vr, float vg, float vb) : Color(vr, vg, vb, 255.0f) {}
  Color(float vr, float vg, float vb, float va) : r{vr}, g{vg}, b{vb}, a{va} {}
  uint32_t AsRGBA() const {
    const auto uir = ((uint32_t)r & 0xFF);
    const auto uig = ((uint32_t)g & 0xFF);
    const auto uib = ((uint32_t)b & 0xFF);
    const auto uia = ((uint32_t)a & 0xFF);
    return (uir << 24) | (uig << 16) | (uib << 8) | (uia << 0);
  }
  uint32_t AsRGB() const { return AsRGBA() >> 8; }
};

}  // namespace sren
