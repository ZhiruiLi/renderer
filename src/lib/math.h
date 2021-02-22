#pragma once

#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

namespace sren {

constexpr float kPI = 3.14159265358979323846264338327950288419716939937510F;

template <class T>
inline std::enable_if_t<!std::numeric_limits<T>::is_integer, bool> AlmostEqual(
    T x, T y, T epsilon) {
  return std::abs(x - y) <= epsilon;
}

template <class T>
inline std::enable_if_t<!std::numeric_limits<T>::is_integer, bool> AlmostEqual(
    T x, T y) {
  return AlmostEqual(x, y, std::numeric_limits<T>::epsilon());
}

inline float SafeInverseSqrt(float f) {
  if (std::abs(f) == 0.0f) return f;
  return 1.0F / std::sqrt(f);
}

template <class T>
inline void ClampInPlace(T lo, T hi, T *target) {
  if (*target < lo) {
    *target = lo;
  } else if (*target > hi) {
    *target = hi;
  }
}

template <class T>
inline T Clamp(T lo, T hi, T target) {
  return std::min(hi, std::max(lo, target));
}

template <class T>
inline T Radian(T angle) {
  return angle / T(180) * T(kPI);
}

}  // namespace sren
