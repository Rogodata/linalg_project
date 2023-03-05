#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../source/csr_matrix.hpp"
#include "../source/iteration_methods.hpp"

TEST(task_4, task_test)
{
  // В третьем номере просто пстроил график.
  // Тут продифференцируем, чтобы найти точки, где градиент функции равен нулю.
  // Заметим, что А является матрицей строго положительно определённой квдартатичной формы (онп же будет матрицей Гесса)
  // поэтому в точке, где градиент будет равен нулю и плучим минимум
  // Чтобы найти эту точку достаточно решить СЛАУ Ax = b
  std::map<Coords, double> pairs = {{{0, 0}, 12}, {{0, 1}, 17}, {{1, 2}, 3}, {{1, 0}, 17}, {{1, 1}, 15825}, {{1, 2}, 28}, {{2, 0}, 3}, {{2, 1}, 28}, {{2, 2}, 238}};
  Csr_matrix<double> matrix_A = Csr_matrix(pairs);
  std::vector<double> b = {1, 2, 3};
  std::vector<double> x0 = {1, 1, 1};
  //tau надо взять достаточно маленьким, формула есть в лекции.
  double tau = 0.0001;
  std::vector<double> mpi = MPI_meth(matrix_A, 1e-13, b, x0, tau);
  // здесь собственно выводим решение
  for (auto i : mpi)
  {
      std::cout << i << std::endl;
  } 
  std::vector<double> gz = G_Z_meth(matrix_A, 1e-20, b, x0);
  std::vector<double> jac = Jacoby_meth(matrix_A, 1e-20, b, x0);
  // график лежит в папке с тестами. МПИ сходится за гораздо большее число итераций нежели алгоритмы Якоби и Гаусса-Зейделя
  // По этой причине графиков два
  for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], gz[i], 1e-13);
    }
    for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], jac[i], 1e-13);
    }
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}