#pragma once

#include <vector>
#include <cmath>

#include "csr_matrix.hpp"

template <typename T>
T get_r_inf_norm(const Csr_matrix<T> &A, const std::vector<T> &x, const std::vector<T> &b)
{
    T r = 0;
    for (size_t j = 0; j < b.size(); j++)
    {
        if (abs(b[j] - A.dot(x)[j]) > r)
            r = abs(b[j] - A.dot(x)[j]);
    }
    return r;
}

template <typename T>
std::vector<T> Jacoby_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{   
    std::vector<T> xk = x0, xt;
    xt.reserve(x0.size());
    while(tolerance > get_r_inf_norm(A, xk, b)){
        for(size_t k = 0; k < x0.size(); k ++){
            xt[k] = (1 / A.element(k, k)) * (b[k] - A.dot(xk)[k] + A.element(k,k) * xk[k]);
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
    while(tolerance > get_r_inf_norm(A, xk, b)){
        for(size_t k = 0; k < x0.size(); k ++){
            for(size_t i = 0; i < k - 1; i ++)
                sum_1 += A.element(k, i) * xk[i];
            for(size_t i = k + 1; i < x0.size(); i ++)
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
    std::vector<T> xk = x0, xt;
    while(tolerance > get_r_inf_norm(A, xk, b)){
        xt = A.dot(xk);
        for(size_t k = 0; k < x0.size(); k ++){
            xk[k] = xk[k] - tau * (xt[k] - b[k]);
        }
    }
    return xk;
}

