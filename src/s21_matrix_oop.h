#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double* matrix_;   // pointer to the memory where the matrix will be allocated
  S21Matrix CutMatrix(int index) const;

 public:
  S21Matrix();                        // default constructor
  S21Matrix(int rows, int cols);      // parameterized constructor
  S21Matrix(const S21Matrix& other);  // copy cnstructor
  S21Matrix(S21Matrix&& other);       // move cnstructor
  ~S21Matrix();                       // destructor

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& other);
  bool operator==(const S21Matrix& other) const;
  double& operator()(int i, int j);  // index operator overload
  const double& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;

  // some public methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // void Output() const;
};

#endif