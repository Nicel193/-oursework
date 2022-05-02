#ifndef EVENTS_H
#define EVENTS_H

#pragma once

#include "Window.h"

typedef unsigned int uint;

class Events
{
public:
    static bool *keys;
    static uint *frames;
    static uint current;

    static float deltaX;
    static float deltaY;
    static float x;
    static float y;

    static bool cursorLocked;
    static bool cursorStarted;

    static int Initialization();

    static void pullEvents();

    //--------------------------------

    static bool isPressed(int keycode);
    static bool justPressed(int keycode);

    static bool isClicked(int button);
    static bool justClicked(int button);
};

#endif