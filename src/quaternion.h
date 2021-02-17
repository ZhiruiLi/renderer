#pragma once

#include <array>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <type_traits>

#include "math.h"
#include "vector.h"

namespace sren {

template <class T,
          class = std::enable_if_t<!std::numeric_limits<T>::is_integer, void>>
class Quaternion {
 public:
  enum {
    N = 4,
  };

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

  Quaternion() = default;

  Quaternion(T a, T b, T c, T d) : data_{a, b, c, d} {}

  Quaternion(T real, Vector<T, 3> const& imag)
      : data_{real, imag.x(), imag.y(), imag.z()} {}

  Quaternion(T real, std::array<T, 3> const& imag)
      : data_{real, imag.x(), imag.y(), imag.z()} {}

  Quaternion(T real, T const* imag) : data_{real, imag[0], imag[1], imag[2]} {}

  explicit Quaternion(std::array<T, N> const& data) : data_{data} {}

  explicit Quaternion(T const* data) { std::copy(data, data + N, begin()); }

  static Quaternion Pure(Vector<T, 3> const& imag) {
    return Quaternion(0, imag.x(), imag.y(), imag.z());
  }

  static Quaternion Rotate(Vector<T, 3> const& axis, T theta) {
    auto const half_theta = theta / 2;
    return Quaternion(std::cos(half_theta), axis * std::sin(half_theta))
        .Normalize();
  }

  static Quaternion Fill(T value) {
    Quaternion ret{};
    std::fill(ret.begin(), ret.end(), value);
    return ret;
  }

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

  constexpr std::size_t size() const { return N; }

  T a() const { return data_[0]; }

  Quaternion& set_a(T a) {
    data_[0] = a;
    return *this;
  }

  T b() const { return data_[1]; }

  Quaternion& set_b(T b) {
    data_[1] = b;
    return *this;
  }

  T c() const { return data_[2]; }

  Quaternion& set_c(T c) {
    data_[2] = c;
    return *this;
  }

  T d() const { return data_[3]; }

  Quaternion set_d(T d) {
    data_[3] = d;
    return *this;
  }

  Quaternion& Set(T const* data) {
    for (int i = 0; i < N; i++) {
      data_[i] = data[i];
    }
    return *this;
  }

  Quaternion& Set(T a, T b, T c, T d) {
    set_a(a);
    set_b(b);
    set_c(c);
    set_d(d);
    return *this;
  }

  // 两个四元数几乎相等
  bool AlmostEqual(Quaternion const& rhs, T epsilon) const {
    auto const m = ((*this) - rhs).SquareMagnitude();
    return m <= epsilon * epsilon;
  }

  // 两个四元数几乎相等
  bool AlmostEqual(Quaternion const& rhs) const {
    return AlmostEqual(rhs, std::numeric_limits<T>::epsilon());
  }

  // 四元数反向
  friend Quaternion operator-(Quaternion const& v) { return Zero() - v; }

  // 四元数比较相等
  friend bool operator==(Quaternion const& lhs, Quaternion const& rhs) {
    for (int i = 0; i < N; i++) {
      if (lhs[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  // 四元数比较不相等
  friend bool operator!=(Quaternion const& lhs, Quaternion const& rhs) {
    return !(lhs == rhs);
  }

  // 四元数加法
  Quaternion& operator+=(Quaternion const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  // 四元数加法
  friend Quaternion operator+(Quaternion lhs, Quaternion const& rhs) {
    lhs += rhs;
    return lhs;
  }

  // 四元数减法
  Quaternion& operator-=(Quaternion const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  // 四元数减法
  friend Quaternion operator-(Quaternion lhs, Quaternion const& rhs) {
    lhs -= rhs;
    return lhs;
  }

  // 四元数对常量乘法
  Quaternion& operator*=(T s) {
    for (int i = 0; i < N; i++) {
      data_[i] *= s;
    }
    return *this;
  }

  // 四元数对常量乘法
  friend Quaternion operator*(T s, Quaternion v) {
    v *= s;
    return v;
  }

  // 四元数对常量乘法
  friend Quaternion operator*(Quaternion v, T s) {
    v *= s;
    return v;
  }

  Quaternion& operator*=(Quaternion const& rhs) {
    *this = *this * rhs;
    return *this;
  }

  // 四元数乘法
  friend Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs) {
    return Quaternion(lhs.a() * rhs.a() - lhs.b() * rhs.b() -
                          lhs.c() * rhs.c() - lhs.d() * rhs.d(),
                      lhs.b() * rhs.a() + lhs.a() * rhs.b() -
                          lhs.d() * rhs.c() + lhs.c() * rhs.d(),
                      lhs.c() * rhs.a() + lhs.d() * rhs.b() +
                          lhs.a() * rhs.c() - lhs.b() * rhs.d(),
                      lhs.d() * rhs.a() - lhs.c() * rhs.b() +
                          lhs.b() * rhs.c() + lhs.a() * rhs.d());
  }

  // 四元数对常量的除法
  Quaternion& operator/=(T s) {
    for (int i = 0; i < N; i++) {
      data_[i] /= s;
    }
    return *this;
  }

  // 四元数对常量的除法
  friend Quaternion operator/(Quaternion v, T s) {
    v /= s;
    return v;
  }

  // 四元数输出到 ostream
  friend std::ostream& operator<<(std::ostream& out, const Quaternion& v) {
    return out << "(" << v.a() + "," << v.b() << "," << v.c() << "," << v.d()
               << ")";
  }

  // 计算平方和
  T SquareMagnitude() const {
    return a() * a() + b() * b() + c() * c() + d() * d();
  }

  // 计算长度
  T Magnitude() const { return std::sqrtf(SquareMagnitude()); }

  // 对四元数的每一项都取倒数
  Quaternion& SetInverse() {
    for (int i = 0; i < N; i++) {
      data_[i] = 1.0f / data_[i];
    }
    return *this;
  }

  // 复制四元数并对四元数的每一项都取倒数
  Quaternion Inverse() const {
    Quaternion v = *this;
    v.SetInverse();
    return v;
  }

  // 对四元数的每一项都取绝对值
  Quaternion& SetAbs() {
    for (int i = 0; i < N; i++) {
      data_[i] = std::abs(data_[i]);
    }
    return *this;
  }

  // 复制四元数并对四元数的每一项都取绝对值
  Quaternion Abs() const {
    Quaternion v = *this;
    v.SetAbs();
    return v;
  }

  // 将四元数归一化
  Quaternion& SetNormalize() {
    auto const m = SquareMagnitude();
    return (*this) *= SafeInverseSqrt(m);
  }

  // 复制四元数并将四元数归一化
  Quaternion Normalize() const {
    auto const m = SquareMagnitude();
    return (*this) * SafeInverseSqrt(m);
  }

  // 对应位置缩放
  Quaternion& SetScale(Quaternion const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] *= rhs[i];
    }
    return *this;
  }

  // 对应位置缩放
  Quaternion Scale(Quaternion const& rhs) const {
    Quaternion ret = *this;
    ret.SetScale(rhs);
    return ret;
  }

  // 返回每一项都为 0 的四元数
  static Quaternion const& Zero() {
    static Quaternion const v{};
    return v;
  }

  // 返回每一项都无穷大的四元数
  static Quaternion const& Infinty() {
    static Quaternion const v = Fill(std::numeric_limits<T>::infinity());
    return v;
  }

  // 检查一个四元数是否是归一化的
  bool IsNormalized() const {
    return ::sren::AlmostEqual(SquareMagnitude(), 1.0f);
  }

  // 检查一个四元数是否是归一化的
  bool IsNormalized(T epsilon) const {
    return ::sren::AlmostEqual(SquareMagnitude(), 1.0f, epsilon);
  }

  // 四元数的共轭
  Quaternion Conjugation() const { return Quaternion(a(), -b(), -c(), -d()); }

  // 将四元数设为共轭
  Quaternion& SetConjugation() {
    for (int i = 1; i < N; i++) {
      data_[i] = -data_[i];
    }
    return *this;
  }

  Vector<T, 3> ImagPart() const { return {b(), c(), d()}; }

  Vector<T, 3> RotateVector(Vector<T, 3> const& v) const {
    return ((*this) * Pure(v) * Conjugation()).ImagPart();
  }

 private:
  std::array<T, 4> data_{};
};

using Quaternionf = Quaternion<float>;

}  // namespace sren
