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
  Matrix(std::array<std::array<T, M>, N> const &arr) : data{arr} {}

  std::array<T, M> &operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data[i];
  }

  std::array<T, M> const &operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data[i];
  }

  template <std::size_t N1 = N, std::size_t M1 = M>
  std::enable_if_t<N1 == M1> SetIdentity() {
    for (int i = 0; i < N; i++) {
      data[i][i] = T(1);
    }
  }

  template <std::size_t N1 = N, std::size_t M1 = M>
  static std::enable_if_t<N1 == M1, Matrix> const &Identity() {
    static Matrix ret = IdentityCopy();
    return ret;
  }

 private:
  template <std::size_t N1 = N, std::size_t M1 = M>
  static std::enable_if_t<N1 == M1, Matrix> IdentityCopy() {
    Matrix ret{};
    ret.SetIdentity();
    return ret;
  }

  std::array<std::array<T, M>, N> data{};
};

using Matrix3x3 = Matrix<float, 3, 3>;
using Matrix4x4 = Matrix<float, 4, 4>;

template <class T, std::size_t N, std::size_t M>
bool operator==(Matrix<T, N, M> const &lhs, Matrix<T, N, M> const &rhs) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!AlmostEqual(lhs[i][j], rhs[i][j])) {
        return false;
      }
    }
  }
  return true;
}

template <class T, std::size_t N, std::size_t M>
bool operator!=(Matrix<T, N, M> const &lhs, Matrix<T, N, M> const &rhs) {
  return !(lhs == rhs);
}

template <class T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> const &lhs,
                          Matrix<T, N, M> const &rhs) {
  auto ret = lhs;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ret[i][j] += rhs[i][j];
    }
  }
  return ret;
}

template <class T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> const &lhs,
                          Matrix<T, N, M> const &rhs) {
  auto ret = lhs;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ret[i][j] -= rhs[i][j];
    }
  }
  return ret;
}

template <class T, std::size_t N1, std::size_t M, std::size_t N2>
Matrix<T, N1, N2> operator*(Matrix<T, N1, M> const &lhs,
                            Matrix<T, M, N2> const &rhs) {
  Matrix<T, N1, N2> ret{};
  for (int i = 0; i < N1; i++) {
    for (int j = 0; j < N2; j++) {
      for (int k = 0; k < M; k++) {
        ret[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }
  return ret;
}

template <class T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator*(Matrix<T, N, M> const &lhs, T s) {
  auto ret = lhs;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ret[i][j] *= s;
    }
  }
  return ret;
}

template <class T, std::size_t N, std::size_t M>
Vector<T, M> operator*(Vector<T, N> const &v, Matrix<T, N, M> const &m) {
  Vector<T, M> ret{};
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      ret[i] += v[j] * m[j][i];
    }
  }
  return ret;
}

template <class T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator/(Matrix<T, N, M> const &lhs, T s) {
  auto ret = lhs;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ret[i][j] /= s;
    }
  }
  return ret;
}

}  // namespace sren
