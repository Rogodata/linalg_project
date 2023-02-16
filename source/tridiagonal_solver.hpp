#pragma once

#include "tridiagonal_matrix.hpp"
#include <vector>


template<typename T>
std::vector<T> get_solution(const std::vector<T> answers_array,const TridiagonalMatrix<T>& matrix)
{
    std::vector<T> q, p, result_array;
    result_array.resize(matrix.get_n() + 1);
    q.resize(matrix.get_n());
    p.resize(matrix.get_n());
    // прямой ход
    p[0] = -matrix[0].c / matrix[0].b;
    q[0] = answers_array[0] / matrix[0].b;
    for (long i = 1; i < matrix.get_n(); i++)
    {
        p[i] = -((matrix[i].c) / (matrix[i].a * p[i - 1] + matrix[i].b));
        q[i] = ((answers_array[i] - matrix[i].a * q[i - 1]) / (matrix[i].a * p[i - 1] + matrix[i].b));
    }
    // обратный ход
    result_array[matrix.get_n()] = (answers_array[matrix.get_n()] - matrix[matrix.get_n()].a * q[matrix.get_n() - 1]) / (matrix[matrix.get_n()].a * p[matrix.get_n() - 1] + matrix[matrix.get_n()].b);
    for (long i = matrix.get_n() - 1; i > -1; i--)
    {
        result_array[i] = p[i] * result_array[i + 1] + q[i];
    }
    return result_array;
}







