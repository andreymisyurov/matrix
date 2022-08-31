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
  copyMatrix(real_row, m_column, temp, *this);

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
  copyMatrix(m_row, real_column, temp, *this);

  *this = temp;
}

Matrix Matrix::inverseMatrix() {
  double d = determinant();
  if (d == 0) {
    throw std::logic_error("Matrix's determinant is zero");
  }
  Matrix temp = calcComplements();
  Matrix result = temp.transpose();
  result.mulNumber(1. / d);
  return result;
}

Matrix Matrix::calcComplements() {
  checkSquare();
  Matrix result(m_row, m_column);
  double sign = 0;
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      Matrix temp = getMinor(i, j);
      sign = (i + j) & 1 ? -1 : 1;
      result.m_matrix[i][j] = sign * temp.determinant();
    }
  }
  return result;
}

double Matrix::determinant() {
  checkSquare();
  double result = 0.0;
  if (m_row == 1) {
    result = m_matrix[0][0];
  } else if (m_row == 2) {
    result = m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
  } else {
    int j = 0;
    double piece = 0.0;
    double sign = 0.0;
    for (int i = 0; i < m_column; ++i) {
      Matrix temp = getMinor(i, j);
      sign = (i + j) & 1 ? -1.0 : 1.0;
      piece = sign * m_matrix[i][j] * temp.determinant();
      result += piece;
    }
  }
  return result;
}

bool Matrix::eqMatrix(const Matrix &other) const {
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      if (fabs(m_matrix[i][j] - other.m_matrix[i][j]) > EPS) return false;
    }
  }
  return true;
}

void Matrix::sumMatrix(const Matrix &other) {
  checkData(other);
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      m_matrix[i][j] += other.m_matrix[i][j];
    }
  }
}

void Matrix::subMatrix(const Matrix &other) {
  checkData(other);
  Matrix result(other);
  result *= -1.;
  *this += result;
}

void Matrix::mulNumber(const double num) {
  for (int i = 0; i < m_row; ++i) {
    for (int j = 0; j < m_column; ++j) {
      m_matrix[i][j] *= num;
    }
  }
}

void Matrix::mulMatrix(const Matrix &other) {
  checkForMult(other);
  Matrix result(m_row, other.m_column);
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      result.m_matrix[i][j] = 0;
      for (int k = 0; k < m_column; ++k) {
        result.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
      }
    }
  }

  std::swap(*this, result);
}

Matrix Matrix::transpose() {
  Matrix result(m_column, m_row);
  for (int i = 0; i < result.m_row; ++i) {
    for (int j = 0; j < result.m_column; ++j) {
      result.m_matrix[i][j] = m_matrix[j][i];
    }
  }
  return result;
}

bool Matrix::operator==(const Matrix &other) const { return eqMatrix(other); }

Matrix &Matrix::operator=(const Matrix &other) {
  Matrix temp(other.m_row, other.m_column);
  copyMatrix(other.m_row, other.m_column, temp, other);

  std::swap(m_row, temp.m_row);
  std::swap(m_column, temp.m_column);
  std::swap(m_matrix, temp.m_matrix);
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) {
  if (this != &other) {
    std::swap(m_column, other.m_column);
    std::swap(m_row, other.m_row);
    std::swap(m_matrix, other.m_matrix);
  }
  return *this;
}

Matrix Matrix::operator-(const Matrix &other) {
  Matrix temp(*this);
  temp.subMatrix(other);
  return temp;
}

Matrix Matrix::operator+(const Matrix &other) {
  Matrix temp(*this);
  temp.sumMatrix(other);
  return temp;
}

Matrix Matrix::operator*(const Matrix &other) {
  Matrix temp(*this);
  temp.mulMatrix(other);
  return temp;
}

Matrix Matrix::operator*(double &value) {
  Matrix temp(*this);
  temp.mulNumber(value);
  return temp;
}

Matrix Matrix::operator*(double &&value) {
  Matrix temp(*this);
  temp.mulNumber(value);
  return temp;
}

Matrix Matrix::operator+=(const Matrix &other) {
  sumMatrix(other);
  return *this;
}

Matrix Matrix::operator-=(const Matrix &other) {
  subMatrix(other);
  return *this;
}

Matrix Matrix::operator*=(double &&value) {
  mulNumber(value);
  return *this;
}

Matrix Matrix::operator*=(double &value) {
  mulNumber(value);
  return *this;
}

double &Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= m_row || j >= m_column) {
    throw std::logic_error("Nothing to get");
  }
  return m_matrix[i][j];
}

Matrix victoriv::operator*(double &&value, const Matrix &other) {
  return Matrix(other.m_row, other.m_column) * value;
}

Matrix victoriv::operator*(double &value, const Matrix &other) {
  return Matrix(other.m_row, other.m_column) * value;
}

void Matrix::remove() {
  for (int i = 0; i < m_row; ++i) {
    delete[] m_matrix[i];
  }
  delete[] m_matrix;
}

void Matrix::create() {
  m_matrix = new double *[m_row];
  for (int i = 0; i < m_row; ++i) {
    m_matrix[i] = new double[m_column];
    std::memset(m_matrix[i], 0, sizeof(double) * m_column);
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
      minor.m_matrix[countI][countJ] = m_matrix[l][k];
      countJ = (countJ + 1) % minor.m_column;
    }
    countI = (countI + 1) % minor.m_row;
  }
  return minor;
}

void Matrix::copyMatrix(int row, int colum, const Matrix &left,
                        const Matrix &right) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < colum; ++j) {
      left.m_matrix[i][j] = right.m_matrix[i][j];
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
