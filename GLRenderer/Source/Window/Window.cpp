#include "Window.h"

#include <iostream>
#include <iomanip>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window() : Window(640, 480, "GLFW Window")
{
}

Window::Window(int width, int height, const char* title) :
    width{ width },
    height{ height }
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "[Window] GLFW Failed to init!" << std::endl;
        throw std::runtime_error("[Window] GLFW Failed to init!");
    }

    std::cout << "[Window] GLFW Initialized! Version: " << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!glfwWindow)
    {
        glfwTerminate();
        std::cerr << "[Window] GLFW Failed to create window!" << std::endl;
        throw std::runtime_error("[Window] GLFW Failed to create window!");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(GetGLFWWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[Window] GLAD Failed to init!" << std::endl;
        throw std::runtime_error("[Window] GLAD Failed to init!");
    }

    std::cout << "[Window] GLAD Initialized! OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
    std::cout << "[Window] GLFW Terminated! Time elapsed: " << glfwGetTime() << " seconds" << std::endl;
    glfwTerminate();
}

void Window::Loop(std::function<void()> renderLoop)
{
    double lastTime{ glfwGetTime() };
    double lastTimePrintFPS{ glfwGetTime() };
    int frames{ 0 };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(GetGLFWWindow()))
    {
        // Calculate Delta Time
        ++frames;

        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (currentTime - lastTimePrintFPS >= 1.0) {
            
            std::cout << std::fixed << std::setprecision(4);
            std::cout << "[Window] Framerate: " << 1000.0 / double(frames) << " ms | " << frames << " FPS" << std::endl;
            std::cout << std::resetiosflags(std::ios::fixed) << std::setprecision(6);
            
            frames = 0;
            lastTimePrintFPS = currentTime;
        }

        if (renderLoop)
        {
            renderLoop();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(GetGLFWWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}
