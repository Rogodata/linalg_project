#pragma once
#include <map>

struct Coords
{
    Coords(long x, long y)
    {
        col = x;
        row = y;
    }

    friend bool operator==(const Coords pair1, const Coords pair2) { return (pair1.col == pair2.col and pair1.row == pair2.row); }
    friend bool operator<(const Coords pair1, const Coords pair2)
    {
        if (pair1.col == pair2.col)
            return pair1.row < pair2.row;
        return pair1.col < pair2.col;
    }

    long col = 0, row = 0;
};

template <typename T>
class D_O_K
{
public:
    D_O_K(std::map<Coords, T> values) { insides = values; }

    void add_element(Coords coord, T val) { insides.insert_or_assign(coord, val); }

    std::map<Coords, T> get_insides() { return insides; }

private:
    std::map<Coords, T> insides;
};