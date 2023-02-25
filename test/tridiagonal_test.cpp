#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../source/tridiagonal_solver.hpp"

TEST(tridiagonal_solver_test, Test_1)
{
  std::vector<Row<double>> rows_array = {Row<double>(0, 2, -1), Row<double>(5, 8, 2), Row<double>(1, 6, 2), Row<double>(4, -3, 0)};
  TridiagonalMatrix test_matrix1 = TridiagonalMatrix<double>(4, rows_array);
  std::vector<double> true_ansver_array = {1, 1, 1, 1}, test_ansver_array, d_array = {1, 15, 9, 1};
  test_ansver_array = tridiagonal_solution(d_array, test_matrix1);
  for (size_t i = 0; i < 4; ++i)
  {
    std::cout << true_ansver_array[i] << " " << test_ansver_array[i] << std::endl;
    ASSERT_NEAR(true_ansver_array[i], test_ansver_array[i], 1e-13);
  }
}

TEST(tridiagonal_solver_test, Test_2)
{
  std::vector<Row<double>> rows_array = {Row<double>(0.0, 7.0/9.0, 7.0/10.0), Row<double>(6.0/9.0, 13.0/6.0, 5.0/4.0), Row<double>(1.0/9.0, 3.0/8.0, 0)};
  TridiagonalMatrix test_matrix2 = TridiagonalMatrix<double>(3, rows_array);
  std::vector<double> true_ansver_array = {2301.0/1292.0, -6795.0/4522.0, 4775.0/2261.0}, test_ansver_array, d_array = {1.0/3.0, 4.0/7.0, 5.0/8.0};
  test_ansver_array = tridiagonal_solution(d_array, test_matrix2);
  for (size_t i = 0; i < 4; ++i)
  {
    std::cout << true_ansver_array[i] << " " << test_ansver_array[i] << std::endl;
    ASSERT_NEAR(true_ansver_array[i], test_ansver_array[i], 1e-15);
  }
}

TEST(tridiagonal_solver_test, Test_3)
{
  TridiagonalMatrix test_matrix2 = TridiagonalMatrix<double>(4, "test_1.txt");
  std::vector<double> true_ansver_array = {1, 1, 1, 1}, test_ansver_array, d_array = {1 , 15, 9, 1};
  test_ansver_array = tridiagonal_solution(d_array, test_matrix2);
  for (size_t i = 0; i < 4; ++i)
  {
    std::cout << true_ansver_array[i] << " " << test_ansver_array[i] << std::endl;
    ASSERT_NEAR(true_ansver_array[i], test_ansver_array[i], 1e-15);
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
