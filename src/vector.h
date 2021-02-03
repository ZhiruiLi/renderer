#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
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
  Vector() = default;

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 2>>
  Vector(float vx, float vy) : data_{vx, vy} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 3>>
  Vector(float vx, float vy, float vz) : data_{vx, vy, vz} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 4>>
  Vector(float vx, float vy, float vz, float vw) : data_{vx, vy, vz, vw} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  T operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), T> x() const {
    return data_[0];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), T>& x() {
    return data_[0];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T> y() const {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T>& y() {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T> z() const {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T>& z() {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T> w() const {
    return data_[3];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T>& w() {
    return data_[3];
  }

  // 矢量比较
  friend bool operator==(Vector const& lhs, Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      if (!AlmostEqual(lhs[i], rhs[i])) {
        return false;
      }
    }
    return true;
  }

  // 矢量比较
  friend bool operator!=(Vector const& lhs, Vector const& rhs) {
    return !(lhs == rhs);
  }

  // 矢量加法
  Vector& operator+=(Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] += rhs.data_[i];
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
      data_[i] -= rhs.data_[i];
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

  friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << "(";
    if (N > 0) {
      out << v[0];
    }
    for (int i = 1; i < N; i++) {
      out << ", " << v[i];
    }
    out << ")";
    return out;
  }

 private:
  T data_[N] = {0};
};

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;

template <class T, std::size_t N>
inline T SquareMagnitude(Vector<T, N> const& v) {
  return v * v;
}

template <class T, std::size_t N>
inline T Magnitude(Vector<T, N> const& v) {
  return std::sqrtf(SquareMagnitude(v));
}

template <class T, std::size_t N>
inline Vector<T, N> Inverse(Vector<T, N> const& v) {
  auto ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = 1.0f / ret[i];
  }
  return ret;
}

template <class T, std::size_t N>
inline Vector<T, N> Abs(Vector<T, N> const& v) {
  auto ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = std::abs(ret[i]);
  }
  return ret;
}

template <class T, std::size_t N>
inline T Angle(Vector<T, N> const& l, Vector<T, N> const& r) {
  return std::acos(std::min(1.0f, l * r / (Magnitude(l) * Magnitude(r))));
}

template <class T, std::size_t N>
inline Vector<T, N> Normalize(Vector<T, N> const& v) {
  return v / Magnitude(v);
}

}  // namespace sren
