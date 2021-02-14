#include "src/trapezoid.h"

#include <array>

#include "gtest/gtest.h"
#include "src/vertex.h"

using namespace sren;

TEST(DrawTest, CutTriangle_SplitTriangleIntoTrapezoids_2Left) {
  auto const p0 = Vector4(1, -1, 0, 0);
  auto const p1 = Vector4(0, 0, 0, 0);
  auto const p2 = Vector4(1, 1, 0, 0);
  std::array<Vertex, 3> verts = {
      Vertex(p2, {}, {}, {}),
      Vertex(p0, {}, {}, {}),
      Vertex(p1, {}, {}, {}),
  };
  std::array<Trapezoid, 2> traps{};
  auto const count = trapezoids::CutTriangle(verts, &traps);
  ASSERT_EQ(count, 2);
  ASSERT_EQ(traps[0].left.top.pos(), p2);
  ASSERT_EQ(traps[0].left.bottom.pos(), p1);
  ASSERT_EQ(traps[0].right.top.pos(), p2);
  ASSERT_EQ(traps[0].right.bottom.pos(), p0);
  ASSERT_EQ(traps[1].left.top.pos(), p1);
  ASSERT_EQ(traps[1].left.bottom.pos(), p0);
  ASSERT_EQ(traps[1].right.top.pos(), p2);
  ASSERT_EQ(traps[1].right.bottom.pos(), p0);
}

TEST(DrawTest, CutTriangle_SplitTriangleIntoTrapezoids_2Right) {
  auto const p0 = Vector4(0, -1, 0, 0);
  auto const p1 = Vector4(1, 1, 0, 0);
  auto const p2 = Vector4(-2, 3, 0, 0);
  std::array<Vertex, 3> verts = {
      Vertex(p2, {}, {}, {}),
      Vertex(p0, {}, {}, {}),
      Vertex(p1, {}, {}, {}),
  };
  std::array<Trapezoid, 2> traps{};
  auto const count = trapezoids::CutTriangle(verts, &traps);
  ASSERT_EQ(count, 2);
  ASSERT_EQ(traps[0].left.top.pos(), p2);
  ASSERT_EQ(traps[0].left.bottom.pos(), p0);
  ASSERT_EQ(traps[0].right.top.pos(), p2);
  ASSERT_EQ(traps[0].right.bottom.pos(), p1);
  ASSERT_EQ(traps[1].left.top.pos(), p2);
  ASSERT_EQ(traps[1].left.bottom.pos(), p0);
  ASSERT_EQ(traps[1].right.top.pos(), p1);
  ASSERT_EQ(traps[1].right.bottom.pos(), p0);
}
