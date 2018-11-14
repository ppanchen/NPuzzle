//
// Created by Petro Panchenko on 11/14/18.
//

#include "../headers/Logger.h"
#include <iostream>

int Logger::memoryCount = 0;
int Logger::timeCount = 0;

void Logger::printStatistic()
{
    std::cout << "Memory complexity: " << memoryCount << std::endl;
    std::cout << "Time complexity: " << timeCount << std::endl;
}