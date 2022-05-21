#include "Time.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

float Time::lastTime = 0;
float Time::delta = 0;

void Time::Initialization()
{
    lastTime = glfwGetTime();
    delta = 0.0f;
}

void Time::Update()
{
    float currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    lastTime = currentTime;
}

float Time::GetDelta()
{
    return delta;
}
