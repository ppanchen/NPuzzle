//
// Created by Petro Panchenko on 11/7/18.
//

#ifndef NPUZZLE_COMMONTOOLS_H
#define NPUZZLE_COMMONTOOLS_H
#include <memory>
#include <vector>

template <typename T>
class Grid {
    size_t _rows;
    size_t _columns;
    std::vector<T> _data;

public:
    Grid(size_t rows, size_t columns) : _rows(rows), _columns(columns)
    {
        _data.reserve(_rows * _columns);
    }

    Grid (const Grid &toCopy) : _rows(toCopy._rows), _columns(toCopy._columns), _data(toCopy._data)
    {
    }

    void findElement(const T &element)
    {

    }

    size_t rows() const { return _rows; }

    size_t columns() const { return _columns; }

    T *operator()(size_t row, size_t column) {
        return &_data[row * _columns + column];
    }
};


#endif //NPUZZLE_COMMONTOOLS_H
