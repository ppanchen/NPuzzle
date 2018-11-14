//
// Created by Petro Panchenko on 11/14/18.
//

#ifndef NPUZZLE_PARSER_H
#define NPUZZLE_PARSER_H

#include <string>
#include "../headers/CommonHeader.h"
#include "Board.h"


class Parser
{
public:
    static std::string helpString;

    Parser(int argc, char* argv[]);
    bool isFileValid();
    Matrix getMatrix();
    unsigned int getSize();
    Algorithm getAlgorithm();
    bool getHelpRequired();

private:
    bool _readFromInput = true;
    std::string _filename;
    Matrix _matrix;
    Algorithm _algo = Algorithm::Manhattan;
    unsigned _size = 0;
    bool _helpRequired = false;

    std::string getNextArg(int i, int argc, char *argv[]);
    void removeComments(std::string &line);
    bool equals(std::string s1, std::string s2);
};


#endif //NPUZZLE_PARSER_H
