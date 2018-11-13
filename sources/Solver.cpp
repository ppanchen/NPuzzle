//
// Created by Petro Panchenko on 11/7/18.
//

#include "../headers/Solver.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

Solver::Solver(std::shared_ptr<Board> initial)
{
    this->initial = initial;

    if(!isSolvable())
        return;

    auto tmp = [](std::shared_ptr<Item> i1, std::shared_ptr<Item> i2)
            {
                int steps1 = listDepth(*(i1.get()));
                int steps2 = listDepth(*(i2.get()));
                if (steps1 != steps2)
                    return steps1 < steps2;
                else
                    return i1->_board->h() > i2->_board->h();
            };

    std::priority_queue<std::shared_ptr<Item>, std::deque<std::shared_ptr<Item>>, decltype(tmp)> priorityQueue(tmp);

    priorityQueue.push(std::make_shared<Item>(nullptr, initial));
    while (true)
    {
        std::shared_ptr<Item> board = priorityQueue.top();

        if(board->_board->isGoal()) {
            itemToList(Item(board, board->_board));
            return;
        }

        auto neighbors = board->_board->neighbors();
        for (auto const &neighbor : neighbors)
        {

            //оптимизация. Очевидно, что один из соседей - это позиция
            // которая была ходом раньше. Чтобы не возвращаться в состояния,
            // которые уже были делаем проверку. Экономим время и память.
            if(neighbor != nullptr && !containsInPath(*board, *neighbor))
                priorityQueue.push(std::make_shared<Item>(board, neighbor));
        }
    }
}

bool Solver::isSolvable()
{
    return true;
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
        if (item2 == nullptr)
        {
            return;
        }
        result.push_back(*(item2->_board));
    }
}

bool Solver::containsInPath(Solver::Item item, Board board)
{
    Item *item2 = &item;
    while (true)
    {
        if (*item2->_board == board)
            return true;
        item2 = item2->_prevBoard.get();
        if (item2 == nullptr)
            return false;
    }
}
