#include "src/vector.h"

#include <iostream>
#include <limits>

#include "gtest/gtest.h"
#include "src/math.h"

using namespace sren;
using namespace sren::vectors;

TEST(Vector2Test, Abs_WithTwoPositiveValues_ReturnsTwoPositiveValues) {
  Vector2 v(1.0f, 1.0f);
  Vector2 absolutes = v.Abs();
  ASSERT_EQ(1.0f, absolutes.x());
  ASSERT_EQ(1.0f, absolutes.y());
}

TEST(Vector2Test, Abs_WithTwoNegativeValues_ReturnsTwoPositiveValues) {
  Vector2 v(-1.0f, -1.0f);
  Vector2 absolutes = v.Abs();
  ASSERT_EQ(1.0f, absolutes.x());
  ASSERT_EQ(1.0f, absolutes.y());
}

TEST(Vector2Test,
     Abs_WithOneNegativeAndOnePositiveValue_ReturnsTwoPositiveValues) {
  Vector2 v1(-1.0f, 1.0f);
  Vector2 absolutes = v1.Abs();
  ASSERT_EQ(1.0f, absolutes.x());
  ASSERT_EQ(1.0f, absolutes.y());

  Vector2 v2(1.0f, -1.0f);
  absolutes = v2.Abs();
  ASSERT_EQ(1.0f, absolutes.x());
  ASSERT_EQ(1.0f, absolutes.y());
}

TEST(Vector2Test,
     Set_OnVectorWithDifferentValues_UpdatesExistingValuesInVector) {
  Vector2 v(-1.0f, -1.0f);
  v.Set(-2.0f, 2.0f);
  ASSERT_EQ(-2.0f, v.x());
  ASSERT_EQ(2.0f, v.y());
}

TEST(Vector2Test, SetScale_WithAnotherVector_ScalesExistingValuesInVector) {
  Vector2 v(-5.0f, 5.0f);
  Vector2 scale(-1.0f, 2.0f);
  v.SetScale(scale);
  ASSERT_EQ(5.0f, v.x()) << v;
  ASSERT_EQ(10.0f, v.y()) << v;
}

TEST(Vector2Test, Magnitude_OfVector_IsCorrectlyCalculated) {
  Vector2 v(3.0f, 4.0f);
  ASSERT_EQ(5.0f, v.Magnitude());
}

TEST(Vector2Test, SqrMagnitude_OfVector_IsCorrectlyCalculated) {
  Vector2 v(3.0f, 4.0f);
  ASSERT_EQ(25.0f, v.SquareMagnitude());
}

TEST(Vector2Test, Normalize_ByDefault_NormalizezValuesInVector) {
  Vector2 v(3.0f, 4.0f);
  Vector2 normalized = v.Normalize();
  ASSERT_EQ(0.6f, normalized.x());
  ASSERT_EQ(0.8f, normalized.y());
}

TEST(Vector2Test, IndexAccessor_OnVector_ReturnsValuesAtIndex) {
  Vector2 v(2.0f, 3.0f);
  ASSERT_EQ(2.0f, v[0]);
  ASSERT_EQ(3.0f, v[1]);
}

TEST(Vector2Test, IsNormalized_WithNormalizedVector_ReturnsTrue) {
  Vector2 v(0.6F, 0.8F);
  ASSERT_TRUE((v.IsNormalized(0.001F)));
}

TEST(Vector2Test, IsNormalized_WithNonNormalizedVector_ReturnsFalse) {
  Vector2 v(1.0f, 1.0f);
  ASSERT_FALSE(v.IsNormalized(0.001F));
}

TEST(Vector2Test, Inverse_WithNonZeroValues_ReturnsInversedValues) {
  Vector2 v(2.0f, 5.0f);
  Vector2 inversed = v.Inverse();
  ASSERT_EQ(0.5F, inversed.x());
  ASSERT_EQ(0.2F, inversed.y());
}

TEST(Vector2Test, Inverse_WithZeroValues_ReturnsInfinity) {
  Vector2 v(0.0f, 0.0f);
  Vector2 inversed = v.Inverse();
  ASSERT_EQ(std::numeric_limits<float>::infinity(), inversed.x());
  ASSERT_EQ(std::numeric_limits<float>::infinity(), inversed.y());
}

TEST(Vector2Test, Equality_WithSameVectors_ReturnsTrue) {
  Vector2 v1(1.0f, 1.0f);
  Vector2 v2(1.0f, 1.0f);
  ASSERT_TRUE(v1 == v2);
}

TEST(Vector2Test, Equality_WithDifferentVectors_ReturnsFalse) {
  Vector2 v1(1.0f, 1.0f);
  Vector2 v2(2.0f, 1.0f);
  Vector2 v3(1.0f, 2.0f);
  ASSERT_FALSE(v1 == v2);
  ASSERT_FALSE(v1 == v3);
}

TEST(Vector2Test, Inequality_WithDifferentVectors_ReturnsTrue) {
  Vector2 v1(1.0f, 1.0f);
  Vector2 v2(2.0f, 1.0f);
  Vector2 v3(1.0f, 2.0f);
  ASSERT_TRUE(v1 != v2);
  ASSERT_TRUE(v1 != v3);
}

TEST(Vector2Test, Inequality_WithSameVectors_ReturnsFalse) {
  Vector2 v1(1.0f, 1.0f);
  Vector2 v2(1.0f, 1.0f);
  ASSERT_FALSE(v1 != v2);
}

TEST(Vector2Test, Min_WithTwoVectors_ReturnsMinimumOne) {
  Vector2 v1(-1.0f, -1.0f);
  Vector2 v2(1.0f, 1.0f);
  Vector2 mn = vectors::Min(v1, v2);
  ASSERT_TRUE(mn == v1);
}

TEST(Vector2Test, Max_WithTwoVectors_ReturnsMaximumOne) {
  Vector2 v1(-1.0f, -1.0f);
  Vector2 v2(1.0f, 1.0f);
  Vector2 mx = vectors::Max(v1, v2);
  ASSERT_TRUE(mx == v2);
}

TEST(Vector3Test, Scale_WithTwoVectors_ReturnsVectorElementsMultiplied) {
  Vector3 const expected = Vector3(5.0f, 10.0f, 6.0f);
  Vector3 v1(-5.0f, 5.0f, 2.0f);
  Vector3 v2(-1.0f, 2.0f, 3.0f);
  Vector3 scaled = v1.Scale(v2);
  ASSERT_EQ(expected, scaled);
}

TEST(Vector3Test, Normalize_ByDefault_NormalizezValuesInVector) {
  Vector3 input[] = {Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, 0.0f, 0.0f),
                     Vector3(-0.0f, -0.0f, -0.0f), Vector3(3.0f, 4.0f, 0.0f)};
  Vector3 output[] = {Vector3(0.0f, 1.f, 0.0f), Vector3(0.0f, 0.0f, 0.0f),
                      Vector3(-0.0f, -0.0f, -0.0f), Vector3(0.6f, 0.8f, 0.0f)};

  Vector3 normalized = input[0].Normalize();
  ASSERT_TRUE(output[0].AlmostEqual(normalized, 0.0001f)) << normalized;
  normalized = input[1].Normalize();
  ASSERT_TRUE(output[1].AlmostEqual(normalized, 0.0001f)) << normalized;
  normalized = input[2].Normalize();
  ASSERT_TRUE(output[2].AlmostEqual(normalized, 0.0001f)) << normalized;
}

TEST(Vector3Test, Inverse_WithNonZeroValues_ReturnsInversedValues) {
  Vector3 const expected = Vector3(0.5f, 0.2f, 1.0f);
  Vector3 v(2.0f, 5.0f, 1.0f);
  Vector3 inversed = v.Inverse();
  ASSERT_EQ(expected, inversed);
}

TEST(Vector3Test, Inverse_WithZeroValues_ReturnsInfinity) {
  Vector3 const expected = Vector3::Infinty();
  Vector3 v(0.0f, 0.0f, 0.0f);
  Vector3 inversed = v.Inverse();
  ASSERT_EQ(expected, inversed);
}

TEST(Vector3Test, Set_WithArrayOfValues_SetsInXYZOrder) {
  Vector3 const expected = Vector3(1.0f, 5.0f, 13.0f);
  Vector3 target{};
  target.Set(expected.data());
  ASSERT_EQ(expected, target);
}

TEST(Vector3Test, GetPtr_WithValues_ReturnsValuesInXYZOrder) {
  Vector3 const expected = Vector3(1.0f, 5.0f, 13.0f);
  Vector3 source(expected.x(), expected.y(), expected.z());
  float* result = source.data();

  ASSERT_EQ(expected, Vector3(result[0], result[1], result[2]));
}

TEST(Vector3Test, GetPtrConst_WithValues_ReturnsValuesInXYZOrder) {
  Vector3 const expected = Vector3(1.0f, 5.0f, 13.0f);
  float const* result = expected.data();
  ASSERT_EQ(expected, Vector3(result));
}

TEST(Vector2Test, LeftOfLine_OnlyReturnsTrueWhenLeft) {
  auto const p1 = Vector2(0, 1);
  auto const p2 = Vector2(1, 0);
  auto const p_on = Vector2(0.5f, 0.5f);
  auto const p_left = Vector2(0.4f, 0.5f);
  auto const p_right = Vector2(0.6f, 0.5f);
  ASSERT_TRUE(LeftOfLine(p_left, p1, p2));
  ASSERT_TRUE(LeftOfLine(p_left, p2, p1));
  ASSERT_FALSE(LeftOfLine(p_on, p1, p2));
  ASSERT_FALSE(LeftOfLine(p_on, p2, p1));
  ASSERT_FALSE(LeftOfLine(p_right, p1, p2));
  ASSERT_FALSE(LeftOfLine(p_right, p2, p1));
}
