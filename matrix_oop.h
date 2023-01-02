//#ifndef SRC_S21_MATRIX_OOP_H_
//#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>


//namespace victoriv {

inline constexpr auto EPS = 1e-6;

template <typename T>
class Matrix {
 public:
  auto getColum()       -> int { return m_column; };
  auto getRow()         -> int { return m_row; };
//  auto setRow(int x)    -> void;
//  auto setColum(int x)  -> void;

 public:
//  Matrix() = delete;
  explicit Matrix(int value);
  Matrix(int value_row, int value_column);
//  Matrix(Matrix &&other);
  Matrix(const Matrix &other);
//  ~Matrix() { remove(); }

 public:
  auto eqMatrix(const Matrix<T> &other) const  -> bool;
  auto sumMatrix(const Matrix<T> &other)       -> void;
  auto subMatrix(const Matrix<T> &other)       -> void;
  auto mulNumber(T num)          -> void;
  auto mulMatrix(const Matrix<T> &other)       -> void;
  auto determinant()                        -> double;
  auto transpose()                          -> Matrix<T>;
  auto calcComplements()                    -> Matrix<T>;
  auto inverseMatrix()                      -> Matrix<T>;

 public:
  auto operator=(const Matrix<T> &other)       -> Matrix<T> &;
//  auto operator=(Matrix &&other)            -> Matrix &;
  auto operator+=(const Matrix<T> &other)      -> Matrix<T>;
//  auto operator-=(const Matrix &other)      -> Matrix;
//  auto operator*=(T &&value)           -> Matrix<T>;
  auto operator*=(const T &value)            -> Matrix<T>;
  auto operator+(const Matrix<T> &other)       -> Matrix<T>;
  auto operator-(const Matrix<T> &other)       -> Matrix<T>;
//  auto operator*(const Matrix<T> &other)       -> Matrix<T>;
  auto operator*(const T &value)             -> Matrix<T>;
//  auto operator*(T &&value)            -> Matrix<T>;
  auto operator()(int i, int j)             -> T &;
  auto operator==(const Matrix<T> &other) const                    -> bool;
//  auto friend operator*(double &&value, const Matrix &other)    -> Matrix;
//  auto friend operator*(double &value, const Matrix &other)     -> Matrix;


 private:
  auto checkData(const Matrix<T> &other)                       -> void;
  auto checkForMult(const Matrix<T> &other)                    -> void;
  auto checkSquare()                                        -> void;
//  auto checkSetter(int value)                               -> void;
  auto checkConstructor(int value_row, int value_column)    -> void;
  auto create()                                             -> void;
//  auto remove()                                             -> void;
  auto getMinor(int i, int j)                               -> Matrix<T>;
  auto static copyMatrix(int row, int m_column,
            const Matrix &left, const Matrix &right)        -> void;

 private:
  int m_column = 0;
  int m_row = 0;
  T **m_matrix = nullptr;
};
//}  // namespace victoriv

//#endif  // SRC_S21_MATRIX_OOP_H_

#include "matrix_oop.hpp"
