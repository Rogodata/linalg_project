#pragma once

#include <vector>
#include <algorithm>

template <typename T>
class Dence
{
public:
    Dence(const std::vector<T> matrix_array, const size_t height_, const size_t width_)
    {
        matrix = matrix_array;
        height = height_;
        width = width_;
    }

    T element(size_t row_coord, size_t col_coord) const
    {
        return matrix[row_coord * width + col_coord];
    }

    Dence<T> transponse()
    {
        std::vector<T> new_matrix;
        for (size_t i = 0; i < width; i++)
        {
            for (size_t j = 0; j < height; j++)
            {
                new_matrix.push_back(matrix[i + j * width]);
            }
        }
        return {new_matrix, width, height};
    }

    Dence<T> operator*(const Dence<T> matrix_)
    {
        if (width != matrix_.g_height())
        {
            throw std::runtime_error("wrong matrix sizes");
            return {{}, 0, 0};
        }
        else
        {
            T sum = 0;
            std::vector<T> new_matrix;
            // идём по столбцам
            for (size_t i = 0; i < height; i++)
            {
                // по строке
                for (size_t j = 0; j < matrix_.g_width(); j++)
                {
                    for (size_t k = 0; k < width; k++)
                    {
                        sum += matrix[width * i + k] * matrix_.element(k, j);
                    }
                    new_matrix.push_back(sum);
                    sum = 0;
                }
            }
            return {new_matrix, height, matrix_.g_width()};
        }
    }

    friend Dence<T> operator*(const T number, const Dence<T> matrix_)
    {

        std::vector<T> new_matrix;
        for (size_t i = 0; i < matrix_.height; i++)
        {
            for (size_t j = 0; j < matrix_.width; j++)
            {
                new_matrix.push_back(matrix_.element(i, j) * number);
            }
        }
        return {new_matrix, matrix_.height, matrix_.width};
    }

    Dence<T> operator*(const T number)
    {

        std::vector<T> new_matrix;
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                new_matrix.push_back(matrix[width * i + j] * number);
            }
        }
        return {new_matrix, height, width};
    }

    Dence<T> operator+(const Dence<T> matrix_)
    {
        if (height != matrix_.g_height() or width != matrix_.g_width())
        {
            throw std::runtime_error("wrong matrix sizes");
            return {{}, 0, 0};
        }
        else
        {
            T sum = 0;
            std::vector<T> new_matrix;
            for (size_t i = 0; i < height; i++)
            {
                for (size_t j = 0; j < width; j++)
                {
                    new_matrix.push_back(matrix[width * i + j] + matrix_.element(i, j));
                }
            }
            return {new_matrix, height, width};
        }
    }

    Dence<T> operator-(const Dence<T> matrix_)
    {
        if (height != matrix_.g_height() or width != matrix_.g_width())
        {
            throw std::runtime_error("wrong matrix sizes");
            return {{}, 0, 0};
        }
        else
        {
            T sum = 0;
            std::vector<T> new_matrix;
            for (size_t i = 0; i < height; i++)
            {
                for (size_t j = 0; j < width; j++)
                {
                    new_matrix.push_back(matrix[width * i + j] - matrix_.element(i, j));
                }
            }
            return {new_matrix, height, width};
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Dence<T> &matrix)
    {
        for (size_t i = 0; i < matrix.g_height() - 1; i++)
        {
            for (size_t j = 0; j < matrix.g_width(); j++)
            {
                os << matrix.element(i, j) << " ";
            }
            os << std::endl;
        }
        for (size_t j = 0; j < matrix.g_width(); j++)
        {
            os << matrix.element(matrix.g_height() - 1, j) << " ";
        }
        return os;
    };

    size_t g_height() const { return height; }
    size_t g_width() const { return width; }

private:
    std::vector<T> matrix;
    size_t height, width;
};