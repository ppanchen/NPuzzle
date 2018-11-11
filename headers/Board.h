//
// Created by Petro Panchenko on 11/7/18.
//

#ifndef NPUZZLE_BOARD_H
#define NPUZZLE_BOARD_H
#include "CommonTools.h"
#include <set>
#include <iostream>

using Matrix = std::vector<std::vector<int>>;

class Board
{
private:
    static Matrix _aimBlocks;
    static int _size;

    Matrix _blocks;
    int _zeroX = 0;
    int _zeroY = 0;
    int _h = 0;

public:
//    Board(unsigned size);

    Board(Matrix blocks);

//    Board(const Board &b2);

    int dimension() const { return (int)_blocks.size(); }

    int h() { return _h; }

    bool isGoal() { return _h == 0; }

    bool operator==(const Board& other) const;

    std::set<Board*> neighbors();

    static void staticInit(unsigned size);

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
    void init(const Matrix &block);

    Matrix getNewBlock();

    Board* swap(Matrix blocks2, int x1, int y1, int x2, int y2);


};

#endif //NPUZZLE_BOARD_H
