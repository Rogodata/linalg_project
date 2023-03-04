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
        if (fabs(b[j] - A.dot(x)[j]) > r)
            r = fabs(b[j] - A.dot(x)[j]);
    }
    return r;
}

template <typename T>
T get_r_3_norm(const Csr_matrix<T> &A, const std::vector<T> &x, const std::vector<T> &b)
{   
    T r = 0;
    for (size_t j = 0; j < b.size(); j++)
    {   
        r += (b[j] - A.dot(x)[j]) * (b[j] - A.dot(x)[j]);
    }
    return r;
}

template <typename T>
std::vector<T> Jacoby_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{   
    std::vector<T> xk = x0, xt(x0.size(), 0);
    while(tolerance < get_r_inf_norm(A, xk, b)){
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
    while(tolerance < get_r_inf_norm(A, xk, b)){
        for(long long k = 0; k < x0.size(); k ++){
            for(long long i = 0; i < k; i ++)
                sum_1 += A.element(k, i) * xk[i];
            for(long long i = k + 1; i < x0.size(); i ++)
                sum_2 += A.element(k, i) * xk[i];
            xk[k] = (1 / A.element(k, k)) * (b[k] - sum_1 - sum_2);
            sum_1 = 0;
            sum_2 = 0;
        }
    }
    return xk;
}

template<typename Type>
std::vector<Type> operator-(const std::vector<Type>& a, const std::vector<Type>& b) {
    std::vector<Type> result(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

template<typename Type>
std::vector<Type> operator*(const std::vector<Type>& a, const Type &c) {
    std::vector<Type> result(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] * c;
    }
    return result;
}


template <typename T>
std::vector<T> MPI_meth(const Csr_matrix<T> &A, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0, const T tau)
{   
    long long counter = 0;
    std::vector<T> result = x0, r = A.dot(result) - b;
    while(tolerance < get_r_3_norm<T>(A, result, b)){
        counter ++;
        result = result - r*tau;
        r = A.dot(result) - b;
        std::cout << counter << std::endl;
    }
    return result;
}
