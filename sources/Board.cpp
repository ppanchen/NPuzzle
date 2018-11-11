//
// Created by Petro Panchenko on 11/7/18.
//

#include "../headers/Board.h"
#include "sstream"

int Board::_size = 0;
Matrix Board::_aimBlocks;

/// Copy constructor
/// \param b2 - instance to be copied
//Board::Board(const Board &b2)
//{
//    init(b2._blocks);
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

std::set<Board*> Board::neighbors()
{
    std::set<Board*> boardList;
    boardList.insert(swap(getNewBlock(), _zeroX, _zeroY, _zeroX, _zeroY + 1));
    boardList.insert(swap(getNewBlock(), _zeroX, _zeroY, _zeroX, _zeroY - 1));
    boardList.insert(swap(getNewBlock(), _zeroX, _zeroY, _zeroX - 1, _zeroY));
    boardList.insert(swap(getNewBlock(), _zeroX, _zeroY, _zeroX + 1, _zeroY));

    return boardList;
}

void Board::staticInit(unsigned size)
{
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
            if (_blocks[i][j] != _aimBlocks[i][j] && _blocks[i][j] != 0)
                _h += 1;
            if (_blocks[i][j] == 0)
            {
                _zeroX = i;
                _zeroY = j;
            }
        }
    }
}


Matrix Board::getNewBlock()
{
    return Matrix(_blocks);
}

Board* Board::swap(Matrix blocks2, int x1, int y1, int x2, int y2)
{
    if (x2 > -1 && x2 < dimension() && y2 > -1 && y2 < dimension())
    {
        int t = blocks2[x2][y2];
        blocks2[x2][y2] = blocks2[x1][y1];
        blocks2[x1][y1] = t;
        return new Board(blocks2);
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
