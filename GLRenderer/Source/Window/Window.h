#pragma once

#include <functional>

struct GLFWwindow;

class Window
{
private:

	GLFWwindow* glfwWindow;

	int width;
	int height;

	double deltaTime;

public:

	Window();
	Window(int width, int height, const char* title = "");

	~Window();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline double GetDeltaTime() const { return deltaTime; }
	inline GLFWwindow* GetGLFWWindow() const { return glfwWindow; }

	void Loop(std::function<void()> renderLoop = nullptr);
};

