#include <iostream>
#include "../headers/CommonHeader.h"
#include "../headers/Solver.h"
#include "../headers/Logger.h"
#include "../headers/Parser.h"

int main(int argc, char* argv[])
{
//    Matrix blocks
//    {
//        {2, 0, 3},
//        {1, 8, 4},
//        {7, 6, 5}
//    };

    Parser parser(argc, argv);

    if (!parser.isFileValid())
    {
        std::cout << "File is invalid" << std::endl;
        return 0;
    }

    Board::staticInit(parser.getSize(), parser.getAlgorithm());
    Solver *solver = new Solver(std::make_shared<Board>(parser.getMatrix()));
    for (const auto &boards : solver->solution())
    {
        std::cout << boards;
    }
    std::cout << "Steps: " << solver->moves() << std::endl;

    Logger::printStatistic();
    return 0;
}