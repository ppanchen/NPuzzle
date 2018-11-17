#include <utility>

//
// Created by Petro Panchenko on 11/7/18.
//

#ifndef NPUZZLE_SOLVER_H
#define NPUZZLE_SOLVER_H

#include "Board.h"
#include "list"

enum Algorithm
{
    Uniform = 1,
    Greedy
};

class Solver
{
private:
    std::shared_ptr<Board> _initial;
    std::list<Board> result;

    struct Item
    {
        std::shared_ptr<Item> _prevBoard;
        std::shared_ptr<Board> _board;
        Item(std::shared_ptr<Item> prevBoard, std::shared_ptr<Board> board)
        {
            _prevBoard = prevBoard;
            _board = board;
        };
    };

    std::function<bool(std::shared_ptr<Item> i1, std::shared_ptr<Item> i2)> comparator;

public:
    Solver(std::shared_ptr<Board> initial, Algorithm a);
    bool isSolvable();
    int moves();
    std::list<Board> solution();

private:
    static int listDepth(Item item);
    void itemToList(Item item);
    bool containsInPath(Item item, Board *board);

};


#endif //NPUZZLE_SOLVER_H
