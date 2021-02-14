#pragma once

#include <algorithm>
#include <array>

#include "math.h"
#include "vertex.h"

namespace sren {

struct Trapezoid {
  struct Edge {
    Vertex top{};
    Vertex bottom{};
  };
  float top{};
  float bottom{};
  Edge left{};
  Edge right{};
};

namespace trapezoids {

inline int CutTriangle(std::array<Vertex, 3> verts,
                       std::array<Trapezoid, 2> *traps) {
  std::sort(verts.begin(), verts.end(), [](auto const &a, auto const &b) {
    return a.pos().y() < b.pos().y();
  });
  if (AlmostEqual(verts[0].pos().y(), verts[1].pos().y()) &&
      AlmostEqual(verts[1].pos().y(), verts[2].pos().y())) {
    return 0;
  }
  if (AlmostEqual(verts[0].pos().x(), verts[1].pos().x()) &&
      AlmostEqual(verts[1].pos().x(), verts[2].pos().x())) {
    return 0;
  }
  // 三角形底边 y 较小，底边在下
  if (AlmostEqual(verts[0].pos().y(), verts[1].pos().y())) {
    if (verts[0].pos().x() > verts[1].pos().x()) {
      std::swap(verts[0], verts[1]);
    }
    auto &t = (*traps)[0];
    t.top = verts[2].pos().y();
    t.bottom = verts[0].pos().y();
    t.left = {verts[2], verts[0]};
    t.right = {verts[2], verts[1]};
    return 1;
  }
  // 三角形底边 y 较大，底边在上
  if (AlmostEqual(verts[1].pos().y(), verts[2].pos().y())) {
    if (verts[1].pos().x() > verts[2].pos().x()) {
      std::swap(verts[1], verts[2]);
    }
    auto &t = (*traps)[0];
    t.top = verts[1].pos().y();
    t.bottom = verts[0].pos().y();
    t.left = {verts[1], verts[0]};
    t.right = {verts[2], verts[0]};
    return 1;
  }
  (*traps)[0].top = verts[0].pos().y();
  (*traps)[0].bottom = verts[1].pos().y();
  (*traps)[1].top = verts[1].pos().y();
  (*traps)[1].bottom = verts[2].pos().y();
  auto const is_left =
      vectors::LeftOfLine(verts[1].pos(), verts[0].pos(), verts[2].pos());
  if (is_left) {
    (*traps)[0].left = {verts[2], verts[1]};
    (*traps)[0].right = {verts[2], verts[0]};
    (*traps)[1].left = {verts[1], verts[0]};
    (*traps)[1].right = {verts[2], verts[0]};
  } else {
    (*traps)[0].left = {verts[2], verts[0]};
    (*traps)[0].right = {verts[1], verts[0]};
    (*traps)[1].left = {verts[2], verts[0]};
    (*traps)[1].right = {verts[2], verts[1]};
  }
  return 2;
}

}  // namespace trapezoids

}  // namespace sren
