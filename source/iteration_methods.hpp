#pragma once

#include <vector>
#include <cmath>
#include <fstream>

#include "csr_matrix.hpp"

template <typename T>
T get_r_inf_norm(const Csr_matrix<T> &A, const std::vector<T> &x, const std::vector<T> &b)
{
    T r = 0;
    for (size_t j = 0; j < b.size(); j++)
    {
        if (fabs(b[j] - A.dot(x)[j]) > r)
            r = fabs(b[j] - A.dot(x)[j]);
    }
    return r;
}

template <typename T>
std::vector<T> Jacoby_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{   
    unsigned long long counter = 0;
    std::vector<T> xk = x0, xt(x0.size(), 0);
    while (tolerance < get_r_inf_norm(A, xk, b))
    {   
        counter ++;
        for (size_t k = 0; k < x0.size(); k++)
        {
            xt[k] = (1 / A.element(k, k)) * (b[k] - A.dot(xk)[k] + A.element(k, k) * xk[k]);
        }
        xk = xt;
        std::ofstream fout("/home/rogoda/cpp_projects/linalg_project-1/source/jacoby.txt", std::ios::app); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
        fout << get_r_inf_norm<T>(A, xk, b) << " " << counter << std::endl; // запись строки в файл
        fout.close();
    }
    return xk;
}

template <typename T>
std::vector<T> G_Z_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{   
    unsigned long long counter = 0;
    std::vector<T> xk = x0;
    T sum_1 = 0, sum_2 = 0;
    while (tolerance < get_r_inf_norm(A, xk, b))
    {
        counter ++;
        for (long long k = 0; k < x0.size(); k++)
        {
            for (long long i = 0; i < k; i++)
                sum_1 += A.element(k, i) * xk[i];
            for (long long i = k + 1; i < x0.size(); i++)
                sum_2 += A.element(k, i) * xk[i];
            xk[k] = (1 / A.element(k, k)) * (b[k] - sum_1 - sum_2);
            sum_1 = 0;
            sum_2 = 0;
        }
        std::ofstream fout("/home/rogoda/cpp_projects/linalg_project-1/source/gz.txt", std::ios::app); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
        fout << get_r_inf_norm<T>(A, xk, b) << " " << counter << std::endl; // запись строки в файл
        fout.close();
    }
    return xk;
}

template <typename T>
std::vector<T> MPI_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0, const T tau)
{
    unsigned long long counter = 0;
    std::vector<T> xk = x0, xt = A.dot(xk);
    while (tolerance < get_r_inf_norm<T>(A, xk, b))
    {
        counter ++;
        for (size_t i = 0; i < x0.size(); i++)
        {
            xk[i] = xk[i] - tau * (xt[i] - b[i]);
            xt = A.dot(xk);
        }
        std::ofstream fout("/home/rogoda/cpp_projects/linalg_project-1/source/mpi.txt", std::ios::app); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
        fout << get_r_inf_norm<T>(A, xk, b) << " " << counter << std::endl; // запись строки в файл
        fout.close();
        // std::cout << counter << std::endl;
    }
    return xk;
}
