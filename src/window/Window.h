#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{

public:
    static void Initialization(const char *nameWindow, const int width, const int height);
    static void swapBuffers();
    static void terminate();
    static void setShouldClose(bool flag);

    static bool isShouldClose();

    static GLFWwindow *window;

    static int width;
	static int height;
};

#endif