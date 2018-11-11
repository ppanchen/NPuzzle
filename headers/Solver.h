//
// Created by Petro Panchenko on 11/7/18.
//

#ifndef NPUZZLE_SOLVER_H
#define NPUZZLE_SOLVER_H

#include "Board.h"
#include "list"

class Solver
{
private:
    Board initial;
    std::list<Board> result;

    struct Item
    {
        Item *_prevBoard;
        Board *_board;
        Item(Item *prevBoard, Board *board) : _prevBoard(prevBoard), _board(board) {};
    };
    //functor
    class isGreater {
    public:
        isGreater() {}
        inline bool operator() (std::shared_ptr<Item> l1, std::shared_ptr<Item> & l2) const {
            int m1 = measure(*(l1.get()));
            int m2 = measure(*(l2.get()));
            int steps1 = m1 - l1->_board->h();
            int steps2 = m2 - l2->_board->h();
            if (steps1 != steps2)
                return steps1 < steps2;
            else
                return l1->_board->h() > l2->_board->h();
//            return m1 > m2;
        }
    };

public:
    Solver(Board initial);
    bool isSolvable();
    int moves();
    std::list<Board> solution();

private:
    static int measure(Item item);
    void itemToList(Item item);
    bool containsInPath(Item item, Board board);

};


#endif //NPUZZLE_SOLVER_H
