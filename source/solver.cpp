#include "tridiagonal_solver.hpp"
#include "tridiagonal_matrix.hpp"
#include <vector>

int main()
{   
    std::vector<Row<double>> rows_array = {Row<double>(0, double(7.0/9.0), double(7.0/10.0)), Row<double>(6.0/9.0, 13/6, 5/4), Row<double>(1/9, 3/8, 0)};
    TridiagonalMatrix test_matrix1 = TridiagonalMatrix<double>(3, rows_array);
    std::vector<double> true_ansver_array = {2301/1292, -6795/4522, 4775/2261}, test_ansver_array, d_array = {1/3, 4/7, 5/8};
    // выведем матрицу
    std::cout << test_matrix1 << std::endl;
    // решаем
    test_ansver_array = tridiagonal_solution(d_array, test_matrix1);
    // выводим решение
    for (auto it = test_ansver_array.begin(); it != test_ansver_array.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}