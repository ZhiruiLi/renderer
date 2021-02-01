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
  using Inner = T[M];

  Inner &operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data[i];
  }


  Inner const &operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data[i];
  }

  T data[N][M]{};
};

template <class T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> const &lhs,
                          Matrix<T, N, M> const &rhs) {
  auto m = lhs;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      m[i][j] += rhs[i][j];
    }
  }
  return m;
}

}  // namespace sren
