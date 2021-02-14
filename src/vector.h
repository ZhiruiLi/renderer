#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
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

  explicit Vector(T const* data) { std::copy(data, data + N, begin()); }

  explicit Vector(Vector<T, N - 1> const& v, T last) {
    std::copy(v.begin(), v.end(), begin());
    back() = last;
  }

  static Vector Fill(T value) {
    Vector ret{};
    std::fill(ret.begin(), ret.end(), value);
    return ret;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 2>>
  Vector(T vx, T vy) : data_{vx, vy} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 3>>
  Vector(T vx, T vy, T vz) : data_{vx, vy, vz} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 4>>
  Vector(T vx, T vy, T vz, T vw = 1.0f) : data_{vx, vy, vz, vw} {}

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
    data_[0] = x;
    return *this;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T> y() const {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), Vector>& set_y(T y) {
    data_[1] = y;
    return *this;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T> z() const {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), Vector>& set_z(T z) {
    data_[2] = z;
    return *this;
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T> w() const {
    return data_[3];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), Vector>& set_w(T w) {
    data_[3] = w;
    return *this;
  }

  Vector& Set(T const* data) {
    for (int i = 0; i < N; i++) {
      data_[i] = data[i];
    }
    return *this;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 2>>
  Vector& Set(T vx, T vy) {
    set_x(vx);
    set_y(vy);
    return *this;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 3>>
  Vector& Set(T vx, T vy, T vz) {
    set_x(vx);
    set_y(vy);
    set_z(vz);
    return *this;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 4>>
  Vector& Set(T vx, T vy, T vz, T vw = 1.0f) {
    set_x(vx);
    set_y(vy);
    set_z(vz);
    set_w(vw);
    return *this;
  }

  // 两个矢量几乎相等
  bool AlmostEqual(Vector const& rhs, T epsilon) const {
    auto const m = ((*this) - rhs).SquareMagnitude();
    return m <= epsilon * epsilon;
  }

  // 两个矢量几乎相等
  bool AlmostEqual(Vector const& rhs) const {
    return AlmostEqual(rhs, std::numeric_limits<T>::epsilon());
  }

  // 矢量比较相等
  friend bool operator==(Vector const& lhs, Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      if (lhs[i] != rhs[i]) {
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
    v.set_x(lhs.y() * rhs.z() - lhs.z() * rhs.y());
    v.set_y(lhs.z() * rhs.x() - lhs.x() * rhs.z());
    v.set_z(lhs.x() * rhs.y() - lhs.y() * rhs.x());
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

  // 计算向量到向量的投影
  Vector<T, N> ProjectTo(Vector<T, N> const& v) const {
    return (*this) * v / SquareMagnitude() * (*this);
  }

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

  // 将矢量归一化
  Vector& SetNormalize() {
    auto const m = SquareMagnitude();
    return (*this) *= SafeInverseSqrt(m);
  }

  // 复制矢量并将矢量归一化
  Vector Normalize() const {
    auto const m = SquareMagnitude();
    return (*this) * SafeInverseSqrt(m);
  }

  // 对应位置缩放
  Vector& SetScale(Vector const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] *= rhs[i];
    }
    return *this;
  }

  // 对应位置缩放
  Vector Scale(Vector const& rhs) const {
    Vector ret = *this;
    ret.SetScale(rhs);
    return ret;
  }

  // 返回每一项都为 0 的矢量
  static Vector const& Zero() {
    static Vector const v{};
    return v;
  }

  // 返回每一项都无穷大的矢量
  static Vector const& Infinty() {
    static Vector const v = Fill(std::numeric_limits<T>::infinity());
    return v;
  }

  // 检查一个矢量是否是归一化的
  bool IsNormalized() const {
    return ::sren::AlmostEqual(SquareMagnitude(), 1.0f);
  }

  // 检查一个矢量是否是归一化的
  bool IsNormalized(T epsilon) const {
    return ::sren::AlmostEqual(SquareMagnitude(), 1.0f, epsilon);
  }

 private:
  std::array<T, N> data_{};
};

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;

namespace vectors {

// 求两个矢量每一个位置的值的最小值构成的矢量
template <class T, std::size_t N>
inline Vector<T, N> Min(Vector<T, N> lhs, Vector<T, N> const& rhs) {
  Vector<T, N> ret{};
  for (int i = 0; i < N; i++) {
    ret[i] = std::min(lhs[i], rhs[i]);
  }
  return ret;
}

// 求两个矢量每一个位置的值的最大值构成的矢量
template <class T, std::size_t N>
inline Vector<T, N> Max(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  Vector<T, N> ret{};
  for (int i = 0; i < N; i++) {
    ret[i] = std::max(lhs[i], rhs[i]);
  }
  return ret;
}

// 计算与另一个矢量的夹角
template <class T, std::size_t N>
inline T Angle(Vector<T, N> const& lhs, Vector<T, N> const& rhs) {
  return std::acos(
      std::min(1.0f, lhs * rhs / (lhs.Magnitude() * rhs.Magnitude())));
}

// 检查点 p 是否在 p1-p2 构成的直线的左侧
template <class T, std::size_t N>
inline std::enable_if_t<details::HasX(N) && details::HasY(N), bool> LeftOfLine(
    Vector<T, N> const& p, Vector<T, N> const& p1, Vector<T, N> const& p2) {
  auto const tmpx =
      (p1.x() - p2.x()) / (p1.y() - p2.y()) * (p.y() - p2.y()) + p2.x();
  if (tmpx > p.x()) {
    return true;
  }
  return false;
}

}  // namespace vectors

}  // namespace sren
