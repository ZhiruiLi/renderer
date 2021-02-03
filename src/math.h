#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

namespace sren {

inline constexpr float kPI =
    3.14159265358979323846264338327950288419716939937510F;

template <class T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool> AlmostEqual(T x,
                                                                        T y) {
  return std::abs(x - y) <= std::numeric_limits<T>::epsilon();
}

}  // namespace sren
