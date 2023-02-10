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
        a = float(0);
        b = float(0);
        c = float(0);
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
    TridiagonalMatrix(unsigned int size)
    {
        if (size < 3)
        {
            std::cout << "решение такой матрицы очевидно, ожидается, что размер матрицы больше 2" << std::endl;
        }
        else
        {
            this->n_parameter = size - 1;
            rows.resize(0);
        }
    };

    void read_data(std::string file_name)
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

    std::vector<T> get_solution(T *answers_array)
    {
        // Не очень здорово, что я просто подаю указатель на массив данных, но думаю, так быстрее чем с вектором
        // К тому, предполагается, что я доверяю поданному столбцу свободных членов
        std::vector<T> result_array;
        result_array.resize(n_parameter + 1);
        T *p = new T[n_parameter + 1];
        T *q = new T[n_parameter + 1];
        // прямой ход
        p[1] = -rows[0].c / rows[0].b;
        q[1] = answers_array[0] / rows[0].b;
        for (long i = 1; i < n_parameter; i++)
        {
            p[i + 1] = -((rows[i].c) / (rows[i].a * p[i] + rows[i].b));
            q[i + 1] = ((answers_array[i] - rows[i].a * q[i]) / (rows[i].a * p[i] + rows[i].b));
        }
        // обратный ход
        result_array[n_parameter] = (answers_array[n_parameter] - rows[n_parameter].a * q[n_parameter]) / (rows[n_parameter].a * p[n_parameter] + rows[n_parameter].b);
        for (long i = n_parameter - 1; i > -1; i--)
        {
            result_array[i] = p[i + 1] * result_array[i + 1] + q[i + 1];
        }
        delete[] p;
        delete[] q;
        return result_array;
    }

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

int main()
{
    TridiagonalMatrix test_matrix = TridiagonalMatrix<float>(4);
    test_matrix.read_data("test_1.txt");
    // выведем матрицу
    std::cout << test_matrix << std::endl;
    float d_array[4] = {1, 15, 7, 1};
    // решаем
    std::vector<float> result = test_matrix.get_solution(d_array);
    // выводим решение
    for (auto it = result.begin(); it != result.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}