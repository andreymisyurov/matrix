#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

namespace victoriv {

inline constexpr auto EPS = 1e-6;

class Matrix {
 public:
  auto getColum()       -> int { return m_column; };
  auto getRow()         -> int { return m_row; };
  auto setRow(int x)    -> void;
  auto setColum(int x)  -> void;

 public:
  Matrix() = delete;
  explicit Matrix(int value);
  Matrix(int value_row, int value_column);
  Matrix(Matrix &&other);
  Matrix(const Matrix &other);
  ~Matrix() { remove(); }

 public:
  auto eqMatrix(const Matrix &other) const  -> bool;
  auto sumMatrix(const Matrix &other)       -> void;
  auto subMatrix(const Matrix &other)       -> void;
  auto mulNumber(const double num)          -> void;
  auto mulMatrix(const Matrix &other)       -> void;
  auto determinant()                        -> double;
  auto transpose()                          -> Matrix;
  auto calcComplements()                    -> Matrix;
  auto inverseMatrix()                      -> Matrix;

 public:
  auto operator=(const Matrix &other)       -> Matrix &;
  auto operator=(Matrix &&other)            -> Matrix &;
  auto operator+=(const Matrix &other)      -> Matrix;
  auto operator-=(const Matrix &other)      -> Matrix;
  auto operator*=(double &&value)           -> Matrix;
  auto operator*=(double &value)            -> Matrix;
  auto operator+(const Matrix &other)       -> Matrix;
  auto operator-(const Matrix &other)       -> Matrix;
  auto operator*(const Matrix &other)       -> Matrix;
  auto operator*(double &value)             -> Matrix;
  auto operator*(double &&value)            -> Matrix;
  auto operator()(int i, int j)             -> double &;
  auto operator==(const Matrix &other) const                    -> bool;
  auto friend operator*(double &&value, const Matrix &other)    -> Matrix;
  auto friend operator*(double &value, const Matrix &other)     -> Matrix;


 private:
  auto checkData(const Matrix &other)                       -> void;
  auto checkForMult(const Matrix &other)                    -> void;
  auto checkSquare()                                        -> void;
  auto checkSetter(int value)                               -> void;
  auto checkConstructor(int value_row, int value_column)    -> void;
  auto create()                                             -> void;
  auto remove()                                             -> void;
  auto getMinor(int i, int j)                               -> Matrix;
  auto static copyMatrix(int row, int m_column,
            const Matrix &left, const Matrix &right)        -> void;

 private:
  int m_column = 0;
  int m_row = 0;
  double **m_matrix = nullptr;
};

}  // namespace victoriv

#endif  // SRC_S21_MATRIX_OOP_H_
