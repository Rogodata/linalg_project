#include <iostream>
#include <fstream>
#include <vector>
#include <string>

template <typename T>
struct Row
{
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
        }
    };

    std::ifstream &read_data(std::ifstream &file_stream, std::string file_name)
    {
        file_stream.open(file_name);
        file_stream >> rows[0].b >> rows[0].c;
        for (int i = 1; i < n_parameter; i++)
        {
            file_stream >>
                rows[i].b >> rows[i].c >> rows[i].c;
        }
        file_stream >> std::stof(rows[n_parameter].b) >> std::stof(rows[n_parameter].c);
        file_stream.close();
        return file_stream;
    }

    std::vector<T> get_solution(T *answers_array)
    {
        // Не очень здорово, что я просто подаю указатель на массив данных, но думаю, так быстрее чем с вектором
        std::vector<T> result_array;
        T *p = new T[n_parameter + 1];
        T *q = new T[n_parameter + 1];
        // прямой ход
        p[1] = -rows[0].c / rows[0].b;
        q[1] = answers_array[0] / rows[0].b;
        for (long i = 1; i < n_parameter; i++)
        {
            p[i + 1] = -(rows[i].c / (rows[i].a * p[i] + rows[i].b));
            q[i + 1] = -((answers_array[i] - rows[i].a * q[i]) / (rows[i].a * p[i] + rows[i].b));
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

private:
    // поле n_parameter здесь на 1 меньше реального размера матрицы. Сделано для удобства отсчёта элементов с нуля.
    unsigned int n_parameter;
    std::vector<Row<T>> rows;
};

int main()
{
    TridiagonalMatrix test_matrix = TridiagonalMatrix<int>(4);
    std::ifstream fout("/home/rogoda/atom_projects_ubuntu/assembly_labs/lab_5/6_2.txt", std::ios::app);
    fout << pi << " " << i << std::endl; // запись строки в файл
    test_matrix.read_data();
    return 0;
}