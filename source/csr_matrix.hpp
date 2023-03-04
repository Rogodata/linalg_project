#pragma once

#include "dok.hpp"

#include <vector>
#include <algorithm>

template<typename T>
class Csr_matrix{
public:
    Csr_matrix(const std::map<Coords, T> &pairs){
        long max_str = pairs.end()->first.col;
        long prev = -1, now, number = 0; 
        for(auto j:pairs){
            val.push_back(j.second);
            col.push_back(j.first.row);
            now = j.first.col;
            while (prev < now){
                prev ++;
                row.push_back(number);
            }
            number ++;
        }
        row.push_back(number);
    }

    Csr_matrix(const std::vector<T> &values, const std::vector<unsigned long> &cols, const std::vector<unsigned long> &rows){
        col = cols;
        row = rows;
        val = values;
    }

    T element(const unsigned long row_coor, const unsigned long col_coor) const{
        if(col_coor > *std::max_element(col.begin(), col.end()) or row_coor > row.size() - 1){
            return 0;
        }
        else{
            unsigned long needed = row[row_coor], in_row = row[row_coor + 1] - row[row_coor];
            for(unsigned long i = needed; i < needed + in_row; i++){
                if(col[i] == col_coor){
                    return val[i];
                }
            }
            return 0;
        }
    }

    std::vector<T> dot(const std::vector<T> &column_vector){
        std::vector<T> result;
        T sum = 0;
        for (unsigned long i = 0; i < row.size() - 1; i++){
            for(unsigned long j = row[i]; j < std::min(row[i + 1], column_vector.size()); j++){
                sum += val[j] * column_vector[col[j]];
            }
            result.push_back(sum);
            sum = 0;
        }
        return result;
    }

    Csr_matrix<T> operator*(const T number)
    {

        std::vector<T> new_val;
        for (size_t j = 0; j < val.size(); j++)
        {
            new_val.push_back(val[j] * number);
        }
        return {new_val, col, row};
    }

    friend std::ostream &operator<<(std::ostream &os, const Csr_matrix<T> &matrix)
    {
        for (auto i:matrix.val)
        {
            os << i << " ";
        }
        os << std::endl;
        for (auto i:matrix.col)
        {
            os << i << " ";
        }
        os << std::endl;
        for (auto i:matrix.row)
        {
            os << i << " ";
        }
        return os;
    };

    std::vector<T> get_val() const {return val;} 
    std::vector<unsigned long> get_col() const {return col;}
    std::vector<unsigned long> get_row() const {return row;}

private:
    std::vector<T> val;
    std::vector<unsigned long> col, row;
};