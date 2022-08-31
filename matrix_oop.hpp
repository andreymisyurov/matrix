#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

namespace victoriv {

inline constexpr auto EPS = 1e-6;

class Matrix {
 public:
  int getColum() { return m_column; };
  int getRow() { return m_row; };
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
  Matrix operator*=(double &&value);
  Matrix operator*=(double &value);
  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(double &value);
  Matrix operator*(double &&value);
  Matrix friend operator*(double &&value, const Matrix &other);
  friend Matrix operator*(double &value, const Matrix &other);
  double &operator()(int i, int j);
  bool operator==(const Matrix &other) const;

 private:
  void checkData(const Matrix &other);
  void checkForMult(const Matrix &other);
  void checkSquare();
  void checkSetter(int value);
  void checkConstructor(int value_row, int value_column);
  void create();
  void remove();
  Matrix getMinor(int i, int j);
  static void copy_matrix(int row, int m_column, const Matrix &left,
                          const Matrix &right);

 private:
  int m_column = 0;
  int m_row = 0;
  double **matrix = nullptr;
};

}  // namespace victoriv

#endif  // SRC_S21_MATRIX_OOP_H_
