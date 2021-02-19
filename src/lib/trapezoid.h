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

int CutTriangle(std::array<Vertex, 3> verts, std::array<Trapezoid, 2> *traps);

} // namespace trapezoids

} // namespace sren
