//
// Created by Petro Panchenko on 11/7/18.
//

#include "../headers/Solver.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

Solver::Solver(Board initial) : initial(initial)
{
    if(!isSolvable())
        return;
//
//    auto tmp = [](Item *i1, Item *i2)
//            {
//                return measure(*i1) > measure(*i2);
//            };
    std::priority_queue<std::shared_ptr<Item>, std::deque<std::shared_ptr<Item>>, Solver::isGreater> priorityQueue;

//    Item board(nullptr, &initial);
    priorityQueue.push(std::make_shared<Item>(Item(nullptr, &initial)));

    while (true)
    {
        Item* board = (priorityQueue.top().get());

        if(board->_board->isGoal()) {
            itemToList(Item(board, board->_board));
            return;
        }

        auto neighbors = board->_board->neighbors();
        for (auto neighbor : neighbors)
        {

            //оптимизация. Очевидно, что один из соседей - это позиция
            // которая была ходом раньше. Чтобы не возвращаться в состояния,
            // которые уже были делаем проверку. Экономим время и память.
            if(neighbor != nullptr && !containsInPath(*board, *neighbor))
                priorityQueue.push(std::make_shared<Item>(Item(board, neighbor)));
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

int Solver::measure(Solver::Item item)
{
    Item *item2 = &item;
    int c = 0;   // g(x)
    int measure = item._board->h();  // h(x)
    while (true)
    {
        c++;
        item2 = item2->_prevBoard;
        if(item2 == nullptr)
        {
            // g(x) + h(x)
            return measure + c;
        }
    }
}

void Solver::itemToList(Solver::Item item)
{
    Item *item2 = &item;
    while (true)
    {
        item2 = item2->_prevBoard;
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
        item2 = item2->_prevBoard;
        if (item2 == nullptr)
            return false;
    }
}
