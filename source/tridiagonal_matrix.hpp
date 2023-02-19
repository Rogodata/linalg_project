#pragma once

#include "tridiagonal_solver.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

template <typename T>
struct Row
{
    Row()
    {
        // default constructor
        a = 0;
        b = 0;
        c = 0;
    };

    Row(T a, T b, T c)
    {
        // constructor with parameters
        this->a = a;
        this->b = b;
        this->c = c;
    };

    T a, b, c;
};

template <typename T>
class TridiagonalMatrix
{
public:
    TridiagonalMatrix(const unsigned int size, const std::string file_name)
    {
        this->n_parameter = size - 1;
        rows.resize(0);
        std::ifstream file_stream;
        file_stream.open(file_name);
        T a_number, b_number, c_number, zero = 0;
        file_stream >> b_number >> c_number;
        rows.push_back(Row(zero, b_number, c_number));
        for (int i = 1; i < n_parameter; i++)
        {
            file_stream >> a_number >> b_number >> c_number;
            rows.push_back(Row(a_number, b_number, c_number));
        }
        file_stream >> a_number >> b_number;
        rows.push_back(Row(a_number, b_number, zero));
        file_stream.close();
    };

    TridiagonalMatrix(const unsigned int size, const std::vector<Row<T>> rows_array)
    {
        this->n_parameter = size - 1;
        rows = rows_array;
    };


    void read_data(const std::string file_name)
    {
        std::ifstream file_stream;
        file_stream.open(file_name);
        T a_number, b_number, c_number;
        file_stream >> b_number >> c_number;
        rows.push_back(Row(float(0), b_number, c_number));
        for (int i = 1; i < n_parameter; i++)
        {
            file_stream >> a_number >> b_number >> c_number;
            rows.push_back(Row(a_number, b_number, c_number));
        }
        file_stream >> a_number >> b_number;
        rows.push_back(Row(a_number, b_number, float(0)));
        file_stream.close();
    }

    Row<T> operator[](const std::size_t i_coord) const { return rows[i_coord]; }

    unsigned int get_n() const { return n_parameter; }

    friend std::ostream &operator<<(std::ostream &os, const TridiagonalMatrix<T> &matrix)
    {
        os << "The values of diagonals are:" << std::endl;
        for (unsigned int i = 0; i < matrix.n_parameter + 1; i++)
        {
            os << matrix.rows[i].a << " " << matrix.rows[i].b << " " << matrix.rows[i].c << std::endl;
        }
        os << "the end of matrix";
        return os;
    };

private:
    // поле n_parameter здесь на 1 меньше реального размера матрицы. Сделано для удобства отсчёта элементов с нуля.
    unsigned int n_parameter;
    std::vector<Row<T>> rows;
};