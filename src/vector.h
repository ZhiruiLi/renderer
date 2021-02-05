#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <type_traits>

#include "math.h"

namespace sren {

namespace details {
// 是否存在 x 方法
constexpr bool HasX(std::size_t n) { return n >= 1 && n <= 4; }
// 是否存在 y 方法
constexpr bool HasY(std::size_t n) { return n >= 2 && n <= 4; }
// 是否存在 z 方法
constexpr bool HasZ(std::size_t n) { return n >= 3 && n <= 4; }
// 是否存在 w 方法
constexpr bool HasW(std::size_t n) { return n == 4; }
}  // namespace details

template <class T, std::size_t N,
          class = std::enable_if_t<!std::numeric_limits<T>::is_integer, void>>
struct Vector {
 public:
  using value_type = T;
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

  Vector() = default;

  explicit Vector(std::array<T, N> const& data) : data_{data} {}

  explicit Vector(Vector<T, N - 1> const& v, T last) {
    std::copy(v.begin(), v.end(), begin());
    back() = last;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 2>>
  Vector(float vx, float vy) : data_{vx, vy} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 3>>
  Vector(float vx, float vy, float vz) : data_{vx, vy, vz} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 4>>
  Vector(float vx, float vy, float vz, float vw = 1.0f)
      : data_{vx, vy, vz, vw} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  T operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  value_type* data() { return data_.data(); }
  const value_type* data() const { return data_.data(); }

  iterator begin() { return iterator(data()); }
  const_iterator begin() const { return const_iterator(data()); }
  iterator end() { return iterator(data() + N); }
  const_iterator end() const { return const_iterator(data() + N); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }
  const_reverse_iterator crbegin() const { return rbegin(); }
  const_reverse_iterator crend() const { return rend(); }

  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }
  reference back() { return data_[N - 1]; }
  const_reference back() const { return data_[N - 1]; }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), T> x() const {
    return data_[0];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), Vector>& set_x(T x) {
    return data_[0] = x;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T> y() const {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), Vector>& set_y(T y) {
    return data_[1] = y;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T> z() const {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), Vector>& set_z(T z) {
    return data_[2] = z;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T> w() const {
    return data_[3];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), Vector>& set_w(T w) {
    return data_[3] = w;
  }

  // 矢量比较相等
  friend bool operator==(Vector const& lhs, Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      if (!AlmostEqual(lhs[i], rhs[i])) {
        return false;
      }
    }
    return true;
  }

  // 矢量比较不相等
  friend bool operator!=(Vector const& lhs, Vector const& rhs) {
    return !(lhs == rhs);
  }

  // 矢量加法
  Vector& operator+=(Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  // 矢量加法
  friend Vector operator+(Vector lhs, Vector const& rhs) {
    lhs += rhs;
    return lhs;
  }

  // 矢量减法
  Vector& operator-=(Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  // 矢量减法
  friend Vector operator-(Vector lhs, Vector const& rhs) {
    lhs -= rhs;
    return lhs;
  }

  // 矢量对常量乘法
  Vector& operator*=(T s) {
    for (int i = 0; i < N; i++) {
      data_[i] *= s;
    }
    return *this;
  }

  // 矢量对常量乘法
  friend Vector operator*(T s, Vector v) {
    v *= s;
    return v;
  }

  // 矢量对常量乘法
  friend Vector operator*(Vector v, T s) {
    v *= s;
    return v;
  }

  // 矢量点乘
  friend T operator*(Vector const& lhs, Vector const& rhs) {
    T ret = 0;
    for (int i = 0; i < N; i++) {
      ret += lhs[i] * rhs[i];
    }
    return ret;
  }

  // 三维矢量叉乘
  template <std::size_t N1 = N>
  friend std::enable_if_t<N1 == 3, Vector> operator^(Vector const& lhs,
                                                     Vector const& rhs) {
    Vector v{};
    v.x = lhs.y * rhs.z - lhs.z * rhs.y;
    v.y = lhs.z * rhs.x - lhs.x * rhs.z;
    v.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return v;
  }

  // 矢量对常量的除法
  Vector& operator/=(T s) {
    for (int i = 0; i < N; i++) {
      data_[i] /= s;
    }
    return *this;
  }

  // 矢量对常量的除法
  friend Vector operator/(Vector v, T s) {
    v /= s;
    return v;
  }

  // 矢量输出到 ostream
  friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << "[";
    if (N > 0) {
      out << v[0];
    }
    for (int i = 1; i < N; i++) {
      out << "," << v[i];
    }
    out << "]";
    return out;
  }

  // 计算平方和
  T SquareMagnitude() const { return (*this) * (*this); }

  // 计算长度
  T Magnitude() const { return std::sqrtf(SquareMagnitude()); }

  // 对矢量的每一项都取倒数
  Vector& SetInverse() {
    for (int i = 0; i < N; i++) {
      data_[i] = 1.0f / data_[i];
    }
    return *this;
  }

  // 复制矢量并对矢量的每一项都取倒数
  Vector Inverse() const {
    Vector v = *this;
    v.SetInverse();
    return v;
  }

  // 对矢量的每一项都取绝对值
  Vector& SetAbs() {
    for (int i = 0; i < N; i++) {
      data_[i] = std::abs(data_[i]);
    }
    return *this;
  }

  // 复制矢量并对矢量的每一项都取绝对值
  Vector Abs() const {
    Vector v = *this;
    v.SetAbs();
    return v;
  }

  // 计算与另一个矢量的夹角
  T Angle(Vector const& rhs) const {
    return std::acos(
        std::min(1.0f, (*this) * rhs / (Magnitude() * rhs.Magnitude())));
  }

  // 将矢量归一化
  Vector& SetNormalize() { return (*this) /= Magnitude(); }

  // 复制矢量并将矢量归一化
  Vector Normalize() const { return (*this) / Magnitude(); }

 private:
  std::array<T, N> data_{};
};

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;

}  // namespace sren
