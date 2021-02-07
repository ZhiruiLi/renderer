#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

#include "math.h"
#include "point.h"
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

  explicit Matrix(std::array<Row, N> const &arr) : data_{arr} {}

  explicit Matrix(T const *data) { std::copy(data, data + N, begin()); }

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

  // 用矩阵对点进行变换
  friend Point<T, M> operator*(Point<T, N> const &v, Matrix const &m) {
    Point<T, M> ret{};
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

}  // namespace sren
