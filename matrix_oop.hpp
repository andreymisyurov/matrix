#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

inline constexpr auto EPS = 1e-6;

class Matrix {
 public:
  // getters and setters
  int getColum();
  int getRow();
  double getDigit(int i, int j);
  void setRow(int x);
  void setColum(int x);
  void setDegit(int i, int j, double digit);

 public:
  // constructors
  Matrix();
  explicit Matrix(int row_colum);
  Matrix(int set_row, int set_colum);
  Matrix(Matrix &&other);
  Matrix(const Matrix &other);
  ~Matrix() { remove(); }

 public:
  // calculate funcs
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
  // temp func
  void create();
  void remove();
  Matrix getMinor(int i, int j);
  //   friend void copy_matrix(int row, int colum, Matrix &left,
  //                           Matrix &right);
  friend void copy_matrix(int row, int colum, Matrix const &left,
                          Matrix const &right);

 public:
  // operators
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
  int colum = 0;
  int row = 0;
  double **matrix = nullptr;
};

#endif  // SRC_S21_MATRIX_OOP_H_
