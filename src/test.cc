#include "test.h"

TEST_F(test, operator_equality) {
  S21Matrix expected(3, 3);

  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 3; j++) {
      expected(i, j) = i * 3 + j + 1;
    }
  }

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, operator_equal) {
  *a = *b;
  *a = *a;

  EXPECT_EQ(1, *a == *b);

  *b = move(*c);

  EXPECT_THROW(*a = *c, std::out_of_range);
}

TEST_F(test, operator_move_equal) {
  *c = *b;

  *a = move(*b);
  *a = move(*a);

  EXPECT_EQ(1, *a == *c);
  EXPECT_EQ(0, *a == *b);
  EXPECT_THROW(*a = move(*b), std::out_of_range);
}

TEST_F(test, operator_indexation) {
  (*a)(0, 0) = 5;

  EXPECT_EQ(5, (*a)(0, 0));
  EXPECT_THROW((*a)(-1, 2), std::out_of_range);
}

TEST_F(test, operator_const_indexation) {
  const S21Matrix x(2, 2);

  EXPECT_EQ(0, x(0, 0));
  EXPECT_THROW(x(-1, 2), std::out_of_range);
}

TEST_F(test, operator_plus_equal) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 3;
  expected(0, 2) = 5;
  expected(1, 0) = 7;
  expected(1, 1) = 9;
  expected(1, 2) = 11;
  expected(2, 0) = 13;
  expected(2, 1) = 15;
  expected(2, 2) = 17;

  *a += *b;

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, operator_plus) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 3;
  expected(0, 2) = 5;
  expected(1, 0) = 7;
  expected(1, 1) = 9;
  expected(1, 2) = 11;
  expected(2, 0) = 13;
  expected(2, 1) = 15;
  expected(2, 2) = 17;

  *c = *a + *b;

  EXPECT_EQ(1, *c == expected);
}

TEST_F(test, operator_minus_equal) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1;
  expected(1, 1) = 1;
  expected(1, 2) = 1;
  expected(2, 0) = 1;
  expected(2, 1) = 1;
  expected(2, 2) = 1;

  *a -= *b;

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, operator_minus) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1;
  expected(1, 1) = 1;
  expected(1, 2) = 1;
  expected(2, 0) = 1;
  expected(2, 1) = 1;
  expected(2, 2) = 1;

  *c = *a - *b;

  EXPECT_EQ(1, *c == expected);
}

TEST_F(test, operator_multiply_equal) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 24;
  expected(0, 1) = 30;
  expected(0, 2) = 36;
  expected(1, 0) = 51;
  expected(1, 1) = 66;
  expected(1, 2) = 81;
  expected(2, 0) = 78;
  expected(2, 1) = 102;
  expected(2, 2) = 126;

  *a *= *b;

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, operator_multiply) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 24;
  expected(0, 1) = 30;
  expected(0, 2) = 36;
  expected(1, 0) = 51;
  expected(1, 1) = 66;
  expected(1, 2) = 81;
  expected(2, 0) = 78;
  expected(2, 1) = 102;
  expected(2, 2) = 126;

  *c = *a * *b;

  EXPECT_EQ(1, *c == expected);
}

TEST_F(test, operator_mult_equal_number) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(0, 2) = 9;
  expected(1, 0) = 12;
  expected(1, 1) = 15;
  expected(1, 2) = 18;
  expected(2, 0) = 21;
  expected(2, 1) = 24;
  expected(2, 2) = 27;

  *a *= 3;

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, operator_mult_number) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(0, 2) = 9;
  expected(1, 0) = 12;
  expected(1, 1) = 15;
  expected(1, 2) = 18;
  expected(2, 0) = 21;
  expected(2, 1) = 24;
  expected(2, 2) = 27;

  *c = *a * 3;

  EXPECT_EQ(1, *c == expected);
}

TEST_F(test, operator_eq_matrix) {
  S21Matrix expected(3, 3);

  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 3; j++) {
      expected(i, j) = i * 3 + j + 1;
    }
  }

  EXPECT_EQ(1, a->EqMatrix(expected));
  EXPECT_EQ(1, a->EqMatrix(*a));
  EXPECT_EQ(0, a->EqMatrix(*b));
}

TEST_F(test, sum_matrix) {
  S21Matrix x(2, 2);
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 3;
  expected(0, 2) = 5;
  expected(1, 0) = 7;
  expected(1, 1) = 9;
  expected(1, 2) = 11;
  expected(2, 0) = 13;
  expected(2, 1) = 15;
  expected(2, 2) = 17;

  a->SumMatrix(*b);
  EXPECT_EQ(1, *a == expected);
  EXPECT_THROW(a->SumMatrix(x), std::out_of_range);
}

TEST_F(test, sub_matrix) {
  S21Matrix x(2, 2);
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1;
  expected(1, 1) = 1;
  expected(1, 2) = 1;
  expected(2, 0) = 1;
  expected(2, 1) = 1;
  expected(2, 2) = 1;

  a->SubMatrix(*b);

  EXPECT_EQ(1, *a == expected);
  EXPECT_THROW(a->SubMatrix(x), std::out_of_range);
}

TEST_F(test, mul_number) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 0;
  expected(0, 1) = 0;
  expected(0, 2) = 0;
  expected(1, 0) = 0;
  expected(1, 1) = 0;
  expected(1, 2) = 0;
  expected(2, 0) = 0;
  expected(2, 1) = 0;
  expected(2, 2) = 0;

  a->MulNumber(0);

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, mul_matrix) {
  S21Matrix x(2, 3);
  S21Matrix expected(3, 3);
  expected(0, 0) = 24;
  expected(0, 1) = 30;
  expected(0, 2) = 36;
  expected(1, 0) = 51;
  expected(1, 1) = 66;
  expected(1, 2) = 81;
  expected(2, 0) = 78;
  expected(2, 1) = 102;
  expected(2, 2) = 126;

  a->MulMatrix(*b);

  EXPECT_EQ(1, *a == expected);
  EXPECT_THROW(a->MulMatrix(x), std::out_of_range);
}

TEST_F(test, transpose) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 4;
  expected(0, 2) = 7;
  expected(1, 0) = 2;
  expected(1, 1) = 5;
  expected(1, 2) = 8;
  expected(2, 0) = 3;
  expected(2, 1) = 6;
  expected(2, 2) = 9;

  *a = a->Transpose();

  EXPECT_EQ(1, *a == expected);
}

TEST_F(test, calc_complements) {
  S21Matrix x(2, 3);
  S21Matrix expected(3, 3);
  expected(0, 0) = -3;
  expected(0, 1) = 6;
  expected(0, 2) = -3;
  expected(1, 0) = 6;
  expected(1, 1) = -12;
  expected(1, 2) = 6;
  expected(2, 0) = -3;
  expected(2, 1) = 6;
  expected(2, 2) = -3;

  *a = a->CalcComplements();

  EXPECT_EQ(1, *a == expected);
  EXPECT_THROW(x.CalcComplements(), std::out_of_range);
}

TEST_F(test, determinant) {
  S21Matrix x(2, 3);
  S21Matrix y(1, 1);

  EXPECT_EQ(1, 0 - a->Determinant() < 1e-7);
  EXPECT_EQ(1, 0 - y.Determinant() < 1e-7);

  EXPECT_THROW(x.Determinant(), std::out_of_range);
}

TEST_F(test, inverse_matrix) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = 8.0 / 12;
  expected(0, 2) = -1;
  expected(1, 0) = -1;
  expected(1, 1) = -4.0 / 12;
  expected(1, 2) = 1;
  expected(2, 0) = 6.0 / 12;
  expected(2, 1) = 0;
  expected(2, 2) = -3.0 / 12;

  *c = c->InverseMatrix();

  *a = move(*b);
  EXPECT_EQ(1, *c == expected);
  EXPECT_THROW(b->InverseMatrix(), std::out_of_range);
  EXPECT_THROW(a->InverseMatrix(), std::out_of_range);
}

TEST_F(test, get_rows) { EXPECT_EQ(3, a->GetRows()); }

TEST_F(test, get_cols) { EXPECT_EQ(3, a->GetCols()); }

TEST_F(test, set_rows) {
  a->SetRows(4);
  *c = move(*b);

  EXPECT_EQ(4, a->GetRows());
  EXPECT_THROW(b->SetRows(2), std::out_of_range);
}

TEST_F(test, set_cols) {
  a->SetCols(5);
  *c = move(*b);

  EXPECT_EQ(5, a->GetCols());
  EXPECT_THROW(b->SetCols(3), std::out_of_range);
}

TEST_F(test, constructor_move) {
  S21Matrix expected;
  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 3; j++) {
      expected(i, j) = i * 3 + j + 1;
    }
  }
  S21Matrix x = move(*a);
  EXPECT_EQ(1, expected == x);
}

TEST_F(test, exception_test) {
  EXPECT_THROW(S21Matrix x(-3, 3), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}