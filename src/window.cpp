#include <iostream>

#include <GLFW/glfw3.h>

#include "window.hpp"

using namespace Windows;

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	if (monitor != nullptr) {
		const GLFWvidmode* monitorSettings = glfwGetVideoMode(monitor);
		width = monitorSettings->width;
		height = monitorSettings->height;
	}

	window = glfwCreateWindow(width, height, title, monitor, share);

	mode = monitor == nullptr ? WindowMode::WINDOWED : WindowMode::FULLSCREEN;
	mode = window == nullptr ? WindowMode::ERROR : mode;

	// Default to primary monitor if none provided.
	this->monitor = monitor == nullptr ? glfwGetPrimaryMonitor() : monitor;
}


Window::~Window() {
	glfwDestroyWindow(window);
}


void Window::SetWindowMode(WindowMode targetMode) {
	if (targetMode == mode) return;

	switch (targetMode) {
	case WindowMode::FULLSCREEN:
		SetFullscreen();
		break;

	case WindowMode::BORDERLESS:
		SetBorderless();
		break;

	case WindowMode::WINDOWED:
		SetWindowed();
		break;

	default:
		;
	}
	mode = targetMode;
}


void Window::SetFullscreenMonitor(int monitorIndex) {
	int numMonitors;
	GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);
	monitor = monitors[monitorIndex];
}


void Window::MakeThisContext() {
    glfwMakeContextCurrent(window);
}


void Window::Update() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		mode = WindowMode::CLOSED;
	}

	if (glfwGetKey(window, GLFW_KEY_F11)) {
		if (mode == WindowMode::FULLSCREEN) SetWindowMode(WindowMode::WINDOWED);
		else SetWindowMode(WindowMode::FULLSCREEN);
	}


	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}


bool Window::IsOpen() {
	return mode != WindowMode::ERROR && mode != WindowMode::CLOSED;
}


void Window::SetFullscreen() {
	const GLFWvidmode* monitorSettings = glfwGetVideoMode(monitor);
	const char* title = glfwGetWindowTitle(window);

	GLFWwindow* newWindow = glfwCreateWindow(monitorSettings->width, monitorSettings->height,
		title, monitor, nullptr);
	SetWindow(newWindow);
}


void Window::SetBorderless() {
}


void Window::SetWindowed() {
	const GLFWvidmode* monitorSettings = glfwGetVideoMode(monitor);
	const char* title = glfwGetWindowTitle(window);

	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	GLFWwindow* newWindow = glfwCreateWindow(0.9f * monitorSettings->width, 0.9f * monitorSettings->height,
		title, nullptr, nullptr);
	SetWindow(newWindow);
}


void Window::SetWindow(GLFWwindow* newWindow) {
	bool isContext = glfwGetCurrentContext() == window;

	glfwDestroyWindow(window);

	window = newWindow;
	if (isContext) MakeThisContext();
}


