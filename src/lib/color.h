#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>

#include "data2d.h"
#include "key.h"
#include "math.h"
#include "vector.h"

namespace sren {

class Color {
 public:
  enum Format {
    kGrayScale = 1,
    kGrayAlpha = 2,
    kRGB = 3,
    kRGBA = 4,
  };
  using value_type = float;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = value_type*;
  using const_iterator = value_type const*;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 private:
  static value_type Normalize(uint32_t c) { return c / 255.0f; }
  static uint32_t Unnormalize(value_type c) { return uint32_t(c * 255); }
  static uint32_t Shift(uint32_t c, uint32_t n) { return (c >> n) & 0xFF; }
  static uint32_t Unshift(uint32_t c, uint32_t n) { return (c & 0xFF) << n; }

 public:
  Color() = default;
  Color(Vector3 const& rgb) : Color(rgb[0], rgb[1], rgb[2]) {}
  Color(Vector4 const& rgba) : Color(rgba[0], rgba[1], rgba[2], rgba[3]) {}
  Color(value_type r, value_type g, value_type b, value_type a = 1.0f)
      : data_{r, g, b, a} {}

  static Color Gray(uint32_t g) {
    return Color(Normalize(g), Normalize(g), Normalize(g));
  }

  static Color GrayAlpha(uint32_t ga_hex) {
    auto const g = Normalize(Shift(ga_hex, 8));
    return Color(g, g, g, Normalize(Shift(ga_hex, 0)));
  }

  static Color GrayAlpha(uint32_t g, uint32_t a) {
    return Color(Normalize(g), Normalize(g), Normalize(g), Normalize(a));
  }

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

  value_type& operator[](std::size_t i) {
    assert(i >= 0 && i < data_.size());
    return data()[i];
  }

  value_type operator[](std::size_t i) const {
    assert(i >= 0 && i < data_.size());
    return data()[i];
  }

  value_type* data() { return data_.data(); }
  const value_type* data() const { return data_.data(); }

  iterator begin() { return rgba_begin(); }
  const_iterator begin() const { return rgba_begin(); }
  iterator end() { return rgba_end(); }
  const_iterator end() const { return rgba_end(); }

  iterator rgb_begin() { return iterator(data()); }
  const_iterator rgb_begin() const { return const_iterator(data()); }
  iterator rgb_end() { return iterator(data() + 3); }
  const_iterator rgb_end() const { return const_iterator(data() + 3); }

  iterator rgba_begin() { return iterator(data()); }
  const_iterator rgba_begin() const { return const_iterator(data()); }
  iterator rgba_end() { return iterator(data() + 4); }
  const_iterator rgba_end() const { return const_iterator(data() + 4); }

  reverse_iterator rbegin() { return rgba_rbegin(); }
  const_reverse_iterator rbegin() const { return rgba_rbegin(); }
  reverse_iterator rend() { return rgba_rend(); }
  const_reverse_iterator rend() const { return rgba_rend(); }

  reverse_iterator rgb_rbegin() { return reverse_iterator(rgb_end()); }
  const_reverse_iterator rgb_rbegin() const {
    return const_reverse_iterator(rgb_end());
  }
  reverse_iterator rgb_rend() { return reverse_iterator(rgb_begin()); }
  const_reverse_iterator rgb_rend() const {
    return const_reverse_iterator(rgb_begin());
  }

  reverse_iterator rgba_rbegin() { return reverse_iterator(rgba_end()); }
  const_reverse_iterator rgba_rbegin() const {
    return const_reverse_iterator(rgba_end());
  }
  reverse_iterator rgba_rend() { return reverse_iterator(rgba_begin()); }
  const_reverse_iterator rgba_rend() const {
    return const_reverse_iterator(rgba_begin());
  }

  const_iterator cbegin() const { return rgba_cbegin(); }
  const_iterator cend() const { return rgba_cend(); }
  const_reverse_iterator crbegin() const { return rgba_crbegin(); }
  const_reverse_iterator crend() const { return rgba_crend(); }

  const_iterator rgb_cbegin() const { return rgb_begin(); }
  const_iterator rgb_cend() const { return rgb_end(); }
  const_reverse_iterator rgb_crbegin() const { return rgb_rbegin(); }
  const_reverse_iterator rgb_crend() const { return rgb_rend(); }

  const_iterator rgba_cbegin() const { return rgba_begin(); }
  const_iterator rgba_cend() const { return rgba_end(); }
  const_reverse_iterator rgba_crbegin() const { return rgba_rbegin(); }
  const_reverse_iterator rgba_crend() const { return rgba_rend(); }

  constexpr std::size_t size() const { return 4; }

  value_type r() const { return data_[0]; }
  void set_r(value_type r) { data_[0] = r; }
  value_type g() const { return data_[1]; }
  void set_g(value_type g) { data_[1] = g; }
  value_type b() const { return data_[2]; }
  void set_b(value_type b) { data_[2] = b; }
  value_type a() const { return data_[3]; }
  void set_a(value_type a) { data_[3] = a; }

  value_type r_hex() const { return Unnormalize(r()); }
  void set_r_hex(uint32_t r_hex) { set_r(Normalize(r_hex)); }
  value_type g_hex() const { return Unnormalize(g()); }
  void set_g_hex(uint32_t g_hex) { set_g(Normalize(g_hex)); }
  value_type b_hex() const { return Unnormalize(b()); }
  void set_b_hex(uint32_t b_hex) { set_b(Normalize(b_hex)); }
  value_type a_hex() const { return Unnormalize(a()); }
  void set_a_hex(uint32_t a_hex) { set_a(Normalize(a_hex)); }

  uint32_t rgb_hex() const {
    return Unshift(r_hex(), 16) | Unshift(g_hex(), 8) | Unshift(b_hex(), 0);
  }

  uint32_t rgba_hex() const {
    return Unshift(r_hex(), 24) | Unshift(g_hex(), 16) | Unshift(b_hex(), 8) |
           Unshift(a_hex(), 0);
  }

  void Fix() {
    for (int i = 0; i < 4; i++) {
      Clamp(0.0f, 1.0f, &data_[i]);
    }
  }

  // 颜色比较相等
  friend bool operator==(Color const& lhs, Color const& rhs) {
    for (int i = 0; i < 4; i++) {
      if (lhs[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  // 颜色比较不相等
  friend bool operator!=(Color const& lhs, Color const& rhs) {
    return !(lhs == rhs);
  }

  // 颜色加法
  Color& operator+=(Color const& rhs) {
    for (int i = 0; i < 4; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  // 颜色加法
  friend Color operator+(Color lhs, Color const& rhs) {
    lhs += rhs;
    return lhs;
  }

  // 颜色减法
  Color& operator-=(Color const& rhs) {
    for (int i = 0; i < 4; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  // 颜色减法
  friend Color operator-(Color lhs, Color const& rhs) {
    lhs -= rhs;
    return lhs;
  }

  // 颜色对常量乘法，调制
  Color& operator*=(value_type s) {
    for (int i = 0; i < 4; i++) {
      data_[i] *= s;
    }
    return *this;
  }

  // 颜色对常量乘法
  friend Color operator*(value_type s, Color v) {
    v *= s;
    return v;
  }

  // 颜色对常量乘法
  friend Color operator*(Color v, value_type s) {
    v *= s;
    return v;
  }

  // 颜色和颜色相乘，调制
  Color& operator*=(Color const& rhs) {
    for (int i = 0; i < 4; i++) {
      data_[i] *= rhs[i];
    }
    return *this;
  }

  // 颜色和颜色相乘，调制
  friend Color operator*(Color lhs, Color const& rhs) {
    lhs *= rhs;
    return lhs;
  }

  // 颜色对常量除法，调制
  Color& operator/=(value_type s) {
    for (int i = 0; i < 4; i++) {
      data_[i] /= s;
    }
    return *this;
  }

  // 颜色对常量除法
  friend Color operator/(Color v, value_type s) {
    v /= s;
    return v;
  }

 private:
  std::array<value_type, 4> data_{};
};

namespace colors {

inline Color const& Red() {
  static auto const c = Color::RGB(0xFF, 0x0, 0x0);
  return c;
}

inline Color const& Lime() {
  static auto const c = Color::RGB(0x0, 0xFF, 0x0);
  return c;
}

inline Color const& Green() {
  static auto const c = Color::RGB(0x0, 0x80, 0x0);
  return c;
}

inline Color const& Purple() {
  static auto const c = Color::RGB(0x80, 0x0, 0x80);
  return c;
}

inline Color const& Teal() {
  static auto const c = Color::RGB(0x0, 0x80, 0x80);
  return c;
}

inline Color const& Blue() {
  static auto const c = Color::RGB(0x0, 0x0, 0xFF);
  return c;
}

inline Color const& White() {
  static auto const c = Color::RGB(0xFF, 0xFF, 0xFF);
  return c;
}

inline Color const& Black() {
  static auto const c = Color::RGB(0x0, 0x0, 0x0);
  return c;
}

inline Color const& Yellow() {
  static auto const c = Color::RGB(0xFF, 0xFF, 0x0);
  return c;
}

inline Color const& Cyan() {
  static auto const c = Color::RGB(0x0, 0xFF, 0xFF);
  return c;
}

inline Color const& Magenta() {
  static auto const c = Color::RGB(0xFF, 0x0, 0xFF);
  return c;
}

inline Color SafeAdd(Color const& lhs, Color const& rhs) {
  Color ret{};
  for (int i = 0; i < 4; i++) {
    ret[i] = Clamp(0.0f, 1.0f, lhs[i] + rhs[i]);
  }
  return ret;
}

inline Color SafeSub(Color const& lhs, Color const& rhs) {
  Color ret{};
  for (int i = 0; i < 4; i++) {
    ret[i] = Clamp(0.0f, 1.0f, lhs[i] - rhs[i]);
  }
  return ret;
}

inline Color SafeMul(Color const& lhs, Color const& rhs) {
  Color ret{};
  for (int i = 0; i < 4; i++) {
    ret[i] = Clamp(0.0f, 1.0f, lhs[i] * rhs[i]);
  }
  return ret;
}

inline Color SafeMul(Color const& c, float s) {
  if (s < 0.0f) {
    return c;
  }
  if (s > 1.0f) {
    auto const maxv = std::max_element(c.rgb_begin(), c.rgb_end());
    auto const max_scaled = (*maxv) * s;
    if (max_scaled > 1.0f) {
      s = 1.0f / (*maxv);
    }
  }
  return Color(c.r() * s, c.g() * s, c.b() * s, c.a() * s);
}

inline Color GetFromData2D(Data2D const& data, Vector2 const& uv) {
  int const x = uv.x() * data.width();
  int const y = uv.y() * data.height();
  auto const buff = data.Get(x, y);
  switch (data.bytestep()) {
    case Color::kGrayScale:
      return Color::Gray(buff[0]);
    case Color::kGrayAlpha:
      return Color::GrayAlpha(buff[0], buff[1]);
    case Color::kRGB:
      return Color::RGB(buff[0], buff[1], buff[2]);
    case Color::kRGBA:
      return Color::RGBA(buff[0], buff[1], buff[2], buff[3]);
  }
  return Color{};
}

inline Color Blend(Color const& c1, Color const& c2) {
  auto const v1 = c1.a();
  auto const v2 = 1.0f - v1;
  return c1 * v1 + c2 * v2;
}

}  // namespace colors

}  // namespace sren
