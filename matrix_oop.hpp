#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

inline constexpr auto EPS = 1e-6;

class Matrix {
 public:
  class Invalid : std::exception {};

 public:
  int getColum();
  int getRow();
  void setRow(int x);
  void setColum(int x);

 public:
  Matrix() = delete;
  explicit Matrix(int value);
  Matrix(int value_row, int value_column);
  Matrix(Matrix &&other);
  Matrix(const Matrix &other);
  ~Matrix() { remove(); }

 public:
  bool eq_matrix(const Matrix &other) const;
  void sum_matrix(const Matrix &other);
  void sub_matrix(const Matrix &other);
  void mul_number(const double num);
  void mul_matrix(const Matrix &other);
  Matrix transpose();
  double determinant();
  Matrix calc_complements();
  Matrix inverse_matrix();

 public:
  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other);
  Matrix operator+=(const Matrix &other);
  Matrix operator-=(const Matrix &other);
  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(const double &x);
  Matrix operator*(double &&x);
  double &operator()(int i, int j);
  bool operator==(const Matrix &other);

 private:
  void create();
  void remove();
  Matrix getMinor(int i, int j);
  static void copy_matrix(int row, int m_column, Matrix const &left,
                          Matrix const &right);

 private:
  int m_column = 0;
  int m_row = 0;
  double **matrix = nullptr;
};

#endif  // SRC_S21_MATRIX_OOP_H_
