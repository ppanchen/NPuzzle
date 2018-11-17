//
// Created by Petro Panchenko on 11/7/18.
//

#ifndef NPUZZLE_BOARD_H
#define NPUZZLE_BOARD_H
#include <set>
#include <iostream>
#include <map>
#include <vector>
#include "CommonHeader.h"

enum Heuristic
{
    Manhattan = 1,
    Hamming,
    Euclidean
};

class Board
{
private:
    static Matrix _aimBlocks;
    static int _size;
    static Heuristic _algorithmFlag;

    Matrix _blocks;
    int _zeroX = 0;
    int _zeroY = 0;
    int _h = 0;

public:
//    Board(unsigned size);

    Board(Matrix blocks);

//    Board(const Board *b2);

    int dimension() const { return (int)_blocks.size(); }

    int h() { return _h; }

    bool isGoal() { return _h == 0; }

    bool operator==(const Board& other) const;

    std::set<std::shared_ptr<Board>> neighbors();

    static void staticInit(unsigned size, Heuristic algorithmFlag);

    friend std::ostream& operator<<(std::ostream& os, const Board& board);

    bool isSolvable();

private:
    int inversions();
    void init(const Matrix &block);

    std::shared_ptr<Board> swap(Matrix blocks2, int x1, int y1, int x2, int y2);

    int Manhattan(int x, int y);
    int Euclidean(int x, int y);

};

#endif //NPUZZLE_BOARD_H
