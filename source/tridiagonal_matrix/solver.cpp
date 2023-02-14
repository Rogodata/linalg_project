#include "tridiagonal_solver.hpp"

int main()
{
    TridiagonalMatrix test_matrix = TridiagonalMatrix<float>(4, "test_1.txt");
    // выведем матрицу
    std::cout << test_matrix << std::endl;
    float d_array[4] = {1, 15, 9, 1};
    // решаем
    std::vector<float> result = test_matrix.get_solution(d_array);
    // выводим решение
    for (auto it = result.begin(); it != result.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}