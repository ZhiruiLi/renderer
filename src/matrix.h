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
  Matrix() = default;
  Matrix(std::array<std::array<T, M>, N> const &arr) : data_{arr} {}

  std::array<T, M> &operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  std::array<T, M> const &operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data_[i];
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

  std::array<std::array<T, M>, N> data_{};
};

using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

}  // namespace sren
