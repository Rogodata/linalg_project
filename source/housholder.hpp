#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include "dence.hpp"

// В тестах мы сначала проходимся алгоритмом который точно может сделать всё правильно но долго, проверяем свойства пполученных матриц
//затем, зная что алгоритм разложил матрицу верно, протестируем быстрый аллгоритм на соответствие результата




template <typename T>
Dence<T> get_u(Dence<T> x_vec)
{
    std::vector<T> e_ = {std::sqrt((x_vec.transponse() * x_vec).element(0, 0))};
    for (size_t i = 0; i < x_vec.g_height() - 1; i++)
    {
        e_.push_back(0);
    }
    Dence<T> e = {e_, x_vec.g_height(), 1};
    std::cout << e << std::endl;
    return x_vec.element(0, 0) < 0 ? x_vec - e : x_vec + e;
}

template <typename T>
Dence<T> build_p_test(Dence<T> u_vec, size_t number)
 {  
    //тестовый алгоритм для проверки верхнетруегольности в будущем
    Dence<T> P_sm = Dence<T>(u_vec.g_height()) - ((2 / (u_vec.transponse() * u_vec).element(0, 0)) * (u_vec * u_vec.transponse()));
    std::vector<T> p_matrix = {}, zeros_l(number + u_vec.g_height(), T(0)), zeros_s(number, T(0));
    for (size_t i = 0; i < number; i++)
    {
        p_matrix.push_back(1);
        p_matrix.insert(p_matrix.end(), zeros_l.begin(), zeros_l.end());
    }
    for (size_t j = 0; j < u_vec.g_height(); j++)
    {
        std::vector<T> p_row = P_sm.get_row(j);
        p_matrix.insert(p_matrix.end(), p_row.begin(), p_row.end());
        p_matrix.insert(p_matrix.end(), zeros_s.begin(), zeros_s.end());
    }
    p_matrix.resize((number + u_vec.g_height()) * (number + u_vec.g_height()));
    return {p_matrix, number + u_vec.g_height(), number + u_vec.g_height()};
}


template<typename T>
Dence<T> calculate_R_test(const Dence<T> matrix_)
    {   
        // тестовый алгоритм для проверки верхнетреугольности в будущем
        std::vector<std::vector<T>> u_vectors;
        Dence<T> matrix = matrix_;
        for (size_t i = 0; i < matrix.g_height() - 1; i++)
        {
            Dence<T> u_vec = get_u(Dence<T>(matrix.get_col(i, i), matrix.g_height() - i, 1));
            u_vectors.push_back(u_vec.get_col(0));
            matrix = build_p_test(u_vec, i) * matrix;
        }
        return matrix;
    };



template <typename T>
class Housholder
{
public:
    Housholder(const Dence<T> matrix_) { matrix = Dence<T>(matrix_.g_matrix(), matrix_.g_height(), matrix_.g_width()); }


private:
    Dence<T> matrix;
    std::vector<std::vector<T>> u_vectors;
};
