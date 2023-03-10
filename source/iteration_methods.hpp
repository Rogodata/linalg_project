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
    std::vector<T> xk = x0, xt(x0.size(), 0);
    while (tolerance < get_r_inf_norm(A, xk, b))
    {   
        for (size_t k = 0; k < x0.size(); k++)
        {
            xt[k] = (1 / A.element(k, k)) * (b[k] - A.dot(xk)[k] + A.element(k, k) * xk[k]);
        }
        xk = xt;
    }
    return xk;
}

template <typename T>
std::vector<T> G_Z_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{   
    std::vector<T> xk = x0;
    T sum_1 = 0, sum_2 = 0;
    while (tolerance < get_r_inf_norm(A, xk, b))
    {
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
    }
    return xk;
}

template <typename T>
std::vector<T> MPI_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0, const T tau)
{
    std::vector<T> xk = x0, xt = A.dot(xk);
    while (tolerance < get_r_inf_norm<T>(A, xk, b))
    {
        for (size_t i = 0; i < x0.size(); i++)
        {
            xk[i] = xk[i] - tau * (xt[i] - b[i]);
            xt = A.dot(xk);
        }
    }
    return xk;
}
