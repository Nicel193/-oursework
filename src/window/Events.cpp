#include "Events.h"
#include <string.h>

bool *Events::keys;
uint *Events::frames;
uint Events::current = 0;

float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;

bool Events::cursorLocked = false;
bool Events::cursorStarted = false;

#define MOUSE_BUTTONS 1024

void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
{
    if (Events::cursorLocked)
    {
        Events::deltaX = xPos - Events::x;
        Events::deltaY = yPos - Events::y;
    }
    else
    {
        Events::cursorStarted = true;
    }

    Events::x = xPos;
    Events::y = yPos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        Events::keys[MOUSE_BUTTONS + button] = true;
        Events::frames[MOUSE_BUTTONS + button] = Events::current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::keys[MOUSE_BUTTONS + button] = false;
        Events::frames[MOUSE_BUTTONS + button] = Events::current;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        Events::keys[key] = true;
        Events::frames[key] = Events::current;
    }
    else if (action == GLFW_RELEASE)
    {
        Events::keys[key] = false;
        Events::frames[key] = Events::current;
    }
}

void window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}

int Events::Initialization()
{
    GLFWwindow *window = Window::window;

    keys = new bool[1032];
    frames = new uint[1032];

    memset(keys, false, 1032 * sizeof(bool));
    memset(frames, false, 1032 * sizeof(bool));

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    return 0;
}

void Events::pullEvents()
{
    current++;
    deltaX = 0;
    deltaY = 0;
    glfwPollEvents();
}

bool Events::isPressed(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
    {
        return false;
    }

    return keys[keycode];
}

bool Events::justPressed(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
    {
        return false;
    }

    return keys[keycode] && frames[keycode] == current;
}

bool Events::isClicked(int button)
{
    int index = MOUSE_BUTTONS + button;
    return keys[index];
}

bool Events::justClicked(int button)
{
    int index = MOUSE_BUTTONS + button;
    return keys[index] && frames[index] == current;
}
