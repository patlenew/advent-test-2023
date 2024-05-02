// Advent2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "FileReader.h"
#include "Logger.h"
#include <ctime>

void Execute(bool& activeRef);

int main()
{
    clock_t time_req;
    time_req = clock();

    bool active = true;

    while (active)
    {
        Execute(active);

        clock_t currentTimeClock = clock() - time_req;
        float currentTime = (float)currentTimeClock/CLOCKS_PER_SEC;

        // 5 min
        if (currentTime >= 300)
        {
            active = false;
            DEBUG_LOG_1("Something is wrong with my code! Time: ", currentTime)
        }
    }
}
void Execute(bool& activeRef)
{
    std::cout << "Hello World!\n";

    FileReader fileReader;
    string content = fileReader.GetFileContent("input5_1.txt");

    //one* first = new one();
    //first->Run(firstContent);
    //first->Run_2(firstContent);

    //two second;
    ////second.Run(content);
    //second.Run_2(content);

    //three third;
    //third.Run(content);
    //third.Run_2(content);

    //four fourth;
    //fourth.Run(content);
    //fourth.Run_2(content);

    five fifth;
    //fifth.Run(content);
    fifth.Run_2(content);

    activeRef = false;
}
