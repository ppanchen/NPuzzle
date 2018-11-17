#include <iostream>
#include "../headers/CommonHeader.h"
#include "../headers/Solver.h"
#include "../headers/Logger.h"
#include "../headers/Parser.h"

int main(int argc, char* argv[])
{
    try
    {
        Parser parser(argc, argv);
        if (parser.getHelpRequired())
        {
            std::cout << "Usage: " << std::endl
                      << "Args:" << std::endl
                      << "\t-inputfile [file]" << std::endl
                      << "\t-heuristic [heuristic] " << std::endl
                      << "\t-algorithm [heuristic] " << std::endl
                      << "\t-help" << std::endl
                      << "Where:" << std::endl
                      << "\t[file] - any file with puzzle" << std::endl
                      << "\t[heuristic] - Manhhattan|Hamming|Euclidean or 1|2|3" << std::endl
                      << "\t[algorithm] - Greedy|Uniform or 1|2" << std::endl
                      << "\t-help - show this window" << std::endl;
            return 0;

        }
        if (!parser.isFileValid())
        {
            std::cout << "File is invalid" << std::endl;
            return 0;
        }
        std::cout << "Chosen heuristic : "<< parser.getHeuristic() << std::endl;
        std::cout << "Chosen algorithm : "<< parser.getAlgorithm() << std::endl;
        Board::staticInit(parser.getSize(), parser.getHeuristic());
        Solver *solver = new Solver(std::make_shared<Board>(parser.getMatrix()), parser.getAlgorithm());
        for (const auto &boards : solver->solution())
        {
            std::cout << boards;
        }
        std::cout << "Steps: " << solver->moves() << std::endl;

        Logger::printStatistic();
        return 0;
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

}