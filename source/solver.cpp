#include "tridiagonal_solver.hpp"
#include "tridiagonal_matrix.hpp"
#include <vector>

int main()
{
    TridiagonalMatrix test_matrix = TridiagonalMatrix<float>(4, "test_1.txt");
    // выведем матрицу
    std::cout << test_matrix << std::endl;
    std::vector<float> d_array = {1, 15, 9, 1};
    // решаем
    std::vector<float> result = get_solution(d_array, test_matrix);
    // выводим решение
    for (auto it = result.begin(); it != result.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}