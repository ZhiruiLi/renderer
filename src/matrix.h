#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

#include "math.h"
#include "vector.h"

namespace sren {

template <class T, std::size_t N, std::size_t M,
          class = typename std::enable_if<!std::numeric_limits<T>::is_integer,
                                          void>::type>
struct Matrix {
  Vector<T, M> &operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data[i];
  }

  Vector<T, M> const &operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data[i];
  }

  static typename std::enable_if<N == M, Matrix>::type const &Identity() {
    static Matrix ret = IdentityCopy();
    return ret;
  }

  Vector<T, M> data[N]{};

 private:
  static typename std::enable_if<N == M, Matrix>::type IdentityCopy() {
    Matrix ret{};
    for (int i = 0; i < N; i++) {
      ret[i][i] = T(1);
    }
    return ret;
  }
};

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
