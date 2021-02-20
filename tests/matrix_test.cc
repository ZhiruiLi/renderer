#include "lib/matrix.h"

#include <gtest/gtest.h>

#include "lib/vector.h"
#include "test.h"

using namespace sren;

TEST(TestMatrix4x4, IsIdentity_GivenIdentityMatrix_ReturnsTrue) {
  float identity[16] = {
      1, 0, 0, 0,  // row 0
      0, 1, 0, 0,  // row 1
      0, 0, 1, 0,  // row 2
      0, 0, 0, 1,  // row 3
  };
  Matrix4x4 matrix(identity);
  ASSERT_TRUE(matrix.IsIdentity());
}

TEST(TestMatrix4x4, IsIdentity_GivenNotIdentityMatrix_ReturnsFalse) {
  float zero[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float all_ones[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  float counterdiagonal_ones[16] = {0, 0, 0, 1, 0, 0, 1, 0,
                                    0, 1, 0, 0, 1, 0, 0, 0};
  float main_diagonal_one_zero[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                                      0, 0, 1, 0, 0, 0, 0, 0};
  float determinant_one[16] = {2, 0, 0, 0, 0, 1, 0, 0,
                               0, 0, 1, 0, 0, 0, 0, 0.5f};
  float not_zero_on_counterdiagonal[16] = {1, 0, 0, 1, 0, 1, 0, 0,
                                           0, 0, 1, 0, 0, 0, 0, 1};
  float permutation[16] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0};
  float main_diagonal_not_ones[16] = {0.42f, 0, 0,     0, 0, 0.42f, 0, 0,
                                      0,     0, 0.42f, 0, 0, 0,     0, 0.42f};
  float negative_identity[16] = {-1, 0, 0,  0, 0, -1, 0, 0,
                                 0,  0, -1, 0, 0, 0,  0, -1};

  Matrix4x4 zero_matrix(zero);
  Matrix4x4 all_ones_matrix(all_ones);
  Matrix4x4 counterdiagonal_ones_matrix(counterdiagonal_ones);
  Matrix4x4 main_diagonal_one_zero_matrix(main_diagonal_one_zero);
  Matrix4x4 determinant_one_matrix(determinant_one);
  Matrix4x4 not_zero_on_counterdiagonal_matrix(not_zero_on_counterdiagonal);
  Matrix4x4 permutation_matrix(permutation);
  Matrix4x4 main_diagonal_not_ones_matrix(main_diagonal_not_ones);
  Matrix4x4 negative_identity_matrix(negative_identity);

  ASSERT_FALSE(zero_matrix.IsIdentity());
  ASSERT_FALSE(all_ones_matrix.IsIdentity());
  ASSERT_FALSE(counterdiagonal_ones_matrix.IsIdentity());
  ASSERT_FALSE(main_diagonal_one_zero_matrix.IsIdentity());
  ASSERT_FALSE(determinant_one_matrix.IsIdentity());
  ASSERT_FALSE(not_zero_on_counterdiagonal_matrix.IsIdentity());
  ASSERT_FALSE(permutation_matrix.IsIdentity());
  ASSERT_FALSE(main_diagonal_not_ones_matrix.IsIdentity());
  ASSERT_FALSE(negative_identity_matrix.IsIdentity());
}

TEST(TestMatrix4x4, Copy_GivenValidMatrix_CreatesCopy) {
  float source[16] = {-1, -2, -3, -4, 0.1f,     0.2f,     0.3f,     0.4f,
                      1,  2,  3,  4,  100.001f, 200.002f, 300.003f, 400.004f};

  float clone[16] = {0.1f,     0.2f,     0.3f,     0.4f,     -1, -2, -3, -4,
                     100.001f, 200.002f, 300.003f, 400.004f, 1,  2,  3,  4};

  Matrix4x4 source_matrix = Matrix4x4(source);
  Matrix4x4 clone_matrix = Matrix4x4(clone);
  Matrix4x4 result_matrix = (clone_matrix = source_matrix);

  ASSERT_ARRAY_EQ(source, source_matrix.data(), 16);
  ASSERT_ARRAY_EQ(source, clone_matrix.data(), 16);
  ASSERT_ARRAY_EQ(source, result_matrix.data(), 16);
}

TEST(TestMatrix4x4, AssignmentOperator_AssignsMatrix3x3ToMatrix4x4) {
  float expected[16] = {
      -1,   -2,   -3,   0,  // row 0
      0.1f, 0.2f, 0.3f, 0,  // row 1
      1,    2,    3,    0,  // row 2
      0,    0,    0,    1,  // row 3
  };

  Matrix3x3 source_matrix({{
      {expected[0], expected[1], expected[2]},
      {expected[4], expected[5], expected[6]},
      {expected[8], expected[9], expected[10]},
  }});

  Matrix4x4 result_matrix(source_matrix);
  ASSERT_ARRAY_EQ(expected, result_matrix.data(), 16);
}

TEST(TestMatrix4x4, WorldTransform_MoveVectorToGivenPos) {
  Vector4 expected(1, 2, 3, 1);
  Vector4 source(-5, -4, -3, 1);
  Vector3 world_pos(6, 6, 6);
  auto const trans_matrix = matrixs::WorldTransform(world_pos);
  auto const result = source * trans_matrix;
  ASSERT_EQ(result, expected) << result;
  auto const id_matrix = matrixs::WorldTransform(Vector3(0.0f, 0.0f, 0.0f));
  ASSERT_TRUE(id_matrix.IsIdentity()) << id_matrix;
}

TEST(TestMatrix4x4, RotateTransform_MoveVectorToRotatedPos) {
  auto const id_matrix = matrixs::RotateTransform(Vector3(0.0f, 0.0f, 0.0f));
  ASSERT_TRUE(id_matrix.IsIdentity()) << id_matrix;
}
