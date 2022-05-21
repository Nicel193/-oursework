#include "GameStatistic.h"

#include <iostream>
#include <fstream>

int GameStatistic::GameScore = 0;

void GameStatistic::SaveStatistic()
{
    std::ofstream out;

    out.open("E:\\Projects\\C++\\Coursework\\GameStatistic\\GameStatistic.txt", std::ofstream::app);
    std::ifstream in("E:\\Projects\\C++\\Coursework\\GameStatistic\\GameStatistic.txt");

    int game = 1;

    if (in.is_open())
    {
        char c = in.get();

        while (in.good())
        {
            c = in.get();

            if (c == '\n')
            {
                game++;

                if (game >= 1000)
                {
                    std::cout << "Statistics file are full\n";
                    return;
                }
            }
        }
    }
    else
    {
        std::cout << "Open (in)file error\n";
    }

    if (out.is_open())
    {
        out << "Game: " << game << " Your score: " << GameStatistic::GameScore << "\n";
    }
    else
    {
        std::cout << "Open (out)file error\n";
    }

    out.close();
}

void GameStatistic::ShowStatistic()
{
    std::cout << "Your score: " << GameStatistic::GameScore << "\n";
}