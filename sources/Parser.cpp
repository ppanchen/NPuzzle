//
// Created by Petro Panchenko on 11/14/18.
//

#include "../headers/Parser.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

Parser::Parser(int argc, char **argv)
{
    std::string supportedArgs[]
            {
                "-INPUTFILE", "-I",
                "-HEURISTIC", "-H",
                "-ALGORITHM", "-A",
                "-HELP"
            };

    //if first argument is not in supportedArgs array, that means this is inputfile
    if (argc > 1)
    {
        std::string *res = std::find(supportedArgs, supportedArgs + 7, argv[1]);
        if (res == supportedArgs + 7)
        {
            _filename = argv[1];
            _readFromInput = false;
        }
    }


    for (int i = 1; i < argc; i++)
    {
        std::string argument(argv[i]);

        if (equals(argument, supportedArgs[0]) || equals(argument, supportedArgs[1])) //-INPUTFILE processing
        {
            _filename = getNextArg(i, argc, argv);
            _readFromInput = false;
        }

        else if (equals(argument, supportedArgs[2]) || equals(argument, supportedArgs[3])) //-HEURISIC processing
        {
            std::string algoName = getNextArg(i, argc, argv);
            if (equals(algoName, "Manhhattan") || equals(algoName, "1"))
                _heur = Heuristic::Manhattan;
            else if (equals(algoName, "Hamming") || equals(algoName, "2"))
                _heur = Heuristic::Hamming;
            else if (equals(algoName, "Euclidean") || equals(algoName, "3"))
                _heur = Heuristic::Euclidean;
        }

        else if (equals(argument, supportedArgs[4]) || equals(argument, supportedArgs[5])) //-ALGORITHM processing
        {
            std::string algoName = getNextArg(i, argc, argv);
            if (equals(algoName, "Uniform") || equals(algoName, "1"))
                _algo = Algorithm::Uniform;
            else if (equals(algoName, "Greedy") || equals(algoName, "2"))
                _algo = Algorithm::Greedy;
        }

        else if (equals(argument, supportedArgs[6])) //-HELP processing
        {
            _helpRequired = true;
        }
    }

}

bool Parser::isFileValid()
{
    bool firstLine = true;
    int lineCount = 0;
    std::ifstream file;

    if (!_readFromInput)
    {
        file.open(_filename);
        if (!(file.is_open() && file.good()))
            return false;
    }

    std::string line;
    while (getline(_readFromInput ? std::cin : file , line))
    {
        removeComments(line);
        if (line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            continue;

        if (firstLine)
        {
            char *pEnd;
            _size = (unsigned)strtol(line.c_str(), &pEnd, 10);

            if (*pEnd != '\0'|| (_size <= 2))
            {
                if (_readFromInput)
                {
                    std::cout << "Input error, please try again!" << std::endl << "Size has to be greater than 2" << std::endl;
                    line = "";
                    continue;
                }
                else
                    return false;
            }

            _matrix.resize((unsigned)_size);
            firstLine = false;
        }
        else
        {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::string regexString = "(\\s*[0-9]+\\s*){" + std::to_string(_size) +  "}";
            std::regex regexNumber(regexString);

            bool isValid = std::regex_match(line, regexNumber);

            if (!isValid || lineCount >= _size)
            {
                if (_readFromInput)
                {
                    std::cout << "Input error, please try again!" << std::endl;
                    line = "";
                    continue;
                }
                else
                    return false;
            }

            std::stringstream  ss(line);
            int temp;
            while (ss >> temp)
                _matrix[lineCount].push_back(temp);
            lineCount++;
            if (_readFromInput && lineCount >= _size)
            {
                return true;
            }
        }
    }

    return isMatrixValid();
}

Matrix Parser::getMatrix()
{
    return _matrix;
}

unsigned int Parser::getSize()
{
    return _size;
}

Heuristic Parser::getHeuristic()
{
    return _heur;
}

Algorithm Parser::getAlgorithm()
{
    return _algo;
}

bool Parser::getHelpRequired()
{
    return _helpRequired;
}

void Parser::removeComments(std::string & line)
{
    line = line.substr(0, line.find('#'));
    line.erase(line.find_last_not_of(" \t\n\v\f\r") + 1);
    line.erase(0, line.find_first_not_of(" \t\n\v\f\r"));
}

bool Parser::equals(std::string s1, std::string s2)
{
    return std::equal(s1.begin(), s1.end(),
                      s2.begin(), s2.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

std::string Parser::getNextArg(int i, int argc, char **argv)
{
    int next = i + 1;
    if (next < argc)
    {
        if (argv[next][0] != '-')
            return argv[next];
    }
    else
        throw std::invalid_argument("Arguments error!");
    return nullptr;
}

bool Parser::isMatrixValid()
{
    int s = 0;
    while (s < _size * _size)
    {
        bool wasFound = false;
        for(const auto &vector : _matrix)
        {
            wasFound |= std::find(vector.begin(), vector.end(), s) != vector.end();
        }
        if (!wasFound)
            return false;
        s++;
    }
    return true;
}
