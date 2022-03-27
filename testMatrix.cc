#include <gtest/gtest.h>

#include "Matrix.h"



TEST(CreationAdnGetters, MatrixCreation) {
  mat::Matrix<int, 2, 2> m0;
  EXPECT_EQ(m0(0, 0), 0);
  EXPECT_EQ(m0(0, 1), 0);
  EXPECT_EQ(m0(1, 0), 0);
  EXPECT_EQ(m0(1, 1), 0); 

  mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
  EXPECT_EQ(m1(0, 0), 1);
  EXPECT_EQ(m1(0, 1), 2);
  EXPECT_EQ(m1(1, 0), 3);
  EXPECT_EQ(m1(1, 1), 4);

  mat::Matrix<int, 10, 10> m2 ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100});
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      EXPECT_EQ(m2(i, j), i * 10 + j + 1);
    }
  }
}

 TEST(Iterator, MatrixIterator) {
   mat::Matrix<int, 2, 2> m0;
   int i = 0;
   for (auto it = m0.begin(); it != m0.end(); ++it)
   {
     EXPECT_EQ(*it, 0);
     i++;
   }
   EXPECT_EQ(i, 4);

   mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
   i = 0;
   for (auto it = m1.begin(); it != m1.end(); ++it)
   {
     EXPECT_EQ(*it, i + 1);
     i++;
   }
   EXPECT_EQ(i, 4);

   mat::Matrix<int, 10, 10> m2 ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100});
   i = 0;
   for (auto it = m2.begin(); it != m2.end(); ++it)
   {
     EXPECT_EQ(*it, i + 1);
     i++;
   }
   EXPECT_EQ(i, 100);
 }



 TEST(Iterator, MatrixConstIterator){
    const mat::Matrix<int, 2, 2> m0;
    int i = 0;
    for (auto it = m0.begin(); it != m0.end(); ++it)
    {
      EXPECT_EQ(*it, 0);
      i++;
    }
    EXPECT_EQ(i, 4);

    const mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
    i = 0;
    for (auto it = m1.begin(); it != m1.end(); ++it)
    {
      EXPECT_EQ(*it, i + 1);
      i++;
    }
    EXPECT_EQ(i, 4);

    const mat::Matrix<int, 10, 10> m2 ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100});
    i = 0;
    for (auto it = m2.begin(); it != m2.end(); ++it)
    {
      EXPECT_EQ(*it, i + 1);
      i++;
    }
    EXPECT_EQ(i, 100);

 }


 TEST(OperationTest, MatrixAddition) {
   mat::Matrix<int, 2, 2> m0;
   mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m3 ({2, 4, 6, 8});
   EXPECT_EQ(m0 + m0, m0);
   EXPECT_EQ(m0 + m1, m1);
   EXPECT_EQ(m1 + m2, m3);
   EXPECT_EQ(m1 + m0, m1);
   EXPECT_EQ(m0 + m2, m2);
   EXPECT_EQ(m2 + m0, m2);
 }

 TEST(OperationTest, MatrixSubtraction) {
   mat::Matrix<int, 2, 2> m0;
   mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m3 ({-1, -2, -3, -4});
   EXPECT_EQ(m0 - m0, m0);
   EXPECT_EQ(m0 - m1, m3);
   EXPECT_EQ(m1 - m2, m0);
   EXPECT_EQ(m1 - m0, m1);
   EXPECT_EQ(m0 - m2, m3);
   EXPECT_EQ(m2 - m0, m2);
 }

 TEST(OperationTest, MatrixMultiplication) {
   mat::Matrix<int, 2, 2> m0;
   mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
   mat::Matrix<int, 2, 2> m3 ({7, 10,15, 22});
   EXPECT_EQ(m0 * m0, m0);
   EXPECT_EQ(m0 * m1, m0);
   EXPECT_EQ(m1 * m2, m3);
   EXPECT_EQ(m1 * m0, m0);
   EXPECT_EQ(m0 * m2, m0);
   EXPECT_EQ(m2 * m0, m0);
 }

 TEST(OperationTest, MatrixAdditionInPlace){
    mat::Matrix<int, 2, 2> m0;
    mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m3 ({2, 4, 6, 8});
    mat::Matrix<int, 2, 2> m4 ({3, 6, 9, 12});
    m0 += m0;
    EXPECT_EQ(m0, m0);
    m0 += m1;
    EXPECT_EQ(m0, m1);
    m1 += m2;
    EXPECT_EQ(m1, m3);
    m1 += m0;
    EXPECT_EQ(m1, m4);
    m0 += m2;
    EXPECT_EQ(m0, m3);
    m2 += m0;
    EXPECT_EQ(m2, m4);
 }

 TEST(OperationTest, MatrixSubtractionInPlace){
    mat::Matrix<int, 2, 2> m0bis;
    mat::Matrix<int, 2, 2> m0;
    mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m3 ({-1, -2, -3, -4});
    mat::Matrix<int, 2, 2> m4 ({-2, -4, -6, -8});
    mat::Matrix<int, 2, 2> m5 ({3, 6, 9, 12});

    m0 -= m0;
    EXPECT_EQ(m0, m0);
    m0 -= m1;
    EXPECT_EQ(m0, m3);
    m1 -= m2;
    EXPECT_EQ(m1, m0bis);
    m1 -= m0;
    EXPECT_EQ(m1, m2);
    m0 -= m2;
    EXPECT_EQ(m0, m4);
    m2 -= m0;
    EXPECT_EQ(m2, m5);
 }

 TEST(OperationTest, MatrixMultiplicationInPlace){
    mat::Matrix<int, 2, 2> m0;
    mat::Matrix<int, 2, 2> m1 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m2 ({1, 2, 3, 4});
    mat::Matrix<int, 2, 2> m3 ({7, 10, 15, 22});
    m0 *= m0;
    EXPECT_EQ(m0, m0);
    m0 *= m1;
    EXPECT_EQ(m0, m0);
    m1 *= m2;
    EXPECT_EQ(m1, m3);
    m1 *= m0;
    EXPECT_EQ(m1, m0);
    m0 *= m2;
    EXPECT_EQ(m0, m0);
    m2 *= m0;
    EXPECT_EQ(m2, m0);
 }

 TEST(IdentityMatrix, IdentityMatrixTest){
    mat::Matrix<int, 2, 2> i0({1, 0, 0, 1});
    EXPECT_EQ((mat::identity<int, 2>()),i0);

    mat::Matrix<int, 4, 4> i1({1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1});
    EXPECT_EQ((mat::identity<int, 4>()), i1);
 }

 TEST(TransposedMatrixTest, Transposed){
    mat::Matrix<int, 2, 2, mat::MatrixOrdering::RowMajor> m0({1, 2, 3, 4});
    mat::Matrix<int, 2, 2, mat::MatrixOrdering::ColMajor> m1({1, 3, 2, 4});
    EXPECT_EQ(m0.transpose(), m1);
    mat::Matrix<int, 4, 4, mat::MatrixOrdering::RowMajor> m2({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    mat::Matrix<int, 4, 4, mat::MatrixOrdering::ColMajor> m3({1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16});
    EXPECT_EQ(m2.transpose(), m3);
 }



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
