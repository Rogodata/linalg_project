#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../source/csr_matrix.hpp"

TEST(csr_test, constructor_test_1)
{   
    //тест конструктора
    std::map<Coords, double> pairs = {{{0, 0}, 1}, {{0 , 1}, 2}, {{1, 1}, 4}, {{2, 1}, 2}, {{2, 2}, 6}};
    Csr_matrix<double> matrix = Csr_matrix(pairs);
    std::vector<double> true_val = {1, 2, 4, 2, 6}; 
    std::vector<long> true_col = {0, 1, 1, 1, 2}, true_row = {0, 2, 3, 5};
    for (long i = 0; i < 5; i ++)
    {
        ASSERT_EQ(true_val[i], matrix.get_val()[i]);
        ASSERT_EQ(true_col[i], matrix.get_col()[i]);
    }
    for (long i = 0; i < 4; i ++)
    {
        ASSERT_NEAR(true_val[i], matrix.get_val()[i], 1e-13);
    }
}

TEST(csr_test, constructor_test_2)
{
    //тест конструктора с пустыми строками (первой и ещё какой-нибудь) и столбцами (аналогично) 
    /*
    0 0 0 0 0
    0 1 2 0 0
    0 0 0 0 0
    0 0 4 0 0
    0 0 2 0 6
    */
    std::map<Coords, double> pairs = {{{1, 1}, 1}, {{1 , 2}, 2}, {{3, 2}, 4}, {{4, 2}, 2}, {{4, 4}, 6}};
    Csr_matrix<double> matrix = Csr_matrix(pairs);
    std::vector<double> true_val = {1, 2, 4, 2, 6}; 
    std::vector<long> true_col = {1, 2, 2, 2, 4}, true_row = {0, 0, 2, 2, 3, 5};
    for (long i = 0; i < 5; i ++)
    {
        ASSERT_EQ(true_val[i], matrix.get_val()[i]);
        ASSERT_EQ(true_col[i], matrix.get_col()[i]);
    }
    for (long i = 0; i < 6; i ++)
    {
        ASSERT_NEAR(true_val[i], matrix.get_val()[i], 1e-13);
    }
}

TEST(csr_test, element_getting_test_1)
{   
    // тест для сложной матрицы из прошлого теста
    std::map<Coords, double> pairs = {{{1, 1}, 1}, {{1 , 2}, 2}, {{3, 2}, 4}, {{4, 2}, 2}, {{4, 4}, 6}};
    Csr_matrix<double> matrix = Csr_matrix(pairs);
    std::vector<double> true_val = {1, 2, 2, 0, 0}, values = {matrix.element(1, 1), matrix.element(1, 2), matrix.element(4, 2), matrix.element(0, 0), matrix.element(100, 100)}; 
    for (long i = 0; i < 6; i ++)
    {
        ASSERT_NEAR(true_val[i], true_val[i], 1e-13);
    }

}

TEST(csr_test, column_multiplication_test_1)
{   
    // тест для сложной матрицы из прошлого теста
    std::map<Coords, double> pairs = {{{1, 1}, 1}, {{1 , 2}, 2}, {{3, 2}, 4}, {{4, 2}, 2}, {{4, 4}, 6}};
    Csr_matrix<double> matrix = Csr_matrix(pairs);
    std::vector<double> true_val1 = {0, 8, 0, 12, 36}, to_mul1 = {1, 2, 3, 4, 5}, to_mul2 = {0, 0, 0}, to_mul3 = {1, 2, 3, 4, 5, 6, 7, 8}, \
    mul_res1 = matrix.dot(to_mul1), mul_res2 = matrix.dot(to_mul2), mul_res3 = matrix.dot(to_mul3), true_val2 = {0, 0, 0, 0, 0}, true_val3 = {0, 8, 0, 12, 36}; 
    for (long i = 0; i < 5; i ++)
    {
        ASSERT_NEAR(true_val1[i], mul_res1[i], 1e-13);
    }
    for (long i = 0; i < 5; i ++)
    {
        ASSERT_NEAR(true_val2[i], mul_res2[i], 1e-13);
    }
    for (long i = 0; i < 5; i ++)
    {
        ASSERT_NEAR(true_val3[i], mul_res3[i], 1e-13);
    }
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
