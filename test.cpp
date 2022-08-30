#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <stdexcept>

#include "matrix_oop.hpp"

TEST(copy_constr, example_1) {
  Matrix testa{2};
  testa.setDegit(0, 0, 1);
  testa.setDegit(0, 1, 2);
  testa.setDegit(1, 0, 3);
  testa.setDegit(1, 1, 4);
  Matrix copy = testa;
  for (int i = 0; i < testa.getRow(); i++) {
    for (int j = 0; j < testa.getColum(); j++) {
      GTEST_ASSERT_EQ(copy.getDigit(i, j), testa.getDigit(i, j));
    }
  }
}

TEST(determinant, normal_1_1) {
  Matrix testa{1};
  testa.setDegit(0, 0, 100);
  GTEST_ASSERT_EQ(testa.determinant(), 100.0);
}

TEST(determinant, normal_2_2) {
  Matrix testa{2};
  testa.setDegit(0, 0, 1);
  testa.setDegit(0, 1, 2);
  testa.setDegit(1, 0, 3);
  testa.setDegit(1, 1, 4);
  GTEST_ASSERT_EQ(testa.determinant(), -2.0);
}

TEST(determinant, normal1_3_3) {
  Matrix testa{3};
  testa.setDegit(0, 0, 1);
  testa.setDegit(0, 1, 2);
  testa.setDegit(0, 2, 3);
  testa.setDegit(1, 0, 4);
  testa.setDegit(1, 1, 5);
  testa.setDegit(1, 2, 6);
  testa.setDegit(2, 0, 7);
  testa.setDegit(2, 1, 8);
  testa.setDegit(2, 2, 9);
  GTEST_ASSERT_EQ(testa.determinant(), 0.0);
}

TEST(determinant, normal_double_3_3) {
  Matrix testa{3};
  testa.setDegit(0, 0, 1.1);
  testa.setDegit(0, 1, 2.2);
  testa.setDegit(0, 2, 3);
  testa.setDegit(1, 0, 4.4);
  testa.setDegit(1, 1, 5);
  testa.setDegit(1, 2, 6.6);
  testa.setDegit(2, 0, 7);
  testa.setDegit(2, 1, 8.8);
  testa.setDegit(2, 2, 9);
  EXPECT_NEAR(testa.determinant(), 11.292, 0.7);
}

TEST(determinant, normal2_3_3) {
  Matrix testa{3};
  testa.setDegit(0, 0, 1);
  testa.setDegit(0, 1, 2);
  testa.setDegit(0, 2, 3);
  testa.setDegit(1, 0, 4);
  testa.setDegit(1, 1, 5);
  testa.setDegit(1, 2, 6);
  testa.setDegit(2, 0, 7);
  testa.setDegit(2, 1, 8);
  testa.setDegit(2, 2, 9);
  GTEST_ASSERT_EQ(testa.determinant(), 0.0);
}

TEST(determinant, normal_4_4) {
  Matrix testa{4};
  testa.setDegit(0, 0, 4);
  testa.setDegit(0, 1, 5);
  testa.setDegit(0, 2, -1);
  testa.setDegit(0, 3, 8);
  testa.setDegit(1, 0, 1);
  testa.setDegit(1, 1, -5);
  testa.setDegit(1, 2, 9);
  testa.setDegit(1, 3, 3);
  testa.setDegit(2, 0, -5);
  testa.setDegit(2, 1, 1);
  testa.setDegit(2, 2, 9);
  testa.setDegit(2, 3, 2);
  testa.setDegit(3, 0, 7);
  testa.setDegit(3, 1, 8);
  testa.setDegit(3, 2, 2);
  testa.setDegit(3, 3, 1);
  GTEST_ASSERT_EQ(testa.determinant(), 6930.0);
}

TEST(equals, true_1) {
  Matrix first{1};
  first.setDegit(0, 0, 100);
  Matrix second{1};
  second.setDegit(0, 0, 100);
  bool result = first.eq_matrix(second);
  GTEST_ASSERT_EQ(result, 1);
}

TEST(equals, true_2) {
  Matrix first{2};
  first.setDegit(0, 0, 1.11);
  first.setDegit(0, 1, 2.22);
  first.setDegit(1, 0, 3.33);
  first.setDegit(1, 1, 4.44);
  Matrix second{2};
  second.setDegit(0, 0, 1.11);
  second.setDegit(0, 1, 2.22);
  second.setDegit(1, 0, 3.33);
  second.setDegit(1, 1, 4.44);
  bool result = first.eq_matrix(second);
  GTEST_ASSERT_EQ(result, 1);
}

TEST(equals, true_3) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 2);
  first->setDegit(0, 2, 3);
  first->setDegit(1, 0, 4);
  first->setDegit(1, 1, 5);
  first->setDegit(1, 2, 6);
  first->setDegit(2, 0, 7);
  first->setDegit(2, 1, 8);
  first->setDegit(2, 2, 9);
  Matrix *second = new Matrix(3);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 2);
  second->setDegit(0, 2, 3);
  second->setDegit(1, 0, 4);
  second->setDegit(1, 1, 5);
  second->setDegit(1, 2, 6);
  second->setDegit(2, 0, 7);
  second->setDegit(2, 1, 8);
  second->setDegit(2, 2, 9);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 1);
  delete (first);
  delete (second);
}

TEST(equals, true_4) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 0.0000009);
  first->setDegit(0, 1, 0);
  first->setDegit(0, 2, 0);
  first->setDegit(1, 0, 1e-7);
  first->setDegit(1, 1, 0);
  first->setDegit(1, 2, 0);
  first->setDegit(2, 0, 0);
  first->setDegit(2, 1, 0);
  first->setDegit(2, 2, 0);
  Matrix *second = new Matrix(3);
  second->setDegit(0, 0, 0);
  second->setDegit(0, 1, 0);
  second->setDegit(0, 2, 0);
  second->setDegit(1, 0, -0.0);
  second->setDegit(1, 1, 0);
  second->setDegit(1, 2, 0);
  second->setDegit(2, 0, -1e-7);
  second->setDegit(2, 1, 0.000000000012315);
  second->setDegit(2, 2, 0);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 1);
  delete (first);
  delete (second);
}

TEST(equals, false_1) {
  Matrix *first = new Matrix(1);
  first->setDegit(0, 0, 100.00001);
  Matrix *second = new Matrix(1);
  second->setDegit(0, 0, 100);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 0);
  delete (first);
  delete (second);
}

TEST(equals, false_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.11);
  first->setDegit(0, 1, 1e-6);
  first->setDegit(1, 0, 3.33);
  first->setDegit(1, 1, 4.44);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1.11);
  second->setDegit(0, 1, -1e-6);
  second->setDegit(1, 0, 3.33);
  second->setDegit(1, 1, 4.44);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 0);
  delete (first);
  delete (second);
}

TEST(equals, false_3) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.11);
  first->setDegit(0, 1, 1);
  first->setDegit(1, 0, 3.33);
  first->setDegit(1, 1, 4.44);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1.11);
  second->setDegit(0, 1, -1);
  second->setDegit(1, 0, 3.33);
  second->setDegit(1, 1, 4.44);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 0);
  delete (first);
  delete (second);
}

TEST(equals, false_4) {
  Matrix *first = new Matrix(2, 3);
  first->setDegit(0, 0, 1.11);
  first->setDegit(0, 1, 1);
  first->setDegit(0, 2, 1.5);
  first->setDegit(1, 0, 3.33);
  first->setDegit(1, 1, 4.44);
  first->setDegit(1, 2, 5);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1.11);
  second->setDegit(0, 1, 1);
  second->setDegit(1, 0, 3.33);
  second->setDegit(1, 1, 4.44);
  bool result = first->eq_matrix(*second);
  GTEST_ASSERT_EQ(result, 0);
  delete (first);
  delete (second);
}

TEST(transpose, example_1) {
  Matrix *first = new Matrix(2, 3);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 2);
  first->setDegit(0, 2, 3);
  first->setDegit(1, 0, 4);
  first->setDegit(1, 1, 5);
  first->setDegit(1, 2, 6);
  Matrix *second = new Matrix(3, 2);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 4);
  second->setDegit(1, 0, 2);
  second->setDegit(1, 1, 5);
  second->setDegit(2, 0, 3);
  second->setDegit(2, 1, 6);
  Matrix ex = first->transpose();
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      GTEST_ASSERT_EQ(ex.getDigit(i, j), second->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
}

TEST(transpose, example_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 3);
  second->setDegit(1, 0, 2);
  second->setDegit(1, 1, 4);
  Matrix ex = first->transpose();
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      GTEST_ASSERT_EQ(ex.getDigit(i, j), second->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
}

TEST(transpose, example_3) {
  Matrix *first = new Matrix(1);
  first->setDegit(0, 0, 1);
  Matrix *second = new Matrix(1);
  second->setDegit(0, 0, 1);
  Matrix ex = first->transpose();
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      GTEST_ASSERT_EQ(ex.getDigit(i, j), second->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
}

TEST(sum, example_1) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 2);
  first->setDegit(0, 2, 3);
  first->setDegit(1, 0, 4);
  first->setDegit(1, 1, 5);
  first->setDegit(1, 2, 6);
  first->setDegit(2, 0, 7);
  first->setDegit(2, 1, 8);
  first->setDegit(2, 2, 9);
  Matrix *second = new Matrix(3);
  second->setDegit(0, 0, -1);
  second->setDegit(0, 1, -2);
  second->setDegit(0, 2, -3);
  second->setDegit(1, 0, -4);
  second->setDegit(1, 1, -5);
  second->setDegit(1, 2, -6);
  second->setDegit(2, 0, -7);
  second->setDegit(2, 1, -8);
  second->setDegit(2, 2, -9);
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, 0);
  result->setDegit(0, 1, 0);
  result->setDegit(0, 2, 0);
  result->setDegit(1, 0, 0);
  result->setDegit(1, 1, 0);
  result->setDegit(1, 2, 0);
  result->setDegit(2, 0, 0);
  result->setDegit(2, 1, 0);
  result->setDegit(2, 2, 0);
  first->sum_matrix(*second);
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(sum, example_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, -1);
  second->setDegit(0, 1, -2);
  second->setDegit(1, 0, -3);
  second->setDegit(1, 1, -4.0000001);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 0);
  result->setDegit(0, 1, 0);
  result->setDegit(1, 0, 0);
  result->setDegit(1, 1, 0);
  first->sum_matrix(*second);
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(sub, example_1) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 2);
  first->setDegit(0, 2, 3);
  first->setDegit(1, 0, 4);
  first->setDegit(1, 1, 5);
  first->setDegit(1, 2, 6);
  first->setDegit(2, 0, 7);
  first->setDegit(2, 1, 8);
  first->setDegit(2, 2, 9);
  Matrix *second = new Matrix(3);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 2);
  second->setDegit(0, 2, 3);
  second->setDegit(1, 0, 4);
  second->setDegit(1, 1, 5);
  second->setDegit(1, 2, 6);
  second->setDegit(2, 0, 7);
  second->setDegit(2, 1, 8);
  second->setDegit(2, 2, 9);
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, 0);
  result->setDegit(0, 1, 0);
  result->setDegit(0, 2, 0);
  result->setDegit(1, 0, 0);
  result->setDegit(1, 1, 0);
  result->setDegit(1, 2, 0);
  result->setDegit(2, 0, 0);
  result->setDegit(2, 1, 0);
  result->setDegit(2, 2, 0);
  first->sub_matrix(*second);
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(sub, example_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 2);
  second->setDegit(1, 0, 3);
  second->setDegit(1, 1, 4.0000001);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 0);
  result->setDegit(0, 1, 0);
  result->setDegit(1, 0, 0);
  result->setDegit(1, 1, 0);
  first->sub_matrix(*second);
  for (int i = 0; i < second->getRow(); i++) {
    for (int j = 0; j < second->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(mul_number, example_1) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 1.0000001 * 5);
  result->setDegit(0, 1, 2 * 5);
  result->setDegit(1, 0, 3 * 5);
  result->setDegit(1, 1, 4 * 5);
  first->mul_number(5.0);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(mul_number, example_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 1.0000001 * 0);
  result->setDegit(0, 1, 2 * 0);
  result->setDegit(1, 0, 3 * 0);
  result->setDegit(1, 1, 4 * 0);
  first->mul_number(0.000000001);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(mul_number, example_3) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 1.0000001);
  result->setDegit(0, 1, 2);
  result->setDegit(1, 0, 3);
  result->setDegit(1, 1, 4);
  first->mul_number(1.0);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(mul_number, example_4) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.0000001);
  first->setDegit(0, 1, 2);
  first->setDegit(1, 0, 3);
  first->setDegit(1, 1, 4);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, -1.0000001);
  result->setDegit(0, 1, -2);
  result->setDegit(1, 0, -3);
  result->setDegit(1, 1, -4);
  first->mul_number(-1.0);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(mul_matrix, example_1) {
  Matrix *first = new Matrix(3, 2);
  first->setDegit(0, 0, 1);
  first->setDegit(0, 1, 4);
  first->setDegit(1, 0, 2);
  first->setDegit(1, 1, 5);
  first->setDegit(2, 0, 3);
  first->setDegit(2, 1, 6);
  Matrix *second = new Matrix(2, 3);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, -1);
  second->setDegit(0, 2, 1);
  second->setDegit(1, 0, 2);
  second->setDegit(1, 1, 3);
  second->setDegit(1, 2, 4);
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, 9);
  result->setDegit(0, 1, 11);
  result->setDegit(0, 2, 17);
  result->setDegit(1, 0, 12);
  result->setDegit(1, 1, 13);
  result->setDegit(1, 2, 22);
  result->setDegit(2, 0, 15);
  result->setDegit(2, 1, 15);
  result->setDegit(2, 2, 27);
  first->mul_matrix(*second);
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(mul_matrix, example_2) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, 1.5);
  first->setDegit(0, 1, 1.5);
  first->setDegit(1, 0, 1.5);
  first->setDegit(1, 1, 1.5);
  Matrix *second = new Matrix(2);
  second->setDegit(0, 0, 1);
  second->setDegit(0, 1, 1);
  second->setDegit(1, 0, 1);
  second->setDegit(1, 1, 1);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, 3);
  result->setDegit(0, 1, 3);
  result->setDegit(1, 0, 3);
  result->setDegit(1, 1, 3);
  first->mul_matrix(*second);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(first->getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(calc_complements, example_1) {
  Matrix first(3);
  first.setDegit(0, 0, 1);
  first.setDegit(0, 1, 2);
  first.setDegit(0, 2, 3);
  first.setDegit(1, 0, 0);
  first.setDegit(1, 1, 4);
  first.setDegit(1, 2, 2);
  first.setDegit(2, 0, 5);
  first.setDegit(2, 1, 2);
  first.setDegit(2, 2, 1);
  Matrix second = first.calc_complements();
  Matrix result(3);
  result.setDegit(0, 0, 0);
  result.setDegit(0, 1, 10);
  result.setDegit(0, 2, -20);
  result.setDegit(1, 0, 4);
  result.setDegit(1, 1, -14);
  result.setDegit(1, 2, 8);
  result.setDegit(2, 0, -8);
  result.setDegit(2, 1, -2);
  result.setDegit(2, 2, 4);
  for (int i = 0; i < first.getRow(); i++) {
    for (int j = 0; j < first.getColum(); j++) {
      EXPECT_NEAR(second.getDigit(i, j), result.getDigit(i, j), EPS);
    }
  }
}

TEST(calc_complements, example_2) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 2);
  first->setDegit(0, 1, 5);
  first->setDegit(0, 2, 7);
  first->setDegit(1, 0, 6);
  first->setDegit(1, 1, 3);
  first->setDegit(1, 2, 4);
  first->setDegit(2, 0, 5);
  first->setDegit(2, 1, -2);
  first->setDegit(2, 2, -3);
  Matrix second = first->calc_complements();
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, -1);
  result->setDegit(0, 1, 38);
  result->setDegit(0, 2, -27);
  result->setDegit(1, 0, 1);
  result->setDegit(1, 1, -41);
  result->setDegit(1, 2, 29);
  result->setDegit(2, 0, -1);
  result->setDegit(2, 1, 34);
  result->setDegit(2, 2, -24);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(second.getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(inverse_matrix, example_1) {
  Matrix *first = new Matrix(2);
  first->setDegit(0, 0, -1.5);
  first->setDegit(0, 1, -1.5);
  first->setDegit(1, 0, -0.5);
  first->setDegit(1, 1, -1.5);
  Matrix *result = new Matrix(2);
  result->setDegit(0, 0, -1);
  result->setDegit(0, 1, 1);
  result->setDegit(1, 0, 1. / 3);
  result->setDegit(1, 1, -1);
  Matrix second = first->inverse_matrix();
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(second.getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(inverse_matrix, example_2) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 2);
  first->setDegit(0, 1, 5);
  first->setDegit(0, 2, 7);
  first->setDegit(1, 0, 6);
  first->setDegit(1, 1, 3);
  first->setDegit(1, 2, 4);
  first->setDegit(2, 0, 5);
  first->setDegit(2, 1, -2);
  first->setDegit(2, 2, -3);
  Matrix second = first->inverse_matrix();
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, 1);
  result->setDegit(0, 1, -1);
  result->setDegit(0, 2, 1);
  result->setDegit(1, 0, -38);
  result->setDegit(1, 1, 41);
  result->setDegit(1, 2, -34);
  result->setDegit(2, 0, 27);
  result->setDegit(2, 1, -29);
  result->setDegit(2, 2, 24);
  for (int i = 0; i < first->getRow(); i++) {
    for (int j = 0; j < first->getColum(); j++) {
      EXPECT_NEAR(second.getDigit(i, j), result->getDigit(i, j), EPS);
    }
  }
  delete (first);
  delete (result);
}

TEST(operator_eq, example_1) {
  Matrix first(3);
  first.setDegit(0, 0, 2);
  first.setDegit(0, 1, 5);
  first.setDegit(0, 2, 7);
  first.setDegit(1, 0, 6);
  first.setDegit(1, 1, 3);
  first.setDegit(1, 2, 4);
  first.setDegit(2, 0, 5);
  first.setDegit(2, 1, -2);
  first.setDegit(2, 2, -3);
  Matrix result(3);
  result.setDegit(0, 0, 1);
  result.setDegit(0, 1, -1);
  result.setDegit(0, 2, 1);
  result.setDegit(1, 0, -38);
  result.setDegit(1, 1, 41);
  result.setDegit(1, 2, -34);
  result.setDegit(2, 0, 27);
  result.setDegit(2, 1, -29);
  result.setDegit(2, 2, 24);
  int check = (first == result);
  GTEST_ASSERT_EQ(check, 0);
}

TEST(operator_eq, example_2) {
  Matrix *first = new Matrix(3);
  first->setDegit(0, 0, 2);
  first->setDegit(0, 1, 5);
  first->setDegit(0, 2, 7);
  first->setDegit(1, 0, 6);
  first->setDegit(1, 1, 3);
  first->setDegit(1, 2, 4);
  first->setDegit(2, 0, 5);
  first->setDegit(2, 1, -2);
  first->setDegit(2, 2, -3);
  Matrix *result = new Matrix(3);
  result->setDegit(0, 0, 2);
  result->setDegit(0, 1, 5);
  result->setDegit(0, 2, 7);
  result->setDegit(1, 0, 6);
  result->setDegit(1, 1, 3);
  result->setDegit(1, 2, 4);
  result->setDegit(2, 0, 5);
  result->setDegit(2, 1, -2);
  result->setDegit(2, 2, -3);
  int check = (*first == *result);
  GTEST_ASSERT_EQ(check, 1);
  delete (first);
  delete (result);
}

TEST(operator_sum, example_1) {
  Matrix first(3);
  first.setDegit(0, 0, 2);
  first.setDegit(0, 1, 5);
  first.setDegit(0, 2, 7);
  first.setDegit(1, 0, 6);
  first.setDegit(1, 1, 3);
  first.setDegit(1, 2, 4);
  first.setDegit(2, 0, 5);
  first.setDegit(2, 1, 2);
  first.setDegit(2, 2, 3);
  Matrix second(3);
  second.setDegit(0, 0, 2);
  second.setDegit(0, 1, 5);
  second.setDegit(0, 2, 7);
  second.setDegit(1, 0, 6);
  second.setDegit(1, 1, 3);
  second.setDegit(1, 2, 4);
  second.setDegit(2, 0, 5);
  second.setDegit(2, 1, 2);
  second.setDegit(2, 2, 3);
  Matrix result(3);
  result.setDegit(0, 0, 2 * 2);
  result.setDegit(0, 1, 5 * 2);
  result.setDegit(0, 2, 7 * 2);
  result.setDegit(1, 0, 6 * 2);
  result.setDegit(1, 1, 3 * 2);
  result.setDegit(1, 2, 4 * 2);
  result.setDegit(2, 0, 5 * 2);
  result.setDegit(2, 1, 2 * 2);
  result.setDegit(2, 2, 3 * 2);
  Matrix summa = (first + second);
  for (int i = 0; i < second.getRow(); i++) {
    for (int j = 0; j < second.getColum(); j++) {
      GTEST_ASSERT_EQ(summa.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_sum, example_2) {
  Matrix first{3};
  first.setDegit(0, 0, 2);
  first.setDegit(0, 1, 5);
  first.setDegit(0, 2, 7);
  first.setDegit(1, 0, 6);
  first.setDegit(1, 1, 3);
  first.setDegit(1, 2, 4);
  first.setDegit(2, 0, 5);
  first.setDegit(2, 1, 2);
  first.setDegit(2, 2, 3);
  Matrix second{3};
  second.setDegit(0, 0, -2);
  second.setDegit(0, 1, -5);
  second.setDegit(0, 2, -7);
  second.setDegit(1, 0, -6);
  second.setDegit(1, 1, -3);
  second.setDegit(1, 2, -4);
  second.setDegit(2, 0, -5);
  second.setDegit(2, 1, -2);
  second.setDegit(2, 2, -3);
  Matrix result{3};
  result.setDegit(0, 0, 0);
  result.setDegit(0, 1, 0);
  result.setDegit(0, 2, 0);
  result.setDegit(1, 0, 0);
  result.setDegit(1, 1, 0);
  result.setDegit(1, 2, 0);
  result.setDegit(2, 0, 0);
  result.setDegit(2, 1, 0);
  result.setDegit(2, 2, 0);
  Matrix summa = first + second;
  for (int i = 0; i < second.getRow(); i++) {
    for (int j = 0; j < second.getColum(); j++) {
      GTEST_ASSERT_EQ(summa.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_sub, example_1) {
  Matrix first{3};
  first.setDegit(0, 0, 2);
  first.setDegit(0, 1, 5);
  first.setDegit(0, 2, 7);
  first.setDegit(1, 0, 6);
  first.setDegit(1, 1, 3);
  first.setDegit(1, 2, 4);
  first.setDegit(2, 0, 5);
  first.setDegit(2, 1, 2);
  first.setDegit(2, 2, 3);
  Matrix second{3};
  second.setDegit(0, 0, 2);
  second.setDegit(0, 1, 5);
  second.setDegit(0, 2, 7);
  second.setDegit(1, 0, 6);
  second.setDegit(1, 1, 3);
  second.setDegit(1, 2, 4);
  second.setDegit(2, 0, 5);
  second.setDegit(2, 1, 2);
  second.setDegit(2, 2, 3);
  Matrix result{3};
  result.setDegit(0, 0, 0);
  result.setDegit(0, 1, 0);
  result.setDegit(0, 2, 0);
  result.setDegit(1, 0, 0);
  result.setDegit(1, 1, 0);
  result.setDegit(1, 2, 0);
  result.setDegit(2, 0, 0);
  result.setDegit(2, 1, 0);
  result.setDegit(2, 2, 0);
  Matrix summa = first - second;
  for (int i = 0; i < second.getRow(); i++) {
    for (int j = 0; j < second.getColum(); j++) {
      GTEST_ASSERT_EQ(summa.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_brackets, example_1) {
  Matrix first(1);
  first(0, 0) = 15;
  Matrix result(1);
  result(0, 0) = 15;
  GTEST_ASSERT_EQ(first.getDigit(0, 0), result.getDigit(0, 0));
}

TEST(operator_brackets, example_2) {
  Matrix first(2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix result(2);
  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 3;
  result(1, 1) = 4;
  for (int i = 0; i < result.getRow(); i++) {
    for (int j = 0; j < result.getColum(); j++) {
      GTEST_ASSERT_EQ(first.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_mult_number, example_1) {
  Matrix first(2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix result(2);
  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 3;
  result(1, 1) = 4;
  double n = 1.0;
  first = first * n;
  for (int i = 0; i < result.getRow(); i++) {
    for (int j = 0; j < result.getColum(); j++) {
      GTEST_ASSERT_EQ(first.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_mult_number, example_2) {
  Matrix first(2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix result(2);
  result(0, 0) = 2;
  result(0, 1) = 4;
  result(1, 0) = 6;
  result(1, 1) = 8;
  double n = 2.0;
  first = first * n;
  for (int i = 0; i < result.getRow(); i++) {
    for (int j = 0; j < result.getColum(); j++) {
      GTEST_ASSERT_EQ(first.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_mult_number, example_3) {
  Matrix first(2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix result(2);
  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;
  double n = 0.0;
  first = first * n;
  for (int i = 0; i < result.getRow(); i++) {
    for (int j = 0; j < result.getColum(); j++) {
      GTEST_ASSERT_EQ(first.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_mult_number_rvalue, example_4) {
  Matrix first(2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(1, 0) = 3;
  first(1, 1) = 4;
  Matrix result(2);
  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;
  first = first * 0.0;
  for (int i = 0; i < result.getRow(); i++) {
    for (int j = 0; j < result.getColum(); j++) {
      GTEST_ASSERT_EQ(first.getDigit(i, j), result.getDigit(i, j));
    }
  }
}

TEST(operator_mult_matrix, example_1) {
  Matrix *first = new Matrix(2);
  (*first)(0, 0) = 1;
  (*first)(0, 1) = 2;
  (*first)(1, 0) = 3;
  (*first)(1, 1) = 4;
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 1;
  (*second)(1, 0) = 1;
  (*second)(1, 1) = 1;
  Matrix *result = new Matrix(2);
  (*result)(0, 0) = 3;
  (*result)(0, 1) = 3;
  (*result)(1, 0) = 7;
  (*result)(1, 1) = 7;
  *first = (*first) * (*second);
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(operator_sum_eq, example_1) {
  Matrix *first = new Matrix(2);
  (*first)(0, 0) = 1;
  (*first)(0, 1) = 2;
  (*first)(1, 0) = 3;
  (*first)(1, 1) = 4;
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 1;
  (*second)(1, 0) = 1;
  (*second)(1, 1) = 1;
  Matrix *result = new Matrix(2);
  (*result)(0, 0) = 2;
  (*result)(0, 1) = 3;
  (*result)(1, 0) = 4;
  (*result)(1, 1) = 5;
  *first += (*second);
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(operator_sub_eq, example_1) {
  Matrix *first = new Matrix(2);
  (*first)(0, 0) = 1;
  (*first)(0, 1) = 2;
  (*first)(1, 0) = 3;
  (*first)(1, 1) = 4;
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  Matrix *result = new Matrix(2);
  (*result)(0, 0) = 0;
  (*result)(0, 1) = 0;
  (*result)(1, 0) = 0;
  (*result)(1, 1) = 0;
  *first -= (*second);
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(operator_eq_move, example_1) {
  Matrix *first = new Matrix(2);
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  Matrix *result = new Matrix(2);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  *first = std::move(*second);
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(constructor_move, example_1) {
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  Matrix *result = new Matrix(2);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  Matrix *first = new Matrix(std::move(*second));
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(first->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (first);
  delete (second);
  delete (result);
}

TEST(setRow_scale, example_1) {
  Matrix *second = new Matrix(2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  second->setRow(3);
  Matrix *result = new Matrix(3, 2);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(2, 0) = 0;
  (*result)(2, 1) = 0;
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(second->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (second);
  delete (result);
}

TEST(setRow_scale, example_2) {
  Matrix *second = new Matrix(3, 2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  (*second)(2, 0) = 5;
  (*second)(2, 1) = 8;
  second->setRow(2);
  Matrix *result = new Matrix(2, 2);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(second->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (second);
  delete (result);
}

TEST(setColum_scale, example_1) {
  Matrix *second = new Matrix(2, 3);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(0, 2) = 3;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  (*second)(1, 2) = 8;
  second->setColum(2);
  Matrix *result = new Matrix(2, 2);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(second->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (second);
  delete (result);
}

TEST(setColum_scale, example_2) {
  Matrix *second = new Matrix(2, 2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  second->setColum(3);
  Matrix *result = new Matrix(2, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 0;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(1, 2) = 0;
  for (int i = 0; i < result->getRow(); i++) {
    for (int j = 0; j < result->getColum(); j++) {
      GTEST_ASSERT_EQ(second->getDigit(i, j), result->getDigit(i, j));
    }
  }
  delete (second);
  delete (result);
}

TEST(catch_exaption_square_constr, example_1) {
  EXPECT_THROW(new Matrix(-2), std::invalid_argument);
}

TEST(catch_exaption_square_constr, example_2) {
  EXPECT_THROW(new Matrix(0), std::invalid_argument);
}

TEST(catch_exaption_double_constr, example_1) {
  EXPECT_THROW(new Matrix(2, -2), std::invalid_argument);
}

TEST(catch_exaption_double_constr, example_2) {
  EXPECT_THROW(new Matrix(-2, 2), std::invalid_argument);
}

TEST(catch_exaption_double_constr, example_3) {
  EXPECT_THROW(new Matrix(0, 0), std::invalid_argument);
}

TEST(catch_exaption_sum_matrix, example_4) {
  Matrix second(2, 2);
  second(0, 0) = 1;
  second(0, 1) = 2;
  second(1, 0) = 3;
  second(1, 1) = 4;
  Matrix result(2, 3);
  result(0, 0) = 1;
  result(0, 1) = 2;
  result(0, 2) = 0;
  result(1, 0) = 3;
  result(1, 1) = 4;
  result(1, 2) = 0;
  EXPECT_THROW(second.sum_matrix(result), std::invalid_argument);
}

TEST(catch_exaption_sub_matrix, example_5) {
  Matrix *second = new Matrix(2, 2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  Matrix *result = new Matrix(2, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 0;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(1, 2) = 0;
  EXPECT_THROW(second->sub_matrix(*result), std::invalid_argument);
  delete (second);
  delete (result);
}

TEST(catch_exaption_mul_matrix, example_6) {
  Matrix *second = new Matrix(2, 2);
  (*second)(0, 0) = 1;
  (*second)(0, 1) = 2;
  (*second)(1, 0) = 3;
  (*second)(1, 1) = 4;
  Matrix *result = new Matrix(2, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 0;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(1, 2) = 0;
  EXPECT_THROW(result->mul_matrix(*second), std::logic_error);
  delete (second);
  delete (result);
}

TEST(catch_exaption_determinant, example_7) {
  Matrix *result = new Matrix(2, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 0;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(1, 2) = 0;
  EXPECT_THROW(result->determinant(), std::logic_error);
  delete (result);
}

TEST(catch_exaption_calc_complements, example_8) {
  Matrix *result = new Matrix(2, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 0;
  (*result)(1, 0) = 3;
  (*result)(1, 1) = 4;
  (*result)(1, 2) = 0;
  EXPECT_THROW(result->calc_complements(), std::logic_error);
  delete (result);
}

TEST(catch_exaption_inverse, example_9) {
  Matrix *result = new Matrix(3, 3);
  (*result)(0, 0) = 1;
  (*result)(0, 1) = 2;
  (*result)(0, 2) = 3;
  (*result)(1, 0) = 4;
  (*result)(1, 1) = 5;
  (*result)(1, 2) = 6;
  (*result)(2, 0) = 7;
  (*result)(2, 1) = 8;
  (*result)(2, 2) = 9;
  EXPECT_THROW(result->inverse_matrix(), std::logic_error);
  delete (result);
}

TEST(catch_exaption_bracket_operator, example_10) {
  Matrix *result = new Matrix(3, 3);
  EXPECT_THROW((*result)(3, 4) = 2, std::logic_error);
  delete (result);
}

TEST(catch_exaption_bracket_operator, example_11) {
  Matrix *result = new Matrix(3, 3);
  EXPECT_THROW((*result)(-3, 4) = 2, std::logic_error);
  delete (result);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  return 0;
}
