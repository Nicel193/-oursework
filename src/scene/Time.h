#ifndef TIME_H
#define TIME_H

#pragma once

class Time
{
public:
    static void Initialization();
    static void Update();

    static float GetDelta();

private:
    static float lastTime, delta;
};
#endif