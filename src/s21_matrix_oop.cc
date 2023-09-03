#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (this != &other) {
    matrix_ = new double[other.rows_ * other.cols_]();
    std::memcpy(matrix_, other.matrix_,
                other.rows_ * other.cols_ * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  if (this != &other) {
    other.matrix_ = nullptr;
    other.rows_ = other.cols_ = 0;
  }
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (this == &other) {
    return true;
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }

  for (int i = 0; i < (rows_ * cols_) && res; i++) {
    if (fabs(matrix_[i] - other.matrix_[i]) > 1e-7) {
      res = false;
    }
  }

  return res;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (other.matrix_ == nullptr) {
    throw std::out_of_range("Error, incorrect matrices");
  }
  if (this == &other) {
    return *this;
  }
  if (this->matrix_ != nullptr) {
    delete[] this->matrix_;
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;

  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (other.matrix_ == nullptr) {
    throw std::out_of_range("Error, incorrect matrices");
  }
  if (this == &other) {
    return (*this);
  }
  if (this->matrix_ != nullptr) {
    delete[] this->matrix_;
  }
  this->matrix_ = new double[other.rows_ * other.cols_];
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i * cols_ + j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i * cols_ + j];
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; ++i) {
    this->matrix_[i] = this->matrix_[i] + other.matrix_[i];
  }
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; i++) {
    this->matrix_[i] = this->matrix_[i] - other.matrix_[i];
  }
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_ * cols_; i++) {
    this->matrix_[i] = this->matrix_[i] * num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix res(rows_, other.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < other.cols_; j++) {
      for (auto k = 0; k < cols_; k++) {
        res.matrix_[i * other.cols_ + j] +=
            this->matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];
      }
    }
  }
  *this = move(res);
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res_(*this);
  res_.MulMatrix(other);
  return res_;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res_(*this);
  res_.MulNumber(num);
  return res_;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res_(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      res_.matrix_[j * rows_ + i] = this->matrix_[i * cols_ + j];
    }
  }
  return res_;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  S21Matrix res_matrix(rows_, cols_);
  for (auto i = 0; i < rows_ * cols_; ++i) {
    double det = this->CutMatrix(i).Determinant();
    res_matrix(i / rows_, i % cols_) = det * pow(-1, i);
  }
  return res_matrix;
}

S21Matrix S21Matrix::CutMatrix(int index) const {
  S21Matrix res(this->rows_ - 1, this->cols_ - 1);
  int k = 0;
  for (auto i = 0; i < this->rows_; i++) {
    if (i != (index / this->rows_)) {
      for (auto j = 0; j < this->cols_; j++) {
        if ((j != (index % this->rows_))) {
          res.matrix_[k] = this->matrix_[i * cols_ + j];
          k++;
        }
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  double res;
  if (rows_ == 1) {
    res = matrix_[0];
  } else if (rows_ == 2) {
    res = matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
  } else {
    double value = 0;
    int sign = 1;
    for (auto i = 0; i < cols_; ++i) {
      value += matrix_[i] * this->CutMatrix(i).Determinant() * sign;
      sign *= -1;
    }
    res = value;
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (matrix_ == nullptr) {
    throw std::out_of_range("Incorrect matrices");
  }
  double determ = this->Determinant();
  if (!determ) {
    throw std::out_of_range("Inverse matrix doesn't exist");
  }
  return this->CalcComplements().Transpose() * (1.0 / determ);
}

// void S21Matrix::Output() const {
//   for (auto i = 0; i < rows_ * cols_; ++i) {
//     cout << this->matrix_[i] << "\t";
//     if (i % cols_ == (cols_ - 1)) {
//       cout << endl;
//     }
//   }
//   cout << endl;
// }

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (matrix_ == nullptr) {
    throw std::out_of_range("Incorrect matrix");
  }
  S21Matrix tmp(rows, this->cols_);
  for (auto i = 0, j = 0; i < rows * cols_ && j < rows_ * cols_; ++i, ++j) {
    tmp.matrix_[i] = matrix_[j];
  }
  delete[] this->matrix_;
  this->matrix_ = tmp.matrix_;
  tmp.matrix_ = nullptr;
  this->rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
  if (!matrix_) {
    throw std::out_of_range("Incorrect matrix");
  }
  S21Matrix tmp(rows_, cols);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0, k = 0; j < cols && k < this->cols_; ++j, ++k) {
      tmp.matrix_[i * cols + j] = matrix_[i * cols_ + k];
    }
  }
  delete[] this->matrix_;
  this->matrix_ = tmp.matrix_;
  tmp.matrix_ = nullptr;
  this->cols_ = cols;
}