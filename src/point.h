#pragma once

#include "vector.h"

namespace sren {

template <class T, std::size_t N,
          class = std::enable_if_t<!std::numeric_limits<T>::is_integer, void>>
struct Point {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = value_type*;
  using const_iterator = value_type const*;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Point() = default;

  explicit Point(std::array<T, N> const& data) : data_{data} {}

  explicit Point(Point<T, N - 1> const& v, T last) {
    std::copy(v.begin(), v.end(), begin());
    back() = last;
  }

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 2>>
  Point(float vx, float vy) : data_{vx, vy} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 3>>
  Point(float vx, float vy, float vz) : data_{vx, vy, vz} {}

  template <std::size_t N1 = N, class = std::enable_if_t<N1 == 4>>
  Point(float vx, float vy, float vz, float vw) : data_{vx, vy, vz, vw} {}

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  T operator[](std::size_t i) const {
    assert(i >= 0 && i < N);
    return data_[i];
  }

  value_type* data() { return data_.data(); }
  const value_type* data() const { return data_.data(); }

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

  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }
  reference back() { return data_[N - 1]; }
  const_reference back() const { return data_[N - 1]; }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), T> x() const {
    return data_[0];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasX(N1), T>& x() {
    return data_[0];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T> y() const {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasY(N1), T>& y() {
    return data_[1];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T> z() const {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasZ(N1), T>& z() {
    return data_[2];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T> w() const {
    return data_[3];
  }

  template <std::size_t N1 = N>
  std::enable_if_t<details::HasW(N1), T>& w() {
    return data_[3];
  }

  // 位置比较相等
  friend bool operator==(Point const& lhs, Point const& rhs) {
    for (int i = 0; i < N; i++) {
      if (!AlmostEqual(lhs[i], rhs[i])) {
        return false;
      }
    }
    return true;
  }

  // 矢量比较不相等
  friend bool operator!=(Point const& lhs, Point const& rhs) {
    return !(lhs == rhs);
  }

  // 点对矢量的加法
  Point& operator+=(Vector<T, N> const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  // 点对矢量的加法
  friend Point operator+(Point lhs, Vector<T, N> const& rhs) {
    lhs += rhs;
    return lhs;
  }

  // 点对矢量的加法
  friend Point operator+(Vector<T, N> const& lhs, Point rhs) {
    rhs += lhs;
    return rhs;
  }

  // 点对矢量的减法
  Point& operator-=(Vector<T, N> const& rhs) {
    for (int i = 0; i < N; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  // 点对矢量的减法
  friend Point operator-(Point lhs, Vector<T, N> const& rhs) {
    lhs -= rhs;
    return lhs;
  }

  // 点对矢量的减法
  friend Point operator-(Vector<T, N> const& lhs, Point rhs) {
    rhs -= lhs;
    return rhs;
  }

  // 两点减法，获得一个矢量
  friend Vector<T, N> operator-(Point const& lhs, Point const& rhs) {
    Vector<T, N> ret{lhs.data_};
    for (int i = 0; i < N; i++) {
      ret[i] -= rhs[i];
    }
    return ret;
  }

  // 点输出到 ostream
  friend std::ostream& operator<<(std::ostream& out, const Point& v) {
    out << "(";
    if (N > 0) {
      out << v[0];
    }
    for (int i = 1; i < N; i++) {
      out << "," << v[i];
    }
    out << ")";
    return out;
  }

  // 原点
  static Point const& Zero() {
    static const Point p{};
    return p;
  }

 private:
  std::array<T, N> data_{};
};

using Point2 = Point<float, 2>;
using Point3 = Point<float, 3>;
using Point4 = Point<float, 4>;

}  // namespace sren
