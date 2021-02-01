#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

#include "math.h"

namespace sren {

// template <class T,
//           class = typename std::enable_if<!std::numeric_limits<T>::is_integer,
//                                           void>::type>
// struct Matrix {
//   T data[4][4]{};
// };
//
// using Matrixf = Matrix<float>;

}  // namespace sren
