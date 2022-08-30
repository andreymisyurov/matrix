#include "matrix_oop.hpp"

Matrix::Matrix(int value) : Matrix(value, value) {}
Matrix::Matrix(int value_row, int value_colum) {
  if (value_colum < 1 || value_row < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  }

  m_row = value_row;
  m_column = value_colum;
  create();
}
Matrix::Matrix(Matrix &&other) { *this = other; }
Matrix::Matrix(const Matrix &other) { *this = other; }

void Matrix::setRow(int new_row) {
  if (new_row < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  } else if (m_row == 0) {
    this->m_row = new_row;
    create();
  } else if (new_row < m_row) {
    Matrix temp(new_row, m_column);
    copy_matrix(new_row, m_column, temp, *this);
    *this = temp;
  } else if (new_row > m_row) {
    Matrix temp(new_row, m_column);
    copy_matrix(m_row, m_column, temp, *this);
    *this = temp;
  }
}

void Matrix::setColum(int new_colum) {
  if (new_colum < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  } else if (m_column == 0) {
    this->m_column = new_colum;
    create();
  } else if (new_colum < m_column) {
    Matrix temp(m_row, new_colum);
    copy_matrix(m_row, new_colum, temp, *this);
    *this = temp;
  } else if (new_colum > m_column) {
    Matrix temp(m_row, new_colum);
    copy_matrix(m_row, m_column, temp, *this);
    *this = temp;
  }
}
int Matrix::getColum() { return m_column; }
int Matrix::getRow() { return m_row; }

Matrix Matrix::inverse_matrix() {
  double d = determinant();
  if (d == 0) {
    throw std::logic_error("Matrix's determinant is zero");
  }
  Matrix result = calc_complements();
  Matrix result2 = result.transpose();
  result2.mul_number(1. / d);
  return result2;
}
Matrix Matrix::calc_complements() {
  if (m_column != m_row) {
    throw std::logic_error("Matrix isn't square");
  }
  Matrix result(m_row, m_column);
  for (int i = 0; i < result.m_row; i++) {
    for (int j = 0; j < result.m_column; j++) {
      Matrix temp = this->getMinor(i, j);
      int sign = (i + j) % 2 == 0 ? 1 : -1;
      result.matrix[i][j] = sign * temp.determinant();
    }
  }
  return result;
}
double Matrix::determinant() {
  if (m_column != m_row) {
    throw std::logic_error("Matrix isn't square");
  }
  double result = 0.0;
  if (m_row == 1) {
    result = matrix[0][0];
  } else if (m_row == 2) {
    result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  } else {
    int j = 0;
    for (int i = 0; i < m_column; i++) {
      Matrix temp = this->getMinor(i, j);
      int sign = ((i + j) % 2 == 0) ? (1) : -1;
      double piece = sign * matrix[i][j] * temp.determinant();
      result += piece;
    }
  }
  return result;
}
bool Matrix::eq_matrix(const Matrix &other) const {
  bool result = true;
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_column; j++) {
      double diff = this->matrix[i][j] - other.matrix[i][j];
      if (fabs(diff) > EPS) {
        result = false;
      }
    }
  }
  return result;
}
void Matrix::sum_matrix(const Matrix &other) {
  if (m_row != other.m_row || m_column != other.m_column) {
    throw std::invalid_argument("Matrix have different rows or columns");
  }
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_column; j++) {
      this->matrix[i][j] += other.matrix[i][j];
    }
  }
}
void Matrix::sub_matrix(const Matrix &other) {
  if (m_row != other.m_row || m_column != other.m_column) {
    throw std::invalid_argument("Matrix have different rows or columns");
  }
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_column; j++) {
      this->matrix[i][j] -= other.matrix[i][j];
    }
  }
}
void Matrix::mul_number(const double num) {
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_column; j++) {
      matrix[i][j] *= num;
    }
  }
}
void Matrix::mul_matrix(const Matrix &other) {
  if (m_column != other.m_row) {
    throw std::logic_error("Not equals rows and column");
  }
  Matrix temp(m_row, other.m_column);
  std::swap(*this, temp);
  for (int i = 0; i < m_row; i++) {
    for (int j = 0; j < m_column; j++) {
      matrix[i][j] = 0;
      for (int k = 0; k < temp.m_column; k++) {
        matrix[i][j] += temp.matrix[i][k] * other.matrix[k][j];
      }
    }
  }
}
Matrix Matrix::transpose() {
  Matrix result(m_column, m_row);
  for (int i = 0; i < result.m_row; i++) {
    for (int j = 0; j < result.m_column; j++) {
      result.matrix[i][j] = matrix[j][i];
    }
  }
  return result;
}

bool Matrix::operator==(const Matrix &other) { return eq_matrix(other); }

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
Matrix Matrix::operator*(const double &x) {
  Matrix temp(*this);
  temp.mul_number(x);
  return temp;
}
Matrix Matrix::operator*(double &&x) {
  Matrix temp(*this);
  temp.mul_number(x);
  return temp;
}
Matrix Matrix::operator+=(const Matrix &other) {
  this->sum_matrix(other);
  return *this;
}
Matrix Matrix::operator-=(const Matrix &other) {
  this->sub_matrix(other);
  return *this;
}
double &Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i > m_row || j > m_column) {
    throw std::logic_error("Nothing to get");
  }
  return this->matrix[i][j];
}

void Matrix::remove() {
  for (int i = 0; i < m_row; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  m_row = 0;
  m_column = 0;
  matrix = nullptr;
}
void Matrix::create() {
  if (m_row > 0 && m_column > 0) {
    delete (matrix);
    matrix = new double *[m_row];
    for (int i = 0; i < m_row; i++) {
      matrix[i] = new double[m_column];
      std::memset(matrix[i], 0, sizeof(double) * m_column);
    }
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
    for (int k = 0; k < m_column; k++) {
      if (k == j) continue;
      minor.matrix[countI][countJ] = matrix[l][k];
      countJ = (countJ + 1) % minor.m_column;
    }
    countI = (countI + 1) % minor.m_row;
  }
  return minor;
}
void Matrix::copy_matrix(int row, int colum, Matrix const &left,
                         Matrix const &right) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      left.matrix[i][j] = right.matrix[i][j];
    }
  }
}
