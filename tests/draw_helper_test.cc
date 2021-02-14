#include "src/draw_helper.h"

#include "test.h"

using namespace sren;
using namespace sren::details;

TEST(TestDrawHelper, Interp_InterpValueByRatio) {
  ASSERT_EQ(Interp(1, 2, 0.5), 1.5);
  ASSERT_EQ(Interp(-1, 1, 0.5), 0);
}

TEST(TestDrawHelper, InterpVector_InterEachValueOfVector) {
  Vector4 expect(1.5, 0, 1, 3);
  Vector4 v1(1, -1, 3, 3);
  Vector4 v2(2, 1, -1, 3);
  ASSERT_EQ(InterpVector(v1, v2, 0.5f), expect);
}
