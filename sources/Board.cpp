//
// Created by Petro Panchenko on 11/7/18.
//

#include <sstream>
#include <vector>
#include <cmath>
#include "../headers/Board.h"
#include "../headers/Logger.h"

int Board::_size = 0;
Matrix Board::_aimBlocks;
Algorithm Board::_algorithmFlag;

/// Copy constructor
/// \param b2 - instance to be copied
//Board::Board(const Board *b2)
//{
//    init(b2->_blocks);
//}

Board::Board(Matrix blocks)
{
    init(blocks);
}

bool Board::operator==(const Board& other) const
{
    bool result = true;

    result &= _blocks == other._blocks;

    return result;
}

std::set<std::shared_ptr<Board>> Board::neighbors()
{
    std::set<std::shared_ptr<Board>> boardList;
    boardList.insert(swap(_blocks, _zeroX, _zeroY, _zeroX, _zeroY + 1));
    boardList.insert(swap(_blocks, _zeroX, _zeroY, _zeroX, _zeroY - 1));
    boardList.insert(swap(_blocks, _zeroX, _zeroY, _zeroX - 1, _zeroY));
    boardList.insert(swap(_blocks, _zeroX, _zeroY, _zeroX + 1, _zeroY));

    return boardList;
}

void Board::staticInit(unsigned size, Algorithm algoFlag)
{
    _algorithmFlag = algoFlag;
    _size = size;

    if (_aimBlocks.empty())
    {
        _aimBlocks.resize(size);
        for (std::vector<int> &ver : _aimBlocks)
        {
            ver = std::vector<int>(size, 0);
        }
        //С помощью переменной s задаются числа внутри массива начиная с 1.
        int s = 1;

        //Заполняем периметр массива по часовой стрелке.
        for (int y = 0; y < size; y++) {
            _aimBlocks[0][y] = s;
            s++;
        }
        for (int x = 1; x < size; x++) {
            _aimBlocks[x][size - 1] = s;
            s++;
        }
        for (int y = size - 2; y >= 0; y--) {
            _aimBlocks[size - 1][y] = s;
            s++;
        }
        for (int x = size - 2; x > 0; x--) {
            _aimBlocks[x][0] = s;
            s++;
        }

        //Периметр заполнен. Продолжаем заполнять массив и задаём
        //координаты ячейки, которую необходимо заполнить следующей.
        int c = 1;
        int d = 1;

        while (s < size * size) {
            while (_aimBlocks[c][d + 1] == 0) {
                _aimBlocks[c][d] = s;
                s++;
                d++;
            }

            //Движемся вниз.
            while (_aimBlocks[c + 1][d] == 0) {
                _aimBlocks[c][d] = s;
                s++;
                c++;
            }

            //Движемся влево.
            while (_aimBlocks[c][d - 1] == 0) {
                _aimBlocks[c][d] = s;
                s++;
                d--;
            }

            //Движемся вверх.
            while (_aimBlocks[c - 1][d] == 0) {
                _aimBlocks[c][d] = s;
                s++;
                c--;
            }
        }
    }
}

void Board::init(const Matrix &block)
{
    _blocks = block;

    for (int i = 0; i < _blocks.size(); i++)
    {
        for (int j = 0; j < _blocks[i].size(); j++)
        {
            switch (Board::_algorithmFlag)
            {
                case Algorithm::Manhattan:
                    _h += Manhattan(i, j);
                case Algorithm::Hamming:
                    if (_blocks[i][j] != _aimBlocks[i][j] && _blocks[i][j] != 0)
                        _h += 1;
                case Algorithm::Euclidean:
                    _h += Euclidean(i, j);
            }
            if (_blocks[i][j] == 0)
            {
                _zeroX = i;
                _zeroY = j;
            }
        }
    }
}

std::shared_ptr<Board> Board::swap(Matrix blocks2, int x1, int y1, int x2, int y2)
{
    if (x2 > -1 && x2 < dimension() && y2 > -1 && y2 < dimension())
    {
        int t = blocks2[x2][y2];
        blocks2[x2][y2] = blocks2[x1][y1];
        blocks2[x1][y1] = t;
        Logger::memoryCount++;
        return std::make_shared<Board>(blocks2);
    }
    else
        return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    if (!board._blocks.empty())
    {
        for (auto block : board._blocks)
        {
            std::copy(block.begin(), block.end() - 1,
                      std::ostream_iterator<int>(os, ", "));
            os << block.back() << std::endl;
        }
        os << std::endl;
    }
    return os;
}

int Board::Manhattan(int x, int y)
{
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_aimBlocks[i][j] == _blocks[x][y]) {
                return abs(i - x) + abs(j - y);
            }
        }
    }
    return 0;
}

int Board::Euclidean(int x, int y)
{
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_aimBlocks[i][j] == _blocks[x][y]) {
                return (int)sqrt((i - x) * (i - x) + (j - y) * (j - y));
            }
        }
    }
    return 0;
}

int Board::inversions()
{
    std::vector<int> order;

    for (int i = 0; i < _size ; i++)
    {
        for (int j = 0; j < _size ; j++)
        {
            order.push_back(_blocks[i][j]);
        }
    }

    int inversions = 0;
    for (int i = 0; i < order.size() - 1; i++)
    {
        for (int j = i + 1; j < order.size(); j++)
        {
            if (order[i] > order[j] && order[j] != 0)
            {
                inversions++;
            }
        }
    }
    return inversions;
}

bool Board::isSolvable()
{
    std::vector<int> order;
    Board aimBoard (_aimBlocks);
    int orInversion = aimBoard.inversions();
    int inversion = this->inversions();
    if (_size  & 1)
    {
        return ((inversion & 1) == (orInversion & 1));
    }
    else
    {
        return (((inversion + (_size * _size - (_zeroY * _size + _zeroX))) & 1) == ((orInversion + (_size * _size - (aimBoard._zeroY * _size + aimBoard._zeroX)))  & 1));
    }
}
