#include "src/draw_helper.h"

#include "test.h"

using namespace sren;
using namespace sren::details;

TEST(TestDrawHelper, Interp_InterpValueByRatio) {
  ASSERT_EQ(Interp(1, 2, 0.5), 1.5);
  ASSERT_EQ(Interp(-1, 1, 0.5), 0);
}

TEST(TestDrawHelper, InterpVector_InterpEachValueOfVector) {
  Vector4 expect(1.5, 0, 1, 3);
  Vector4 v1(1, -1, 3, 3);
  Vector4 v2(2, 1, -1, 3);
  ASSERT_EQ(InterpVector(v1, v2, 0.5f), expect);
}

TEST(TestDrawHelper, CalcRenderPoint_GetTheInterpPoint) {
  Vertex expect({1, 2, 0.3f, 1}, {}, {}, {});
  Vertex top({3, 4, 0.1f, 1}, {}, {}, {});
  Vertex bottom({0, 1, 0.4f, 1}, {}, {}, {});
  ASSERT_EQ(CalcRenderPoint(top, bottom, 2.0f), expect);
}
