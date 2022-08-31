#include "matrix_oop.hpp"

using namespace victoriv;

Matrix::Matrix(int value) : Matrix(value, value) {}
Matrix::Matrix(int value_row, int value_column) {
  checkConstructor(value_column, value_row);
  m_row = value_row;
  m_column = value_column;
  create();
}

Matrix::Matrix(Matrix &&other) { *this = other; }

Matrix::Matrix(const Matrix &other) { *this = other; }

void Matrix::setRow(int new_row) {
  checkSetter(new_row);
  if (m_row == new_row) return;
  Matrix temp(new_row, m_column);
  int real_row = (new_row < m_row) ? new_row : m_row;
  copy_matrix(real_row, m_column, temp, *this);

  *this = temp;
}

void Matrix::checkSetter(int value) {
  if (value < 1) throw std::invalid_argument("Bad value for row or colum.");
}

void Matrix::setColum(int new_column) {
  checkSetter(new_column);
  if (m_row == new_column) return;
  Matrix temp(m_row, new_column);
  int real_column = (new_column < m_column) ? new_column : m_column;
  copy_matrix(m_row, real_column, temp, *this);

  *this = temp;
}

Matrix Matrix::inverse_matrix() {
  double d = determinant();
  if (d == 0) {
    throw std::logic_error("Matrix's determinant is zero");
  }
  Matrix temp = calc_complements();
  Matrix result = temp.transpose();
  result.mul_number(1. / d);
  return result;
}

Matrix Matrix::calc_complements() {
  checkSquare();
  Matrix result(m_row, m_column);
  double sign = 0;
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      Matrix temp = getMinor(i, j);
      sign = (i + j) & 1 ? -1 : 1;
      result.matrix[i][j] = sign * temp.determinant();
    }
  }
  return result;
}

double Matrix::determinant() {
  checkSquare();
  double result = 0.0;
  if (m_row == 1) {
    result = matrix[0][0];
  } else if (m_row == 2) {
    result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  } else {
    int j = 0;
    double piece = 0.0;
    double sign = 0.0;
    for (int i = 0; i < m_column; ++i) {
      Matrix temp = getMinor(i, j);
      sign = (i + j) & 1 ? -1.0 : 1.0;
      piece = sign * matrix[i][j] * temp.determinant();
      result += piece;
    }
  }
  return result;
}

bool Matrix::eq_matrix(const Matrix &other) const {
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      if (fabs(matrix[i][j] - other.matrix[i][j]) > EPS) return false;
    }
  }
  return true;
}

void Matrix::sum_matrix(const Matrix &other) {
  checkData(other);
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      matrix[i][j] += other.matrix[i][j];
    }
  }
}

void Matrix::sub_matrix(const Matrix &other) {
  checkData(other);
  Matrix result(other);
  result *= -1.;
  *this += result;
}

void Matrix::mul_number(const double num) {
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      matrix[i][j] *= num;
    }
  }
}

void Matrix::mul_matrix(const Matrix &other) {
  checkForMult(other);
  Matrix result(m_row, other.m_column);
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      result.matrix[i][j] = 0;
      for (int k = 0; k < m_column; ++k) {
        result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
      }
    }
  }

  std::swap(*this, result);
}

Matrix Matrix::transpose() {
  Matrix result(m_column, m_row);
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      result.matrix[i][j] = matrix[j][i];
    }
  }
  return result;
}

bool Matrix::operator==(const Matrix &other) const { return eq_matrix(other); }

Matrix &Matrix::operator=(const Matrix &other) {
  Matrix temp(other.m_row, other.m_column);
  copy_matrix(other.m_row, other.m_column, temp, other);

  std::swap(m_row, temp.m_row);
  std::swap(m_column, temp.m_column);
  std::swap(matrix, temp.matrix);
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) {
  if (this != &other) {
    std::swap(m_column, other.m_column);
    std::swap(m_row, other.m_row);
    std::swap(matrix, other.matrix);
  }
  return *this;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix temp(*this);
  temp.sub_matrix(other);
  return temp;
}

Matrix Matrix::operator+(const Matrix &other) {
  Matrix temp(*this);
  temp.sum_matrix(other);
  return temp;
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix temp(*this);
  temp.mul_matrix(other);
  return temp;
}

Matrix Matrix::operator*(double &value) {
  Matrix temp(*this);
  temp.mul_number(value);
  return temp;
}

Matrix Matrix::operator*(double &&value) {
  Matrix temp(*this);
  temp.mul_number(value);
  return temp;
}

Matrix Matrix::operator+=(const Matrix &other) {
  sum_matrix(other);
  return *this;
}

Matrix Matrix::operator-=(const Matrix &other) {
  sub_matrix(other);
  return *this;
}

Matrix Matrix::operator*=(double &&value) {
  mul_number(value);
  return *this;
}

Matrix Matrix::operator*=(double &value) {
  mul_number(value);
  return *this;
}

double &Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= m_row || j >= m_column) {
    throw std::logic_error("Nothing to get");
  }
  return matrix[i][j];
}

Matrix victoriv::operator*(double &&value, const Matrix &other) {
  return Matrix(other.m_row, other.m_column) * value;
}

Matrix victoriv::operator*(double &value, const Matrix &other) {
  return Matrix(other.m_row, other.m_column) * value;
}

void Matrix::remove() {
  for (int i = 0; i < m_row; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void Matrix::create() {
  matrix = new double *[m_row];
  for (int i = 0; i < m_row; ++i) {
    matrix[i] = new double[m_column];
    std::memset(matrix[i], 0, sizeof(double) * m_column);
  }
}

Matrix Matrix::getMinor(int i, int j) {
  Matrix minor(m_row - 1, m_column - 1);
  int countI = 0;
  int countJ = 0;
  for (int l = 0; l < m_row; l++) {
    if (l == i) {
      continue;
    }
    for (int k = 0; k < m_column; ++k) {
      if (k == j) continue;
      minor.matrix[countI][countJ] = matrix[l][k];
      countJ = (countJ + 1) % minor.m_column;
    }
    countI = (countI + 1) % minor.m_row;
  }
  return minor;
}

void Matrix::copy_matrix(int row, int colum, const Matrix &left,
                         const Matrix &right) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < colum; ++j) {
      left.matrix[i][j] = right.matrix[i][j];
    }
  }
}

void Matrix::checkData(const Matrix &other) {
  if (m_row != other.m_row || m_column != other.m_column)
    throw std::invalid_argument("Matrix have different rows or columns");
}

void Matrix::checkForMult(const Matrix &other) {
  if (m_column != other.m_row)
    throw std::logic_error("Not equals rows and column");
}

void Matrix::checkSquare() {
  if (m_column != m_row) throw std::logic_error("Matrix isn't square");
}

void Matrix::checkConstructor(int value_row, int value_column) {
  if (value_column < 1 || value_row < 1)
    throw std::invalid_argument("Bad value for row or colum.");
}
