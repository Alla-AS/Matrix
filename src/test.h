#ifndef TEST_H_
#define TEST_H_

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class test : public ::testing::Test {
 protected:
  S21Matrix *a;
  S21Matrix *b;
  S21Matrix *c;

  test() {
    a = new S21Matrix(3, 3);
    b = new S21Matrix(3, 3);
    c = new S21Matrix(3, 3);
  }
  ~test() {
    delete a;
    delete b;
    delete c;
  }
  void SetUp() {
    for (auto i = 0; i < 3; i++) {
      for (auto j = 0; j < 3; j++) {
        (*a)(i, j) = i * 3 + j + 1;
      }
    }
    for (auto i = 0; i < 3; i++) {
      for (auto j = 0; j < 3; j++) {
        (*b)(i, j) = i * 3 + j;
      }
    }
    (*c)(0,0) = 1;
    (*c)(0,1) = 2;
    (*c)(0,2) = 4;
    (*c)(1,0) = 3;
    (*c)(1,1) = 3;
    (*c)(2,0) = 2;
    (*c)(2,1) = 4;
    (*c)(2,2) = 4;
  }
  // void TearDown() {}
};

#endif  // TEST_H_
