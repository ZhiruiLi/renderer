#include "src/matrix.h"

#include "test.h"

using namespace sren;

// TEST(TestMatrix4x4, TransformAABBSlow_AndTransformAAB_ReturnSameValues) {
//   Matrix4x4 m;
//   for (int i = 0; i < 16; ++i) m.m_Data[i] = (float)(7 - i);
//   AABB aabb(Vector3f(1, 2, 3), Vector3f(4, 5, 6));
//   AABB aabbSlow;
//   TransformAABBSlow(aabb, m, aabbSlow);
//   AABB aabbRef;
//   TransformAABB(aabb, m, aabbRef);
//   CHECK_CLOSE(aabbRef.m_Center, aabbSlow.m_Center, 0.000001F);
//   CHECK_CLOSE(aabbRef.m_Extent, aabbSlow.m_Extent, 0.000001F);
// }

// TEST(TestMatrix4x4, MiscMatrixTests) {
//   Matrix4x4 m0, m1, m2, m6;
//   for (int i = 0; i < 16; ++i) {
//     m0.data()[i] = (float)i;
//     m1.data()[15 - i] = (float)i;
//   }
//
//   m2 = m0 * m1;
//   MultiplyMatrices4x4REF(&m0, &m1, &m2);
//   MultiplyMatrices4x4(&m0, &m1, &m6);
//   CHECK_EQUAL(0, memcmp(m2.m_Data, m6.m_Data, sizeof(Matrix4x4)));
//
//   TransposeMatrix4x4REF(&m0, &m2);
//   TransposeMatrix4x4(&m0, &m6);
//   CHECK_EQUAL(0, memcmp(m2.m_Data, m6.m_Data, sizeof(Matrix4x4)));
//
//   Vector3f v(2.0F, 5.0F, 2.0F);
//   Vector3f res(2.0F, 5.0F, -2.0F);
//
//   Quaternionf q;
//   Quaternionf backConvertedQ;
//   Matrix3x3 m3;
//   Vector3f tempResult;
//
//   q = AxisAngleToQuaternion(Vector3f::yAxis, kPI / 2.0F);
//   QuaternionToMatrix(q, m3);
//
//   CHECK_CLOSE(res, RotateVectorByQuat(q, v), 0.000001F);
//   CHECK_CLOSE(res, m3.MultiplyPoint3(v), 0.000001F);
//
//   MatrixToQuaternion(m3, backConvertedQ);
//   ASSERT_TRUE(CompareApproximately(backConvertedQ, q));
//
//   Vector3f axis;
//   float roll;
//
//   QuaternionToAxisAngle(backConvertedQ, &axis, &roll);
//   CHECK_CLOSE(Vector3f::yAxis, axis, 0.000001F);
//   CHECK_CLOSE(kPI / 2.0F, roll, 0.000001F);
//
//   q = Inverse(q);
//   m3.Invert();
//   MatrixToQuaternion(m3, backConvertedQ);
//   ASSERT_TRUE(CompareApproximately(backConvertedQ, q));
//
//   tempResult = RotateVectorByQuat(q, res);
//   CHECK_CLOSE(v, tempResult, 0.000001F);
//   tempResult = RotateVectorByQuat(backConvertedQ, res);
//   CHECK_CLOSE(v, tempResult, 0.000001F);
//   tempResult = m3.MultiplyPoint3(res);
//   CHECK_CLOSE(v, tempResult, 0.000001F);
// }

TEST(TestMatrix4x4, IsIdentity_GivenIdentityMatrix_ReturnsTrue) {
  float identity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
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

  Matrix4x4 sourceMatrix = Matrix4x4(source);
  Matrix4x4 cloneMatrix = Matrix4x4(clone);
  Matrix4x4 resultMatrix = (cloneMatrix = sourceMatrix);

  ASSERT_ARRAY_EQ(source, sourceMatrix.data(), 16);
  ASSERT_ARRAY_EQ(source, cloneMatrix.data(), 16);
  ASSERT_ARRAY_EQ(source, resultMatrix.data(), 16);
}

TEST(TestMatrix4x4, AssignmentOperator_AssignsMatrix3x3ToMatrix4x4) {
  float expected[16] = {-1, -2, -3, 0, 0.1f, 0.2f, 0.3f, 0,
                        1,  2,  3,  0, 0,    0,    0,    1};

  Matrix3x3 sourceMatrix({{
      {expected[0], expected[4], expected[8]},
      {expected[1], expected[5], expected[9]},
      {expected[2], expected[6], expected[10]},
  }});

  Matrix4x4 resultMatrix(sourceMatrix);

  ASSERT_ARRAY_EQ(expected, resultMatrix.data(), 16);
}

// TEST(TestMatrix4x4, DecomposeProjection_CorrectPerspectivePlaneCoordinates) {
//   Matrix4x4 m;
//   float fov = 90.0f;
//   float aspect = 16.0f / 9.0f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetPerspective(fov, aspect, zNear, zFar);
//   FrustumPlanes planes = m.DecomposeProjection();
//
//   CHECK_CLOSE(zNear, planes.zNear, 0.0001f);
//   // result is 1000.13 vs 1000, which is pretty close. A fixed epsilon of
//   // 0.00001 is not correct, as precision is relative to magnitude.
//   CHECK_CLOSE(zFar, planes.zFar, 0.2f);
//
//   float calculatedFoV = Rad2Deg(atan2(planes.top, planes.zNear) * 2.0f);
//   CHECK_CLOSE(fov, calculatedFoV, 0.0001f);
//
//   float calculatedAspect =
//       (planes.right - planes.left) / (planes.top - planes.bottom);
//   CHECK_CLOSE(aspect, calculatedAspect, 0.0001f);
// }

// TEST(TestMatrix4x4, DecomposeProjection_CorrectOrthoPlaneCoordinates) {
//   Matrix4x4 m;
//   float left = -2.5f;
//   float right = 4.5f;
//   float top = 3.5f;
//   float bottom = -1.5f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetOrtho(left, right, bottom, top, zNear, zFar);
//   FrustumPlanes planes = m.DecomposeProjection();
//
//   // 0.299959779f vs .3f, pretty close.
//   CHECK_CLOSE(zNear, planes.zNear, 0.0001f);
//   CHECK_CLOSE(zFar, planes.zFar, 0.0001f);
//   CHECK_CLOSE(left, planes.left, 0.0001f);
//   CHECK_CLOSE(right, planes.right, 0.0001f);
//   CHECK_CLOSE(top, planes.top, 0.0001f);
//   CHECK_CLOSE(bottom, planes.bottom, 0.0001f);
// }

// TEST(TestMatrix4x4, DecomposeProjection_BackAndForth) {
//   Matrix4x4 m;
//   float fov = 90.0f;
//   float aspect = 16.0f / 9.0f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetPerspective(fov, aspect, zNear, zFar);
//
//   FrustumPlanes planes = m.DecomposeProjection();
//
//   Matrix4x4 matrixFromFrustum;
//   matrixFromFrustum.SetFrustum(planes.left, planes.right, planes.bottom,
//                                planes.top, planes.zNear, planes.zFar);
//
//   for (int i = 0; i < 16; i++) {
//     CHECK_CLOSE(m.m_Data[i], matrixFromFrustum.m_Data[i], 0.000001F);
//   }
// }

// TEST(TestMatrix4x4, DecomposeProjection_Drift) {
//   Matrix4x4 originalMatrix;
//   float fov = 90.0f;
//   float aspect = 16.0f / 9.0f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   originalMatrix.SetPerspective(fov, aspect, zNear, zFar);
//
//   static const int driftIterations = 100;
//
//   FrustumPlanes planes;
//   Matrix4x4 matrixFromFrustum = originalMatrix;
//
//   for (int i = 0; i < driftIterations; i++) {
//     planes = matrixFromFrustum.DecomposeProjection();
//     matrixFromFrustum.SetFrustum(planes.left, planes.right, planes.bottom,
//                                  planes.top, planes.zNear, planes.zFar);
//
//     for (int j = 0; j < 16; j++) {
//       CHECK_CLOSE(originalMatrix.m_Data[j], matrixFromFrustum.m_Data[j],
//                   0.0001f);
//     }
//   }
// }

// TEST(TestMatrix4x4, AdjustDepthRange_NonDestructiveOrtho) {
//   Matrix4x4 m;
//   float left = -2.5f;
//   float right = 4.5f;
//   float top = 3.5f;
//   float bottom = -1.5f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetOrtho(left, right, bottom, top, zNear, zFar);
//
//   Matrix4x4 m2(m);
//
//   m2.AdjustDepthRange(zNear, zFar);
//
//   for (int i = 0; i < 16; i++) {
//     CHECK_CLOSE(m.m_Data[i], m2.m_Data[i], 0.000001F);
//   }
// }

// TEST(TestMatrix4x4, AdjustDepthRange_NonDestructivePerspective) {
//   Matrix4x4 m;
//   float fov = 90.0f;
//   float aspect = 16.0f / 9.0f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetPerspective(fov, aspect, zNear, zFar);
//
//   // set some additional uncommonly used values; these should be preserved
//   m.Get(0, 1) = 0.12345f;
//   m.Get(0, 2) = 0.013f;
//   m.Get(1, 2) = 0.017f;
//
//   Matrix4x4 m2(m);
//
//   m2.AdjustDepthRange(zNear, zFar);
//
//   for (int i = 0; i < 16; i++) {
//     CHECK_CLOSE(m.m_Data[i], m2.m_Data[i], 0.000001F);
//   }
// }

// TEST(TestMatrix4x4, AdjustDepthRange_Ortho) {
//   Matrix4x4 m;
//   float left = -2.5f;
//   float right = 4.5f;
//   float top = 3.5f;
//   float bottom = -1.5f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetOrtho(left, right, bottom, top, zNear, zFar);
//
//   zNear = 12.0f;
//   zFar = 345.0f;
//   m.AdjustDepthRange(zNear, zFar);
//
//   // use DecomposeProjection to verify the results
//   FrustumPlanes planes = m.DecomposeProjection();
//
//   CHECK_CLOSE(zNear, planes.zNear, 0.0001f);
//   CHECK_CLOSE(zFar, planes.zFar, 0.0001f);
//   CHECK_CLOSE(left, planes.left, 0.0001f);
//   CHECK_CLOSE(right, planes.right, 0.0001f);
//   CHECK_CLOSE(top, planes.top, 0.0001f);
//   CHECK_CLOSE(bottom, planes.bottom, 0.0001f);
// }

// TEST(TestMatrix4x4, AdjustDepthRange_Perspective) {
//   Matrix4x4 m;
//   float fov = 90.0f;
//   float aspect = 16.0f / 9.0f;
//   float zNear = 0.3f;
//   float zFar = 1000.0f;
//
//   m.SetPerspective(fov, aspect, zNear, zFar);
//
//   zNear = 12.0f;
//   zFar = 345.0f;
//   m.AdjustDepthRange(zNear, zFar);
//
//   FrustumPlanes planes = m.DecomposeProjection();
//
//   CHECK_CLOSE(zNear, planes.zNear, 0.0001f);
//   CHECK_CLOSE(zFar, planes.zFar, 0.2f);
//
//   float calculatedFoV = Rad2Deg(atan2(planes.top, planes.zNear) * 2.0f);
//   CHECK_CLOSE(fov, calculatedFoV, 0.0001f);
//
//   float calculatedAspect =
//       (planes.right - planes.left) / (planes.top - planes.bottom);
//   CHECK_CLOSE(aspect, calculatedAspect, 0.0001f);
// }

// TEST(TestMatrix4x4, Invert_General3D_Invertible) {
//   float inputData[2][16] = {
//       {4, 2, 3, 1, 5, 8, 7, 6, 9, 10, 12, 11, 13, 14, 15, 16},
//       {4, 3, 2, 1, 7, 8, 6, 5, 10, 11, 12, 9, 13, 15, 14, 16},
//   };
//
//   float expectedData[2][16] = {
//       {0.590909123f, 0.13636364f, -0.227272734f, 0.0f, 0.0681818202f,
//        0.477272749f, -0.295454562f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f,
//        -1.13636398f, -0.954545974f, -0.409090519f, 1.0f},
//       {0.714285731f, -0.333333343f, 0.0476190485f, 0.0f, -0.571428597f,
//        0.666666686f, -0.238095239f, 0.0f, -0.0714285746f, -0.333333343f,
//        0.261904776f, 0.0f, 0.285715103f, -0.999999523f, -0.714286089f, 1.0f},
//   };
//
//   for (int i = 0; i < ARRAY_SIZE(inputData); ++i) {
//     float* inputDataSingle = inputData[i];
//     float* expectedDataSingle = expectedData[i];
//
//     Matrix4x4 input(inputDataSingle);
//     Matrix4x4 output;
//
//     ASSERT_TRUE(Matrix4x4::Invert_General3D(input, output));
//
//     for (int j = 0; j < 16; ++j) {
//       CHECK_CLOSE(output.GetPtr()[j], expectedDataSingle[j], 0.0001f);
//     }
//   }
// }

// TEST(TestMatrix4x4, Invert_General3D_NonInvertible) {
//   float inputData[2][16] = {
//       {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
//       {0, 0, 0, 0, 8, 7, 6, 5, 12, 11, 10, 9, 16, 15, 14, 13},
//   };
//
//   for (int i = 0; i < ARRAY_SIZE(inputData); ++i) {
//     float* inputDataSingle = inputData[i];
//
//     Matrix4x4 input(inputDataSingle);
//     Matrix4x4 output(inputDataSingle);  // initialize to nonzero
//
//     ASSERT_TRUE(!Matrix4x4::Invert_General3D(input, output));
//
//     for (int j = 0; j < 16; ++j) {
//       CHECK_CLOSE(output.GetPtr()[j], 0, 0.0001f);
//     }
//   }
// }
