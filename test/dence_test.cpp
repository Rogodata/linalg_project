#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../source/dence.hpp"

TEST(dence_test, arithmethic_test_1)
{   
    //тест арифметических операций
    std::vector<double> matrix_array = {1.0, 2.0, 3.0, 4.0};
    Dence<double> matrix1 = {matrix_array, 2, 2}, matrix2 = {matrix_array, 1 , 4};
    ASSERT_NEAR((matrix2 * matrix2.transponse()).element(0,0), 30.0, 1e-13);
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
