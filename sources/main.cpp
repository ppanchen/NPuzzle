#include <iostream>
#include "../headers/Solver.h"
#define NDEBUG
#include <assert.h>

int main(int argc, char* argv[])
{
    Matrix blocks
    {
        {2, 0, 3},
        {1, 8, 4},
        {7, 6, 5}
    };

    Board::staticInit(3, Algorithm::Hamming);
//    Board *initial = new Board(blocks);
    Solver *solver = new Solver(std::make_shared<Board>(blocks));
    for (auto boards : solver->solution())
    {
        std::cout << boards;
    }
//    getchar();
    return 0;
}