#ifndef GAMESTATISTIC_H
#define GAMESTATISTIC_H

#pragma once

class GameStatistic
{
public:
   static void SaveStatistic();
   static void ShowStatistic();

   static int GameScore;
};

#endif