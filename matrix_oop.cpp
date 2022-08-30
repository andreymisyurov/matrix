#include "matrix_oop.hpp"

Matrix::Matrix() : colum(0), row(0) {}
Matrix::Matrix(int row_colum) : Matrix(row_colum, row_colum) {}
Matrix::Matrix(int set_row, int set_colum) {
  if (set_colum < 1 || set_row < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  }
  row = set_row;
  colum = set_colum;
  create();
}
Matrix::Matrix(Matrix &&other) {
  if (this != &other) {
    std::swap(this->colum, other.colum);
    std::swap(this->row, other.row);
    std::swap(this->matrix, other.matrix);
  }
}
Matrix::Matrix(const Matrix &other) { *this = other; }

void Matrix::setRow(int new_row) {
  if (new_row < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  } else if (row == 0) {
    this->row = new_row;
    create();
  } else if (new_row < row) {
    Matrix temp(new_row, colum);
    copy_matrix(new_row, colum, temp, *this);
    *this = temp;
  } else if (new_row > row) {
    Matrix temp(new_row, colum);
    copy_matrix(row, colum, temp, *this);
    *this = temp;
  }
}

void Matrix::setColum(int new_colum) {
  if (new_colum < 1) {
    throw std::invalid_argument("Bad value for row or colum.");
  } else if (colum == 0) {
    this->colum = new_colum;
    create();
  } else if (new_colum < colum) {
    Matrix temp(row, new_colum);
    copy_matrix(row, new_colum, temp, *this);
    *this = temp;
  } else if (new_colum > colum) {
    Matrix temp(row, new_colum);
    copy_matrix(row, colum, temp, *this);
    *this = temp;
  }
}
void Matrix::setDegit(int i, int j, double digit) { matrix[i][j] = digit; }
int Matrix::getColum() { return colum; }
int Matrix::getRow() { return row; }
double Matrix::getDigit(int i, int j) { return matrix[i][j]; }

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
  if (colum != row) {
    throw std::logic_error("Matrix isn't square");
  }
  Matrix result(row, colum);
  for (int i = 0; i < result.row; i++) {
    for (int j = 0; j < result.colum; j++) {
      Matrix temp = this->getMinor(i, j);
      int sign = (i + j) % 2 == 0 ? 1 : -1;
      result.matrix[i][j] = sign * temp.determinant();
    }
  }
  return result;
}
double Matrix::determinant() {
  if (colum != row) {
    throw std::logic_error("Matrix isn't square");
  }
  double result = 0.0;
  if (row == 1) {
    result = matrix[0][0];
  } else if (row == 2) {
    result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  } else {
    int j = 0;
    for (int i = 0; i < colum; i++) {
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
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      double diff = this->matrix[i][j] - other.matrix[i][j];
      if (fabs(diff) > EPS) {
        result = false;
      }
    }
  }
  return result;
}
void Matrix::sum_matrix(const Matrix &other) {
  if (row != other.row || colum != other.colum) {
    throw std::invalid_argument("Matrix have different rows or columns");
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      this->matrix[i][j] += other.matrix[i][j];
    }
  }
}
void Matrix::sub_matrix(const Matrix &other) {
  if (row != other.row || colum != other.colum) {
    throw std::invalid_argument("Matrix have different rows or columns");
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      this->matrix[i][j] -= other.matrix[i][j];
    }
  }
}
void Matrix::mul_number(const double num) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      matrix[i][j] *= num;
    }
  }
}
void Matrix::mul_matrix(const Matrix &other) {
  if (colum != other.row) {
    throw std::logic_error("Not equals rows and column");
  }
  Matrix temp(row, other.colum);
  std::swap(*this, temp);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      matrix[i][j] = 0;
      for (int k = 0; k < temp.colum; k++) {
        matrix[i][j] += temp.matrix[i][k] * other.matrix[k][j];
      }
    }
  }
}
Matrix Matrix::transpose() {
  Matrix result(colum, row);
  for (int i = 0; i < result.row; i++) {
    for (int j = 0; j < result.colum; j++) {
      result.matrix[i][j] = matrix[j][i];
    }
  }
  return result;
}

bool operator==(const Matrix &this_l, const Matrix &other) {
  return this_l.eq_matrix(other);
}
Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    remove();
    colum = other.colum;
    row = other.row;
    create();
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < colum; j++) {
        matrix[i][j] = other.matrix[i][j];
      }
    }
  }
  return *this;
}
Matrix &Matrix::operator=(Matrix &&other) {
  if (this != &other) {
    remove();
    std::swap(colum, other.colum);
    std::swap(row, other.row);
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
  if (i < 0 || j < 0 || i > row || j > colum) {
    throw std::logic_error("Nothing to get");
  }
  return this->matrix[i][j];
}

void Matrix::remove() {
  for (int i = 0; i < row; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  row = 0;
  colum = 0;
  matrix = nullptr;
}
void Matrix::create() {
  if (row > 0 && colum > 0) {
    delete (matrix);
    matrix = new double *[row];
    for (int i = 0; i < row; i++) {
      matrix[i] = new double[colum];
      std::memset(matrix[i], 0, sizeof(double) * colum);
    }
  }
}
Matrix Matrix::getMinor(int i, int j) {
  Matrix minor;
  minor.row = row - 1;
  minor.colum = colum - 1;
  minor.create();
  int countI = 0;
  int countJ = 0;
  for (int l = 0; l < row; l++) {
    if (l == i) {
      continue;
    }
    for (int k = 0; k < colum; k++) {
      if (k == j) continue;
      minor.matrix[countI][countJ] = matrix[l][k];
      countJ = (countJ + 1) % minor.colum;
    }
    countI = (countI + 1) % minor.row;
  }
  return minor;
}
void copy_matrix(int row, int colum, Matrix const &left, Matrix const &right) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < colum; j++) {
      left.matrix[i][j] = right.matrix[i][j];
    }
  }
}
