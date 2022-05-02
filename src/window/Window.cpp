#include "Window.h"

GLFWwindow *Window::window;

int Window::width = 0;
int Window::height = 0;

void Window::Initialization(const char *nameWindow, const int width, const int height)
{
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(width, height, nameWindow, nullptr, nullptr);

    if (window == nullptr)
    {
        std::runtime_error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::terminate()
{
    glfwTerminate();
}

void Window::setShouldClose(bool flag)
{
    glfwSetWindowShouldClose(window, flag);
}

bool Window::isShouldClose()
{
    return glfwWindowShouldClose(window);
}