#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

#include "math.h"
#include "vector.h"

namespace sren {

template <class T, std::size_t N, std::size_t M,
          class = std::enable_if_t<!std::numeric_limits<T>::is_integer, void>>
struct Matrix {
  using Row = std::array<T, M>;
  using value_type = T;
  using reference = value_type &;
  using const_reference = value_type const &;
  using iterator = value_type *;
  using const_iterator = value_type const *;
  using pointer = value_type *;
  using const_pointer = value_type const *;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Matrix() = default;

  template <
      std::size_t N1, std::size_t M1, std::size_t N2 = N, std::size_t M2 = M,
      class = std::enable_if_t<N1 <= N2 && M1 <= M2 && N1 == M1 && N2 == M2>>
  explicit Matrix(Matrix<T, N1, M1> const &m) {
    for (int i = 0; i < N1; i++) {
      for (int j = 0; j < M1; j++) {
        data_[i][j] = m[i][j];
      }
    }
    for (int i = N1; i < N2; i++) {
      data_[i][i] = 1;
    }
  }

  explicit Matrix(std::array<Row, N> const &arr) : data_{arr} {}

  explicit Matrix(T const *data) { std::copy(data, data + N * M, begin()); }

  Row &operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  Row const &operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  value_type *data() { return &data_[0][0]; }
  const value_type *data() const { return &data_[0][0]; }

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

  T const &Get(int i, int j) const {
    assert(i >= 0 && i < N && j >= 0 && j < M);
    return data_[i][j];
  }

  Matrix &Set(int i, int j, T v) {
    assert(i >= 0 && i < N && j >= 0 && j < M);
    data_[i][j] = v;
    return *this;
  }

  // 将矩阵设为 0 矩阵
  Matrix &SetZero() { return SetAll(0.0f); }

  // 获取 0 矩阵
  static Matrix const &Zero() {
    static Matrix ret{};
    return ret;
  }

  // 将矩阵每个值都设为给定值
  Matrix &SetAll(T x) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data_[i][j] = x;
      }
    }
    return *this;
  }

  // 获取单位矩阵
  template <std::size_t N1 = N, std::size_t M1 = M>
  std::enable_if_t<N1 == M1, bool> IsIdentity() const {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (i == j) {
          if (!sren::AlmostEqual(data_[i][j], T(1))) {
            return false;
          }
        } else {
          if (!sren::AlmostEqual(data_[i][j], T(0))) {
            return false;
          }
        }
      }
    }
    return true;
  }

  // 获取单位矩阵
  template <std::size_t N1 = N, std::size_t M1 = M>
  std::enable_if_t<N1 != M1, bool> const &IsIdentity() const {
    return false;
  }

  // 将矩阵设为单位矩阵
  template <std::size_t N1 = N, std::size_t M1 = M>
  std::enable_if_t<N1 == M1> SetIdentity() {
    for (int i = 0; i < N; i++) {
      data_[i][i] = T(1);
    }
  }

  // 获取单位矩阵
  template <std::size_t N1 = N, std::size_t M1 = M>
  static std::enable_if_t<N1 == M1, Matrix> const &Identity() {
    static Matrix ret = IdentityCopy();
    return ret;
  }

  // 比较矩阵相等
  friend bool operator==(Matrix const &lhs, Matrix const &rhs) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (!AlmostEqual(lhs[i][j], rhs[i][j])) {
          return false;
        }
      }
    }
    return true;
  }

  // 比较矩阵不相等
  friend bool operator!=(Matrix const &lhs, Matrix const &rhs) {
    return !(lhs == rhs);
  }

  // 矩阵加法
  Matrix &operator+=(Matrix const &rhs) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data_[i][j] += rhs[i][j];
      }
    }
    return *this;
  }

  // 矩阵加法
  friend Matrix operator+(Matrix lhs, Matrix const &rhs) {
    lhs += rhs;
    return lhs;
  }

  // 矩阵减法
  Matrix &operator-=(Matrix const &rhs) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data_[i][j] -= rhs[i][j];
      }
    }
    return *this;
  }

  // 矩阵减法
  friend Matrix operator-(Matrix lhs, Matrix const &rhs) {
    lhs -= rhs;
    return lhs;
  }

  // 用矩阵对矢量进行变换
  friend Vector<T, M> operator*(Vector<T, N> const &v, Matrix const &m) {
    Vector<T, M> ret{};
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        ret[i] += v[j] * m[j][i];
      }
    }
    return ret;
  }

  // 矩阵乘法
  template <std::size_t N1>
  friend Matrix<T, N, N1> operator*(Matrix<T, N, M> const &lhs,
                                    Matrix<T, M, N1> const &rhs) {
    Matrix<T, N, N1> ret{};
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N1; j++) {
        for (int k = 0; k < M; k++) {
          ret[i][j] += lhs[i][k] * rhs[k][j];
        }
      }
    }
    return ret;
  }

  // 矩阵乘法，修改矩阵本身，因此要求变化后列数相同
  template <std::size_t M1 = M>
  std::enable_if_t<M1 == M, Matrix> &operator*=(Matrix<T, M1, M1> const &rhs) {
    *this = (*this) * rhs;
    return *this;
  }

  // 矩阵对常量的乘法
  Matrix &operator*=(T s) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data_[i][j] *= s;
      }
    }
    return *this;
  }

  // 矩阵对常量的乘法
  friend Matrix operator*(Matrix m, T s) {
    m *= s;
    return m;
  }

  // 矩阵对常量的除法
  Matrix &operator/=(T s) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        data_[i][j] /= s;
      }
    }
    return *this;
  }

  // 矩阵对常量的除法
  friend Matrix operator/(Matrix m, T s) {
    m /= s;
    return m;
  }

  // 矩阵输出到 ostream
  friend std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    out << "[";
    for (int i = 0; i < N; i++) {
      if (i != 0) {
        out << ",";
      }
      out << "[";
      for (int j = 0; j < M; j++) {
        if (i != 0) {
          out << ",";
        }
        out << m[i][j];
      }
      out << "]";
    }
    out << "]";
    return out;
  }

  // 将矩阵转置，只对方阵有效
  template <std::size_t N1 = N, std::size_t M1 = M>
  std::enable_if_t<N1 == M1, Matrix> &SetTransform() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        std::swap(data_[i][j], data_[j][i]);
      }
    }
    return *this;
  }

  // 计算转置矩阵
  Matrix<T, M, N> Transform() const {
    Matrix<T, M, N> ret{};
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        ret[j][i] = data_[i][j];
      }
    }
    return *this;
  }

 private:
  template <std::size_t N1 = N, std::size_t M1 = M>
  static std::enable_if_t<N1 == M1, Matrix> IdentityCopy() {
    Matrix ret{};
    ret.SetIdentity();
    return ret;
  }

  std::array<Row, N> data_{};
};

using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

namespace matrixs {

template <class T>
inline Matrix<T, 4, 4> WorldTransform(Vector<T, 3> const &pos) {
  return Matrix<T, 4, 4>({{
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {pos.x(), pos.y(), pos.z(), 1},
  }});
}

template <class T>
inline Matrix<T, 4, 4> ViewTransform(Vector<T, 3> const &pos,
                                     Vector<T, 3> const &target,
                                     Vector<T, 3> const &up = {0, 1, 0}) {
  auto const n = (target - pos).Normalize();
  auto const u = (up ^ n).Normalize();
  auto const v = n ^ u;
  return Matrix4x4({{
      {u.x(), v.x(), n.x(), 0.0f},
      {u.y(), v.y(), n.y(), 0.0f},
      {u.z(), v.z(), n.z(), 0.0f},
      {-(pos * u), -(pos * v), -(pos * n), 1.0f},
  }});
}

template <class T>
inline Matrix<T, 4, 4> ProjectionTransform(T aspect, T fov_radian_v,
                                           T near_clip, T far_clip) {
  auto const theta = fov_radian_v / 2;
  auto const cot_theta = 1 / tan(theta);
  return Matrix4x4({{
      {cot_theta / aspect, 0.0f, 0.0f, 0.0f},
      {0.0f, cot_theta, 0.0f, 0.0f},
      {0.0f, 0.0f, far_clip / (far_clip - near_clip), 1.0f},
      {0.0f, 0.0f, far_clip * near_clip / (near_clip - far_clip), 0.0f},
  }});
}

}  // namespace matrixs

}  // namespace sren
