//
// Created by Petro Panchenko on 11/7/18.
//

#include "../headers/Solver.h"
#include "../headers/Logger.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

Solver::Solver(std::shared_ptr<Board> initial)
{
    this->_initial = initial;

    if(!initial->isSolvable())
        return;

    auto tmp = [&](std::shared_ptr<Item> i1, std::shared_ptr<Item> i2)
            {
//                if (i1.get()->_prevBoard == nullptr)
//                    return true;
//                if (i2.get()->_prevBoard == nullptr)
//                    return false;
                int steps1 = listDepth(*(i1.get()));
                int steps2 = listDepth(*(i2.get()));

                int a1 = steps1 + i1->_board->h();
                int a2 = steps2 + i2->_board->h();

                if (a1 == a2)
                    return i1->_board->h() < i2->_board->h();
                else
                    return a1 > a2;
//                if (steps1 != steps2)
//                    return steps1 < steps2;
//                else
                    return steps1 + i1->_board->h() > steps2 + i2->_board->h();
            };

    std::priority_queue<std::shared_ptr<Item>, std::deque<std::shared_ptr<Item>>, decltype(tmp)> priorityQueue(tmp);

    priorityQueue.push(std::make_shared<Item>(nullptr, initial));
    while (true)
    {
        std::shared_ptr<Item> board = priorityQueue.top();
//        std::cout << *(board->_board) << std::endl;
//        std::getchar();
        if(board->_board->isGoal()) {
            itemToList(Item(board, board->_board));
            return;
        }
        priorityQueue.pop();
        auto neighbors = board->_board->neighbors();
        int i = 0;
        for (auto const &neighbor : neighbors)
        {
            bool contain = containsInPath(*board, neighbor.get());
            if (contain)
                i++;
            if(neighbor != nullptr && !contain)
                priorityQueue.push(std::make_shared<Item>(Item(board, neighbor)));
        }
    }
}

bool Solver::isSolvable()
{
    return _initial->isSolvable();
}

int Solver::moves()
{
    if(!isSolvable())
        return -1;
    return (int)result.size() - 1;
}

std::list<Board> Solver::solution()
{
    return result;
}

int Solver::listDepth(Solver::Item item)
{
    Item *item2 = &item;
    int c = 0;
    while (true)
    {
        c++;
        item2 = item2->_prevBoard.get();
        Logger::timeCount++;
        if(item2 == nullptr)
        {
            return c;
        }
    }
}

void Solver::itemToList(Solver::Item item)
{
    Item *item2 = &item;
    while (true)
    {
        item2 = item2->_prevBoard.get();
        Logger::timeCount++;
        if (item2 == nullptr)
        {
            return;
        }
        result.push_front(*(item2->_board));
    }
}

bool Solver::containsInPath(Solver::Item item, Board *board)
{
    if (board == nullptr)
        return true;
    Item *item2 = &item;
    while (true)
    {
        if (*item2->_board == *board)
            return true;
        item2 = item2->_prevBoard.get();
        Logger::timeCount++;
        if (item2 == nullptr)
            return false;
    }
}
