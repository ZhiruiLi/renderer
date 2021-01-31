#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "math.h"

namespace sren {

template <int N>
struct Vector {
  Vector() = default;

  float& operator[](int i) {
    assert(i >= 0 && i < N);
    return data[i];
  }

  float operator[](int i) const {
    assert(i >= 0 && i < N);
    return data[i];
  }

  float data[N] = {0};
};

template <int N>
Vector<N> operator==(Vector<N> const& lhs, Vector<N> const& rhs) {
  Vector<N> ret = lhs;
  for (int i = 0; i < N; i++) {
    ret[i] += rhs[i];
  }
  return ret;
}

template <int N>
float operator*(Vector<N> const& lhs, Vector<N> const& rhs) {
  float ret = 0;
  for (int i = 0; i < N; i++) {
    ret += lhs[i] * rhs[i];
  }
  return ret;
}

template <int N>
Vector<N> operator+(Vector<N> const& lhs, Vector<N> const& rhs) {
  Vector<N> ret = lhs;
  for (int i = 0; i < N; i++) {
    ret[i] += rhs[i];
  }
  return ret;
}

template <int N>
Vector<N> operator-(Vector<N> const& lhs, Vector<N> const& rhs) {
  Vector<N> ret = lhs;
  for (int i = 0; i < N; i++) {
    ret[i] -= rhs[i];
  }
  return ret;
}

template <int N>
Vector<N> operator*(float f, Vector<N> const& v) {
  Vector<N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] *= f;
  }
  return ret;
}

template <int N>
Vector<N> operator*(Vector<N> const& v, float f) {
  Vector<N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] *= f;
  }
  return ret;
}

template <int N>
Vector<N> operator/(Vector<N> const& v, float f) {
  Vector<N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] /= f;
  }
  return ret;
}

template <int N>
std::ostream& operator<<(std::ostream& out, const Vector<N>& v) {
  out << "(";
  if (N > 0) {
    out << v[0];
  }
  for (int i = 1; i < N; i++) {
    out << ", " << v[i];
  }
  out << ")";
  return out;
}

template <int N>
inline float SquareMagnitude(Vector<N> const& v) {
  return v * v;
}

template <int N>
inline float Magnitude(Vector<N> const& v) {
  return std::sqrtf(SquareMagnitude(v));
}

template <int N>
inline Vector<N> Inverse(Vector<N> const& v) {
  Vector<N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = 1.0f / ret[i];
  }
  return ret;
}

template <int N>
inline Vector<N> Abs(Vector<N> const& v) {
  Vector<N> ret = v;
  for (int i = 0; i < N; i++) {
    ret[i] = std::fabs(ret[i]);
  }
  return ret;
}

template <int N>
inline float Angle(Vector<N> const& l, Vector<N> const& r) {
  return std::acos(std::min(1.0f, l * r / (Magnitude(l) * Magnitude(r))));
}

template <int N>
inline Vector<N> Normalize(Vector<N> const & v) { return v / Magnitude(v); }

}  // namespace sren
